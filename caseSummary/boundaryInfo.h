/*---------------------------------------------------------------------------*\

Copyright (C) 2015 OpenFOAM Foundation
Copyright (C) 2018 OpenCFD Ltd.

Source: https://www.openfoam.com/documentation/guides/latest/api/
or: applications/utilities/preProcessing/createZeroDictionary/boundaryInfo.H

Class
  Foam::boundaryInfo

Description
  Class to provide mesh patching information from polyMesh/boundary.

\*---------------------------------------------------------------------------*/

#ifndef boundaryInfo_H
#define boundaryInfo_H

#include "IOPtrList.H" // PtrList of objects of a certian type T
#include "entry.H"
#include "wordList.H"
#include "boolList.H"
#include "HashSet.H"

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class boundaryInfo Declaration
\*---------------------------------------------------------------------------*/

class boundaryInfo
{
  // Private data

  //- Boundary dictionary
  IOPtrList<entry> boundaryDict_;

  //- Patch names
  wordList names_;

  //- Patch types
  wordList types_;

  //- Constraint flag
  boolList constraint_;

  //- Groups per patch
  List<wordList> groups_;

  //- Set of all group names
  wordHashSet allGroupNames_;

  // Private member functions

  //- Read the boundary dict
  IOPtrList<entry> readBoundaryDict(const Time& runTime, const word& regionName) const;

public:

  // Constructors
  boundaryInfo(const Time& runTime, const word& regionName);

  // Copy and Move Constructors
  boundaryInfo(const boundaryInfo& other) = default;
  boundaryInfo(boundaryInfo&& other) = default;

  // Member Operators
  boundaryInfo& operator=(const boundaryInfo& other) = default;
  boundaryInfo& operator=(boundaryInfo&& other) = default;

  // Destructor
  ~boundaryInfo() = default;

  // Public member functions

  //- Patch names
  const wordList& names() const;

  //- Patch types
  const wordList& types() const;

  //- Constraint flag
  const boolList& constraint() const;

  //- Groups
  const List<wordList>& groups() const;

  //- Set of all group names
  const wordHashSet& allGroupNames() const;

  //- Set the patch type based on the condition
  void setType(const label patchI, const word& condition);

  //- Write the boundary dictionary
  void write() const;

}; // End boundaryInfo

} // End namespace Foam
#endif // boundaryInfo_H
