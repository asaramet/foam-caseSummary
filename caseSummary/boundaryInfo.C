/*---------------------------------------------------------------------------*\

Copyright (C) 2015 OpenFOAM Foundation
Copyright (C) 2018 OpenCFD Ltd.

Source: https://develop.openfoam.com/Development/openfoam/-/tree/OpenFOAM-v2006/
or: applications/utilities/preProcessing/createZeroDictionary/boundaryInfo.C

\*---------------------------------------------------------------------------*/

#include "boundaryInfo.H"
#include "Time.H"
#include "polyMesh.H"
#include "processorPolyPatch.H"

// * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * * * //

namespace Foam
{
  // define debug switch (0) to typeName (IOPtrList<entry>)
  defineTemplateTypeNameAndDebug(IOPtrList<entry>, 0);
}

// * * * * * * * * * * * * Private Member Functions* * * * * * * * * * * * * //

Foam::IOPtrList<Foam::entry> Foam::boundaryInfo::readBoundaryDict
(
  const Foam::Time& runTime,
  const Foam::word& regionName
) const
{
  //Foam::Info << "--> Reading mesh boundaries" << Foam::endl;

  // for this usage, change the typeName of IOPtrList<entry> function to the one in polyBoundaryMesh
  const_cast<Foam::word&>(IOPtrList<Foam::entry>::typeName) = polyBoundaryMesh::typeName;

  // get the patch list
  IOPtrList<entry> boundaryPatchList
  (
    IOobject
    (
      "boundary",
      runTime.findInstance(regionName/polyMesh::meshSubDir, "boundary"),
      regionName/polyMesh::meshSubDir,
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE,
      false
    )
  );

  // remove zero-sized patches
  Foam::PtrList<Foam::entry> boundaryPatchListNew {};
  forAll(boundaryPatchList, patchI)
  {
    const Foam::dictionary& dict { boundaryPatchList[patchI].dict() };
    // pType - patch type (ex: 'empty', 'patch', 'symmetryPlane', 'zeroGradient' etc.)
    const Foam::word pType { dict.get<Foam::word>("type") };
    // processorPolyPatch::typeName is usually 'processor'
    bool procPatch { pType == Foam::processorPolyPatch::typeName };

    bool addPatch { true };
    if (!procPatch) {
      // get the number of faces (Foam::label is collection of some type of ints)
      Foam::label nFaces = dict.get<Foam::label>("nFaces");
      // Calculate the sum of faces (labels in nFaces)
      Foam::reduce(nFaces, Foam::sumOp<Foam::label>());
      if (nFaces == 0)
        addPatch = false;
    }

    // add only non-zero patches
    if (addPatch)
      boundaryPatchListNew.append(boundaryPatchList[patchI].clone());
  }

  boundaryPatchList.transfer(boundaryPatchListNew);

  return boundaryPatchList;
}

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::boundaryInfo::boundaryInfo(const Foam::Time& runTime, const Foam::word& regionName)
:
  boundaryDict_(readBoundaryDict(runTime, regionName)),
  names_(),
  types_(),
  constraint_(),
  groups_(),
  allGroupNames_()
{
  names_.setSize(boundaryDict_.size());
  types_.setSize(boundaryDict_.size());
  constraint_.setSize(boundaryDict_.size(), false);
  groups_.setSize(boundaryDict_.size());

  forAll(boundaryDict_, patchI)
  {
    const Foam::dictionary& dict { boundaryDict_[patchI].dict() };

    names_[patchI] = dict.dictName();
    dict.readEntry("type", types_[patchI]);
    if (Foam::polyPatch::constraintType(types_[patchI]))
      constraint_[patchI] = true;

    if (dict.readIfPresent("inGroups", groups_[patchI]))
      allGroupNames_.insert(groups_[patchI]);
  }
}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

const Foam::wordList& Foam::boundaryInfo::names() const
{
  return names_;
}

const Foam::wordList& Foam::boundaryInfo::types() const
{
  return types_;
}

const Foam::boolList& Foam::boundaryInfo::constraint() const
{
  return constraint_;
}

const Foam::List<Foam::wordList>& Foam::boundaryInfo::groups() const
{
  return groups_;
}

const Foam::wordHashSet& Foam::boundaryInfo::allGroupNames() const
{
  return allGroupNames_;
}

void Foam::boundaryInfo::setType(const label patchI, const word& condition)
{
  // do not override constraint types
  if (constraint_[patchI])
    return;
}
