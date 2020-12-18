/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "Ostream.H"

#include "helperFunctions.H"
#include "dictionaryEntry.H"

void Foam::writeDicts_(Foam::Ostream& os, Foam::dictionary& mainDict, Foam::word title_displacement, int step)
{
  // stop if dictionary is empty
  if (mainDict.empty())
    return;

  // get the dictionary table of contents
  Foam::wordList toc_ {mainDict.toc()};

  // upgrade recursive step
  step += 1;

  // set displacement
  if (step > 1)
    title_displacement += " ";

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
      writeDicts_(os, *dictPtr_, title_displacement, step);
    }
  } // end forAll
}
