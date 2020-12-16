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
    Foam::word regionName { names_[regID] };
    os.writeEntry("Region", regionName);

    os << " Turbulence:" << Foam::endl;
    Foam::turbulenceProperties(runTime_, regionName).write(os);

    os << Foam::endl;
  }

}
