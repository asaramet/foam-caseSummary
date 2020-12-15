/*---------------------------------------------------------------------------*\

Class
  Foam::multiRegionProperties

Description
  Class to collect region information usually must have constant/regionProperties dict

\*---------------------------------------------------------------------------*/
#ifndef MULTIREGIONPROPERIES_H
#define MULTIREGIONPROPERIES_H

#include "regionProperties.H"

namespace Foam
{
  // dummy
  class Time;

/*---------------------------------------------------------------------------*\
                      Class multiRegionProperties Declaration
\*---------------------------------------------------------------------------*/

class multiRegionProperties
{
  // Private data

  // - run Time Object
  const Foam::Time& runTime_;

  //- regionProperties Object to read data from
  regionProperties regionProperties_;

  //- total count of all region names
  Foam::label count_;

  //- list of names
  Foam::wordList names_;

public:

  // Constructors
  multiRegionProperties(const Time& runTime);

  multiRegionProperties(const multiRegionProperties& other) = default;
  multiRegionProperties(multiRegionProperties&& other) = default;

  // Destructor
  ~multiRegionProperties() = default;

  // Default operators
  multiRegionProperties& operator=(const multiRegionProperties& other) = default;
  multiRegionProperties& operator=(multiRegionProperties&& other) = default;

  // Public member functions

  // Display data
  void write(Ostream &os) const;
};

} // End namespace Foam

#endif // MULTIREGIONPROPERIES_H
