/*---------------------------------------------------------------------------*\

Class
  Foam::thermophysicalProperties

Description
  Class to collect simulation data from constant/thermophysicalProperties

\*---------------------------------------------------------------------------*/
#ifndef THERMOPHYSICAL_PROPERTIES_H
#define THERMOPHYSICAL_PROPERTIES_H

#include "IOdictionary.H"

namespace Foam
{
  // dummy
  class Time;

/*---------------------------------------------------------------------------*\
                      Class thermophysicalProperties Declaration
\*---------------------------------------------------------------------------*/

class thermophysicalProperties
{
  // Private data

  //- constant/thermophysicalProperties dictionary
  const IOdictionary thermophysicalProperties_;

public:

  // Overided Constructors
  thermophysicalProperties(const Time& runTime);
  thermophysicalProperties(const Time& runTime, const word& regionName);

  thermophysicalProperties(const thermophysicalProperties& other) = default;
  thermophysicalProperties(thermophysicalProperties&& other) = default;

  // Destructor
  ~thermophysicalProperties() = default;

  // Default operators
  thermophysicalProperties& operator=(const thermophysicalProperties& other) = default;
  thermophysicalProperties& operator=(thermophysicalProperties&& other) = default;

  // Public member functions

  // return true if thermophysicalProperties Object is available
  bool foundProperties(const word&);

  // Display data
  void write(Ostream &os) const;
};


} // End namespace Foam

#endif // THERMOPHYSICAL_PROPERTIES_H
