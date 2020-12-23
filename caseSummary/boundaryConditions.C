/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "boundaryConditions.H"
#include "Time.H"
#include "Ostream.H"
#include "IOobjectList.H"

#include "volFieldsFwd.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::boundaryConditions::boundaryConditions(const Foam::Time& runTime, const Foam::word& regionName)
:
  runTime_ { runTime },
  regionName_ { regionName }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::boundaryConditions::write(Foam::Ostream& os) const
{
  // ignore it if no volumetric mesh found
  if (! Foam::fileHandler().isFile(runTime_.constant()/"polyMesh/points"))
  {
    os << "Warning: Can't read boundary conditions as there is no generated volume mesh!" << Foam::endl;
    return;
  }

  // get the volume mesh
  const Foam::fvMesh mesh
  (
    Foam::IOobject
    (
      regionName_,
      runTime_.timeName(0),
      runTime_,
      Foam::IOobject::MUST_READ
    )
  );

  // create a list of field names
  const Foam::wordList fieldNames
  (
    Foam::IOobjectList(mesh, runTime_.timeName()).sortedNames()
  );

  if (fieldNames.empty())
    os << "TODO: HERE YOU MUST CHECK THE REGIONS" << Foam::endl;

  forAll(fieldNames, i)
  {
    os.writeEntry("-", fieldNames[i]);
  }
  
} // end write(os&)
