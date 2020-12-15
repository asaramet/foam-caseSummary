/*---------------------------------------------------------------------------*\

Class
  Foam::turbulenceProperties

Description
  Class to collect simulation data from constant/turbulenceProperties

\*---------------------------------------------------------------------------*/
#ifndef TURBULENCEPROPERTIES_H
#define TURBULENCEPROPERTIES_H

#include "IOdictionary.H"

namespace Foam
{
  // dummy
  class Time;

/*---------------------------------------------------------------------------*\
                      Class turbulenceProperties Declaration
\*---------------------------------------------------------------------------*/

class turbulenceProperties
{
  // Private data

  //- constant/turbulenceProperties dictionary
  const IOdictionary turbulenceProperties_;
public:

  // Overided Constructors
  turbulenceProperties(const Time& runTime);
  turbulenceProperties(const Time& runTime, const word& regionName);

  turbulenceProperties(const turbulenceProperties& other) = default;
  turbulenceProperties(turbulenceProperties&& other) = default;

  // Destructor
  ~turbulenceProperties() = default;

  // Default operators
  turbulenceProperties& operator=(const turbulenceProperties& other) = default;
  turbulenceProperties& operator=(turbulenceProperties&& other) = default;

  // Public member functions

  // Display data
  void write(Ostream &os) const;
};


} // End namespace Foam

#endif // TURBULENCEPROPERTIES_H
