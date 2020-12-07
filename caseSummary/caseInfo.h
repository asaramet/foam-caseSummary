/*---------------------------------------------------------------------------*\

Copyright (C) 2015 OpenFOAM Foundation
Copyright (C) 2018 OpenCFD Ltd.

Source: https://www.openfoam.com/documentation/guides/latest/api/
or: applications/utilities/preProcessing/createZeroDictionary/caseInfo.H

License
   This file is part of OpenFOAM.

   OpenFOAM is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.

   You should have received a copy of the GNU General Public License
   along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
  Foam::caseInfo

Description
  Class to hold information related to the simulation case.

\*---------------------------------------------------------------------------*/

#ifndef caseInfo_H
#define caseInfo_H

#include "wordList.H"
#include "wordRes.H"
#include "IOdictionary.H"
#include "boundaryInfo.H"

namespace Foam
{
  // dummy
  class Time;

/*---------------------------------------------------------------------------*\
                      Class boundaryInfo Declaration
\*---------------------------------------------------------------------------*/

class caseInfo
{
  // Private data

  //- Properties dictionary
  IOdictionary properties_;

  //- Mesh boundary information (read from mesh boundary file)
  boundaryInfo boundaryInfo_;

  //- Boundary condition dictionary
  const dictionary& bcDict_;

  //- List of condition names
  wordList conditionNames_;

  // Per-condition information

  //- List of patch names
  List<wordRes> patchNames_;

  //- Patch category
  wordList patchCategories_;

  //- Patch type
  wordList patchTypes_;

  // Private member functions

  //- Update the polyMesh boundary info, based on the patch categories
  void updateGeometricBoundaryField();

public:
  // Constructors
  caseInfo(const Time& runTime, const word& regionName);

  // Public member functions

  //- Return the condition ID for a boundary patch
  label findPatchConditionID(const label patchI, const word& patchName) const;

  //- Return the list of patch names
  const List<wordRes>& patchNames() const;

  //- Return the condition name for patch with index patchI
  const word& conditionName(const label patchI) const;

  //- Return the category name for patch with index patchI
  const word& patchCategory(const label patchI) const;

  //- Return the type name for patch with index patchI
  const word& patchType(const label patchI) const;

}; // End class caseInfo

} // End namespace Foam

#endif // caseInfo_H
