/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "boundaryConditions.H"
#include "Time.H"
#include "Ostream.H"
#include "volFieldsFwd.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::boundaryConditions::boundaryConditions(const Foam::Time& runTime)
:
  runTime_ { runTime }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::boundaryConditions::write(Foam::Ostream& os) const
{
  os << "p is a volFieldsScalar not dict!!!" << Foam::endl;
  #if 0
  const Foam::IOdictionary p_
  {
    Foam::IOobject
    (
      "p",
      runTime_.timeName(0),
      runTime_,
      Foam::IOobject::MUST_READ,
      Foam::IOobject::NO_WRITE
    )
  };

  os.writeEntry("DICT NAME", p_.name());
  #endif

} // end write(os&)
