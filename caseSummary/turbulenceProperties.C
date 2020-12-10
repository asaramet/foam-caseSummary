/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "turbulenceProperties.H"
#include "Time.H"
#include "Ostream.H"
//#include "turbulenceModel.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::turbulenceProperties::turbulenceProperties(const Foam::Time& runTime)
:
  turbulenceProperties_
  {
    IOobject
    (
      "turbulenceProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

Foam::turbulenceProperties::turbulenceProperties(const Foam::Time& runTime, const Foam::word& regionName) 
:
  turbulenceProperties_
  {
    IOobject
    (
      regionName/"turbulenceProperties",
      runTime.constant(),
      runTime,
      IOobject::MUST_READ,
      IOobject::NO_WRITE
    )
  }
 {}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::turbulenceProperties::write(Foam::Ostream& os) const
{
  // get flow type (laminar or turbulent)
  const word simulationType { turbulenceProperties_.get<word>("simulationType") };

  if (simulationType == "laminar")
  {
    // display that flow is laminar and exit
    os.writeEntry("Flow", simulationType);
    return;
  }

  // get the model type sub-dict
  const dictionary modelDict { turbulenceProperties_.subDict(simulationType)};

  if (simulationType == "RAS")
  {
    os.writeEntry("Flow", "turbulent RAS");
    os.writeEntry("RAS Model", modelDict.getOrDefault<word>("RASModel", "Warning: RASModel is not defined in turbulenceProperties"));

    word modelCoeff = modelDict.getOrDefault<word>("RASModel", "not found") + "Coeff";

    os.writeEntry("COEFF", modelCoeff);
  }

  if (simulationType == "LES")
  {
    os.writeEntry("Flow", "turbulent LES");
    os.writeEntry("LES Model", modelDict.getOrDefault<word>("LESModel", "Warning: LESModel is not defined in turbulenceProperties"));
  }

  os.writeEntry("turbulence", modelDict.getOrDefault<word>("turbulence", "Warning: missing turbulence keyword in turbulenceProperties"));
}
