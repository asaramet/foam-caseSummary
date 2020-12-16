/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "turbulenceProperties.H"
#include "Time.H"
#include "Ostream.H"
#include "dictionaryEntry.H"

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

  // display flow type
  os << " ";
  os.writeEntry("Flow", simulationType);

  // get the model type sub-dict as a unique pointer
  std::unique_ptr<Foam::dictionary> modelDict {new Foam::dictionary {turbulenceProperties_.findDict(simulationType)}};

  if (modelDict->empty()) return; // if there is no model sub dictionary leave it

  Foam::wordList toc_ {modelDict->toc()};

  writeDicts(os, *modelDict);
  //modelDict->writeEntries(os);

} // end write(os&)

void Foam::turbulenceProperties::writeDicts(Foam::Ostream& os, Foam::dictionary& mainDict, Foam::word title_displacement) const
{
  // stop if dictionary is empty
  if (mainDict.empty())
    return;

  // set displacement
  title_displacement += " ";

  // get the dictionary table of contents
  Foam::wordList toc_ {mainDict.toc()};

  // loop through contents and display them
  forAll(toc_, id)
  {
    // create a pointer to dictionary entry (it's freed by default in Destructor)
    Foam::entry* subEntry {mainDict.findEntry(toc_[id])};

    // write entry data if it's not a sub-dictionary
    if (subEntry->isStream())
    {
      // get entry keyword and save as title
      Foam::word keyword_ {subEntry->keyword()};

      os << title_displacement;
      subEntry->write(os);
    }

    // recursivley process it again if it's a sub-dictionary
    if (subEntry->isDict())
    {
      os << title_displacement << toc_[id] << Foam::endl;
      Foam::dictionary* dictPtr_ {subEntry->dictPtr()};
      writeDicts(os, *dictPtr_, title_displacement);
    }
  }
}
