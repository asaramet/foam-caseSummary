/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "turbulenceProperties.H"
#include "Time.H"
#include "Ostream.H"

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
    os.writeEntry(" Flow", simulationType);
    return;
  }

  // a temporary word variable
  Foam::word tempWord {};

  // display the turbulent flow
  tempWord = "turbulent " + simulationType;
  os.writeEntry(" Flow", tempWord);

  // get the model type sub-dict as a unique pointer
  std::unique_ptr<Foam::dictionary> modelDict {new Foam::dictionary {turbulenceProperties_.findDict(simulationType)}};

  if (!modelDict) return; // if there is no model sub dictionary leave it

  os.writeEntry("  Turbulence", modelDict->getOrDefault<word>("turbulence", "Warning: missing turbulence keyword in turbulenceProperties"));
  if (modelDict->readIfPresent("printCoeffs", tempWord))
    os.writeEntry("  Print coeffs", tempWord);

  // display the model type
  tempWord = simulationType + "Model";
  if (modelDict->found(tempWord))
    os.writeEntry("  Model", modelDict->get<word>(tempWord));

  // get the model coeff dict as a unique pointer
  tempWord += "Coeffs";
  std::unique_ptr<Foam::dictionary> modelCoeffs {new Foam::dictionary {modelDict->findDict(tempWord)}};
  if (!modelCoeffs) return; // if there is no model coeffs sub dictionary leave it

  os << "  Model coeffs:" << Foam::endl;
  os.writeEntry("  Model coeffs", modelCoeffs->name());

}
