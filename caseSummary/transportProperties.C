/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "transportProperties.H"
#include "Time.H"
#include "Ostream.H"
//#include "transportModel.H"
//#include "interfaceProperties.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::transportProperties::transportProperties(const Foam::Time& runTime)
:
  transportProperties_
  {
    IOobject
    (
      "transportProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

Foam::transportProperties::transportProperties(const Foam::Time& runTime, const Foam::word& regionName)
:
  transportProperties_
  {
    IOobject
    (
      regionName/"transportProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::transportProperties::write(Foam::Ostream& os) const
{
  os << "Transport properties:" << Foam::endl;
  os << " ";
  os.writeEntry("Model", transportProperties_.get<Foam::word>("transportModel"));

  if (transportProperties_.found("nu"))
  {
    const Foam::dimensionedScalar nu { transportProperties_.get<Foam::dimensionedScalar>("nu") };
    os << " ";
    os.writeEntry("nu", nu.value());
    os << " ";
    os.writeEntry("nu dim/list", nu.dimensions());
  }

  // TODO: Get the coefficients if any

  os << Foam::endl;
}
