/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "transportProperties.H"
#include "Time.H"
#include "Ostream.H"
//#include "transportModel.H"

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
  os.writeEntry("Model", transportProperties_.get<Foam::word>("transportModel"));
  //os.writeEntry("nu", transportProperties_.get<Foam::scalarField>("nu"));

  os << Foam::endl;
}
