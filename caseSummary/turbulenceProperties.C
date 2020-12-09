/*---------------------------------------------------------------------------*\

License

\*---------------------------------------------------------------------------*/

#include "turbulenceProperties.H"
#include "Time.H"
#include "Ostream.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::turbulenceProperties::turbulenceProperties(const Foam::Time& runTime)
:
  turbulenceProperties_
  (
    IOobject
    (
      "turbulenceProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  )
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::turbulenceProperties::write(Foam::Ostream& os) const
{
  // get simulation Type
  const word simulationType(turbulenceProperties_.get<word>("simulationType"));
  os.writeEntry("Simulation type", simulationType);
}
