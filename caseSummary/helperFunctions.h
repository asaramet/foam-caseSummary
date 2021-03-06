/*---------------------------------------------------------------------------*\

Functions
  Foam::writeDicts_

Description
  Functions used in multiple instances

\*---------------------------------------------------------------------------*/
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

namespace Foam
{
  // dummy
  class Ostream;

/*---------------------------------------------------------------------------*\
                      Functions Declaration
\*---------------------------------------------------------------------------*/


  // recursivley display a dictionary data
  void writeDicts_(Ostream& os, dictionary& mainDict, word displacement = "", int step = 0);

  // display section title
  void title_(string, Ostream&);

  // check if file exists
  bool isFile_(const word&);

} // End namespace Foam

#endif // HELPER_FUNCTIONS_H
