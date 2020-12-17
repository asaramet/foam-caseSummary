/*---------------------------------------------------------------------------*\

Functions
  Foam::writeDicts_

Description
  Functions used in multiple instances

\*---------------------------------------------------------------------------*/
#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "IOdictionary.H"
#include "Ostream.H"

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Functions Declaration
\*---------------------------------------------------------------------------*/


  // recursivley display a dictionary data
  void writeDicts_(Ostream& os, dictionary& mainDict, word displacement = "");


} // End namespace Foam

#endif // HELPERFUNCTIONS_H
