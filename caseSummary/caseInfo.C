/*---------------------------------------------------------------------------*\

Copyright (C) 2015 OpenFOAM Foundation
Copyright (C) 2018 OpenCFD Ltd.

Source: https://develop.openfoam.com/Development/openfoam/-/tree/OpenFOAM-v2006/
or: applications/utilities/preProcessing/createZeroDictionary/boundaryInfo.C

License
   This file is part of OpenFOAM.

   OpenFOAM is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "Time.H"

#include "caseInfo.H"

// * * * * * * * * * * * * Private Member Functions* * * * * * * * * * * * * //

Foam::label Foam::caseInfo::findPatchConditionID(const Foam::label patchI, const Foam::word& patchName) const
{
  const Foam::wordList& patchGroups = boundaryInfo_.groups()[patchI];

  // Assign condition according to last consdition applies, wins
  forAllReverse(conditionNames_, conditionI)
  {
    const Foam::wordRes& patchNames = patchNames_[conditionI];

    for (const Foam::wordRe& select : patchNames) // wordRe is a Foam::word but can contain a regular expression
    {
      // Return literal match
      if (select == patchName)
        return conditionI;
      // Return regex match
      else if (select.match(patchName))
        return conditionI;
      // Check for group match
      else
      {
        for (const Foam::word& groupName : patchGroups)
        {
          if (select == groupName)
            return conditionI;
        }
      }
    }
  }

  // Error if not found
  FatalErrorInFunction << "Boundary patch " << patchName << " not defined" << exit(FatalError);

  return -1;
}

void Foam::caseInfo::updateGeometricBoundaryField()
{
  forAll(boundaryInfo_.names(), i)
  {
    const Foam::word& patchName = boundaryInfo_.names()[i];

    // if constraint for this field is missing, update it
    if (!boundaryInfo_.constraint()[i])
    {
      // Condition ID to apply to mesh boundary patch name
      const Foam::label conditionI = findPatchConditionID(i, patchName);

      const Foam::word& category = patchCategories_[conditionI];

      boundaryInfo_.setType(i, category);
    }
  }

  boundaryInfo_.write();
}

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //
Foam::caseInfo::caseInfo(const Foam::Time& runTime, const Foam::word& regionName)
:
  properties_
  (
    Foam::IOobject
    (
      "caseProperties",           // name
      runTime.system(),           // instance (fileName)
      regionName,                 // local (fileName)
      runTime,                    // registry (objectRegistry)
      Foam::IOobject::MUST_READ,  // read option
      Foam::IOobject::NO_WRITE    // write option
    )
  ),
  boundaryInfo_(runTime, regionName),
  bcDict_(properties_.subDict("boundaryConditions")),
  conditionNames_(bcDict_.toc()),                          // dictionary's table of contents
  patchNames_(conditionNames_.size()),
  patchCategories_(conditionNames_.size()),
  patchTypes_(conditionNames_.size())
{
  // Read the (user-supplied) boundary condition information
  Foam::Info << "--> Read the (user-supplied) boundary condition information" << Foam::endl;

  forAll(conditionNames_, i)
  {
    const Foam::dictionary& dict = bcDict_.subDict(conditionNames_[i]);
    dict.readEntry("category", patchCategories_[i]); // read 'category' from dict and append it to patchCategories_
    dict.readEntry("type", patchTypes_[i]);
    dict.readEntry("patches", patchNames_[i]);
  }
}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

const Foam::List<Foam::wordRes>& Foam::caseInfo::patchNames() const
{
  return patchNames_;
}

const Foam::word& Foam::caseInfo::conditionName(const Foam::label patchI) const
{
  return conditionNames_[patchI];
}

const Foam::word& Foam::caseInfo::patchCategory(const Foam::label patchI) const
{
  return patchCategories_[patchI];
}

const Foam::word& Foam::caseInfo::patchType(const Foam::label patchI) const
{
  return patchTypes_[patchI];
}
