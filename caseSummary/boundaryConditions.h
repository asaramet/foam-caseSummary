/*---------------------------------------------------------------------------*\

Class
  Foam::boundaryConditions

Description
  Class to collect boundary and initial conditions

\*---------------------------------------------------------------------------*/
#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

namespace Foam
{
  // dummy
  class Time;
  class Ostream;

/*---------------------------------------------------------------------------*\
                      Class boundaryConditions Declaration
\*---------------------------------------------------------------------------*/

class boundaryConditions
{
  // Private data

  //- run Time object
  const Time& runTime_;

public:

  // Overided Constructors
  boundaryConditions(const Time& runTime);

  boundaryConditions(const boundaryConditions& other) = default;
  boundaryConditions(boundaryConditions&& other) = default;

  // Destructor
  ~boundaryConditions() = default;

  // Default operators
  boundaryConditions& operator=(const boundaryConditions& other) = default;
  boundaryConditions& operator=(boundaryConditions&& other) = default;

  // Public member functions

  // Display data
  void write(Ostream &os) const;
};


} // End namespace Foam

#endif // BOUNDARY_CONDITIONS_H
