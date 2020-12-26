/*---------------------------------------------------------------------------*\

Class
  Foam::caseSummary

Description
  Class to collect and display OpenFOAM case settings and configuration

\*---------------------------------------------------------------------------*/

#ifndef CASE_SUMMARY_H
#define CASE_SUMMARY_H

#include "argList.H"

namespace Foam
{
  /*---------------------------------------------*\
          class caseSummary Declaration
  \*---------------------------------------------*/
  class caseSummary
  {
    // Private consts
    static const size_t FIRST_COL_WIDTH {30};
    static const size_t SECOND_COL_WIDTH {40};
    // Private Member Functions

    //- Section/paragraph delimiter
    void delimiter(Ostream&) const;

  public:
    // Constructors
    caseSummary() = default;
    caseSummary(const caseSummary& other) = default;
    caseSummary(caseSummary&& other) = default;

    // Default Operators
    caseSummary& operator=(const caseSummary& other) = default;
    caseSummary& operator=(caseSummary&& other) = default;

    // Destructor
    ~caseSummary() = default;

    // Public Member Functions

    //- Display system/machine info
    void systemInfo(Ostream&) const;

    //- Display current case info
    void caseInfo(Ostream&, const argList&) const;

    //- Display initial conditions
    void initials(Ostream&, const Time&) const;

    //- Display phisics
    void phisics(Ostream&, const argList&, const Time&) const;

    //- Display solver information
    void solver(Ostream&, const Time&) const;

    //- Display everythig
    void all(Ostream &os, const argList&, const Time&) const;
  };

  //extern caseSummary caseSummary;

} // End namespace Foam

#endif // CASE_SUMMARY_H
