/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "controlDict.H"
#include "Time.H"
#include "Ostream.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::controlDict::controlDict(const Foam::Time& runTime)
: controlDict_ { runTime.controlDict() }
{}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::controlDict::write(Foam::Ostream& os) const
{
  const word solverName {controlDict_.getOrDefault<word>("application", "Warning: missing application in controlDict")};
  os.writeEntry("Solver", solverName);
}
