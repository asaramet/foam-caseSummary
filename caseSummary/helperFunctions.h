/*---------------------------------------------------------------------------*\

Functions
  Foam::writeDicts_

Description
  Functions used in multiple instances

\*---------------------------------------------------------------------------*/
#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

namespace Foam
{
  // dummy
  class Ostream;

/*---------------------------------------------------------------------------*\
                      Functions Declaration
\*---------------------------------------------------------------------------*/


  // recursivley display a dictionary data
  void writeDicts_(Ostream& os, dictionary& mainDict, word displacement = "", int step = 0);


} // End namespace Foam

#endif // HELPERFUNCTIONS_H
