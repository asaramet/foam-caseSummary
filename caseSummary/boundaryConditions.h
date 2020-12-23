/*---------------------------------------------------------------------------*\

Class
  Foam::boundaryConditions

Description
  Class to collect boundary and initial conditions

\*---------------------------------------------------------------------------*/
#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include "word.H"
#include "fvMesh.H"

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

  //- region name, default is 'region0'
  const word regionName_;

public:

  // Overided Constructors (fvMesh::defaultRegion ~= "region0")
  boundaryConditions(const Time& runTime, const word& regionName = fvMesh::defaultRegion);

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
