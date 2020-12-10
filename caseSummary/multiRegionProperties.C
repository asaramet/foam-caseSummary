/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "multiRegionProperties.H"
#include "turbulenceProperties.H"
#include "Time.H"
#include "Ostream.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::multiRegionProperties::multiRegionProperties (const Foam::Time& runTime)
:
  runTime_ {runTime},
  regionProperties_ { Foam::regionProperties(runTime_) },
  count_ { regionProperties_.count() },
  names_ { regionProperties_.sortedNames() }
{ }


// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::multiRegionProperties::write(Foam::Ostream& os) const
{

  forAll(names_, regID)
  {
    os.writeEntry("Region", names_[regID]);
    Foam::turbulenceProperties(runTime_, names_[regID]).write(os);

    os << "TODO: Transport Properties for " << names_[regID] << Foam::endl;
    os << Foam::endl;
  }

}
