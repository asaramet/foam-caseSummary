/*---------------------------------------------------------------------------*\

Class
  Foam::extraFields

Description
  Class to get the pre-defined extra fields

\*---------------------------------------------------------------------------*/
#ifndef EXTRA_FIELDS_H
#define EXTRA_FIELDS_H

#include "UniformDimensionedField.H"

namespace Foam
{
  // dummy
  class Time;
  class Ostream;

/*---------------------------------------------------------------------------*\
                      Class extraFields Declaration
\*---------------------------------------------------------------------------*/

class extraFields
{
  // Private data

  //- g vector from constant/g dictionary
  const UniformDimensionedField<vector> g_;

public:

  // Overided Constructors
  extraFields(const Time& runTime);

  extraFields(const extraFields& other) = default;
  extraFields(extraFields&& other) = default;

  // Destructor
  ~extraFields() = default;

  // Default operators
  extraFields& operator=(const extraFields& other) = default;
  extraFields& operator=(extraFields&& other) = default;

  // Public member functions

  // Display data
  void write(Ostream &os) const;
};


} // End namespace Foam

#endif // EXTRA_FIELDS_H
