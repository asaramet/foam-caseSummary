/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "Ostream.H"
#include "Time.H"

#include "extraFields.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::extraFields::extraFields(const Foam::Time& runTime)
:
  g_
  {
    IOobject
    (
      "g",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
  {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::extraFields::write(Foam::Ostream& os) const
{
  os << "Gravitational acceleration (g):" << Foam::endl;
  //g_.writeData(os);
  os << " ";
  os.writeEntry("Dimensions", g_.dimensions());
  os << " ";
  os.writeEntry("Value", g_.value());
}
