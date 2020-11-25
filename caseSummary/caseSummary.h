#ifndef _CASESUMMARY_H_

namespace Foam
{
  /*---------------------------------------------*\
          class CaseSummary Declaration
  \*---------------------------------------------*/
  class CaseSummary
  {
    // Private Member Functions

    //- Section/paragraph delimiter
    void delimiter(Ostream &os) const;

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
    void systemInfo(Ostream &os) const;

    //- Display initial conditions
    void initials(Ostream &os) const;

  };

  //extern CaseSummary caseSummary;

} // End namespace Foam

#endif // _CASESUMMARY_H_
