/*---------------------------------------------------------------------------*\

Class
  Foam::controlDict

Description
  Class to collect simulation data from system/controlDict

\*---------------------------------------------------------------------------*/
#include "dictionary.H"
#include "Time.H"

namespace Foam
{
  // dummy
  //class Time;

/*---------------------------------------------------------------------------*\
                      Class controlDict Declaration
\*---------------------------------------------------------------------------*/

class controlDict
{
  // Private data

  //- case Time Object
  const Time& runTime_;

  //- system/controlDict dictionary
  const dictionary controlDict_ { runTime_.controlDict() };
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

  // TODO: display run-time loadable functionality i.e:
  //- TODO: read 'functions' from controlDict
  //- TODO: read 'libs' from controlDict
};


} // End namespace Foam
