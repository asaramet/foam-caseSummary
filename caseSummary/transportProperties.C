/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "transportProperties.H"
#include "helperFunctions.H"
#include "Time.H"
#include "Ostream.H"

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

  std::unique_ptr<Foam::dictionary> transportDict { new Foam::dictionary {transportProperties_ }};
  Foam::writeDicts_(os, *transportDict);

  os << Foam::endl;
}
