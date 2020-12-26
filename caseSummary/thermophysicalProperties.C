/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "thermophysicalProperties.H"
#include "helperFunctions.H"
#include "Time.H"
#include "Ostream.H"
#include "dictionaryEntry.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::thermophysicalProperties::thermophysicalProperties(const Foam::Time& runTime)
:
  thermophysicalProperties_
  {
    Foam::IOobject
    (
      "thermophysicalProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

Foam::thermophysicalProperties::thermophysicalProperties(const Foam::Time& runTime, const Foam::word& regionName)
:
  thermophysicalProperties_
  {
    Foam::IOobject
    (
      regionName/"thermophysicalProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::thermophysicalProperties::write(Foam::Ostream& os) const
{
  std::unique_ptr<Foam::dictionary> thermophysicalDict { new Foam::dictionary { thermophysicalProperties_ }};
  Foam::writeDicts_(os, *thermophysicalDict);

} // end write(os&)
