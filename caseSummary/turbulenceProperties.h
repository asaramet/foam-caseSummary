/*---------------------------------------------------------------------------*\

Class
  Foam::turbulenceProperties

Description
  Class to collect simulation data from constant/turbulenceProperties

\*---------------------------------------------------------------------------*/
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

  // Constructors
  turbulenceProperties(const Time& runTime);

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
