/*---------------------------------------------------------------------------*\

Class
  Foam::transportProperties

Description
  Class to collect simulation data from constant/transportProperties

\*---------------------------------------------------------------------------*/
#ifndef TRANSPORT_PROPERTIES_H
#define TRANSPORT_PROPERTIES_H

#include "IOdictionary.H"

namespace Foam
{
  // dummy
  class Time;

/*---------------------------------------------------------------------------*\
                      Class transportProperties Declaration
\*---------------------------------------------------------------------------*/

class transportProperties
{
  // Private data

  //- constant/transportProperties dictionary
  const IOdictionary transportProperties_;

public:

  // Overided Constructors
  transportProperties(const Time& runTime);
  transportProperties(const Time& runTime, const word& regionName);

  transportProperties(const transportProperties& other) = default;
  transportProperties(transportProperties&& other) = default;

  // Destructor
  ~transportProperties() = default;

  // Default operators
  transportProperties& operator=(const transportProperties& other) = default;
  transportProperties& operator=(transportProperties&& other) = default;

  // Public member functions

  // Display data
  void write(Ostream &os) const;
};


} // End namespace Foam

#endif // TRANSPORT_PROPERTIES_H
