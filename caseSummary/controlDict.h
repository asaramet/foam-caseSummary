/*---------------------------------------------------------------------------*\

Class
  Foam::controlDict

Description
  Class to collect simulation data from system/controlDict

\*---------------------------------------------------------------------------*/
#include "dictionary.H"

namespace Foam
{
  // dummy
  class Time;

/*---------------------------------------------------------------------------*\
                      Class controlDict Declaration
\*---------------------------------------------------------------------------*/

class controlDict
{
  // Private data

  //- system/controlDict dictionary
  const dictionary controlDict_;
public:

  // Constructors
  controlDict(const Time& runTime);

  controlDict(const controlDict& other) = default;
  controlDict(controlDict&& other) = default;

  // Destructor
  ~controlDict() = default;

  // Default operators
  controlDict& operator=(const controlDict& other) = default;
  controlDict& operator=(controlDict&& other) = default;

  // Public member functions

  // Display data
  void write(Ostream &os) const;
};


} // End namespace Foam
