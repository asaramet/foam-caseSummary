/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "turbulenceProperties.H"
#include "helperFunctions.H"
#include "Time.H"
#include "Ostream.H"
#include "dictionaryEntry.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::turbulenceProperties::turbulenceProperties(const Foam::Time& runTime)
:
  turbulenceProperties_
  {
    IOobject
    (
      "turbulenceProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

Foam::turbulenceProperties::turbulenceProperties(const Foam::Time& runTime, const Foam::word& regionName)
:
  turbulenceProperties_
  {
    IOobject
    (
      regionName/"turbulenceProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::turbulenceProperties::write(Foam::Ostream& os) const
{
  // get flow type (laminar or turbulent)
  const word simulationType { turbulenceProperties_.get<word>("simulationType") };

  // display flow type
  os << " ";
  os.writeEntry("Flow", simulationType);

  // get the model type sub-dict as a unique pointer
  std::unique_ptr<Foam::dictionary> modelDict {new Foam::dictionary {turbulenceProperties_.findDict(simulationType)}};

  if (modelDict->empty()) return; // if there is no model sub dictionary leave it

  Foam::wordList toc_ {modelDict->toc()};

  Foam::writeDicts_(os, *modelDict);
  //modelDict->writeEntries(os);

} // end write(os&)
