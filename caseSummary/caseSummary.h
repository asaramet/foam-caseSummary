#ifndef _CASESUMMARY_H_

#include "argList.H"

namespace Foam
{
  /*---------------------------------------------*\
          class CaseSummary Declaration
  \*---------------------------------------------*/
  class CaseSummary
  {
    // Private consts
    static const size_t FIRST_COL_WIDTH {30};
    static const size_t SECOND_COL_WIDTH {40};
    // Private Member Functions

    //- Section/paragraph delimiter
    void delimiter(Ostream&) const;

    //- Section title
    void title(string, Ostream&) const;
  public:
    // Constructors
    CaseSummary() = default;
    CaseSummary(const CaseSummary& other) = default;
    CaseSummary(CaseSummary&& other) = default;

    // Default Operators
    CaseSummary& operator=(const CaseSummary& other) = default;
    CaseSummary& operator=(CaseSummary&& other) = default;

    // Destructor
    ~CaseSummary() = default;

    // Public Member Functions

    //- Display system/machine info
    void systemInfo(Ostream&) const;

    //- Display current case info
    void generalInfo(Ostream&, const argList&) const;

    //- Display initial conditions
    void initials(Ostream &os) const;

    //- Display everythig
    void all(Ostream &os, const argList&) const;
  };

  //extern CaseSummary caseSummary;

} // End namespace Foam

#endif // _CASESUMMARY_H_
