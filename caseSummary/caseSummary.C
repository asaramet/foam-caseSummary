 /*---------------------------------------------------------------------------*\
 Application
     caseSummary

 Description
     Display OpenFOAM case settings and configuration

 Usage
     \b foamDictionary [OPTION] dictionary

       - \par -entry <name>
         Selects an entry

       - \par -keywords
         Prints the keywords (of the selected entry or of the top level if
         no entry was selected

       - \par -add <value>
         Adds the entry (should not exist yet)

       - \par -set <value>
         Adds or replaces the entry

       - \par -remove
         Remove the selected entry

 \*---------------------------------------------------------------------------*/
#include <cctype>
#include "argList.H"
#include "etcFiles.H"
#include "cpuInfo.H"
//#include "IOstream.H"     // iostream
#include "Ostream.H"        // ostream
#include "IOmanip.H"        // iomanip
//#include "profiling.H"
//#include "Time.H"
//#include "Fstream.H"
//#include "includeEntry.H"
//#include "IOstreams.H"
#include <string>

#include "caseSummary.H"

int main(int argc, char *argv[])
{
  Foam::argList::addNote("Display OpenFOAM case settings and configuration");

  Foam::argList::noBanner();
  Foam::argList::noParallel();
  Foam::argList::noMandatoryArgs();

  //argList args(argc, argv);

  #include "setRootCase.H"
  //#include "createTime.H"
  {
    const Foam::fileName inputFile
    {
      // etc/controlDict file is mandatory in every distribution
      Foam::findEtcFile("controlDict", true, 0007)
    };

    Foam::Info << Foam::nl << "Test getLine" << Foam::nl << inputFile << Foam::nl;
  }

  Foam::CaseSummary caseSummary {};

  caseSummary.systemInfo(Foam::Info);
  caseSummary.initials(Foam::Info);

  Foam::Info << "\nEnd\n" << Foam::endl;
}

void Foam::CaseSummary::delimiter(Foam::Ostream &os) const
{
  os << Foam::setw(120) << Foam::setfill('-') << Foam::endl;
}

void Foam::CaseSummary::title(Foam::string title, Foam::Ostream& os = Foam::Info) const
{
  for (char &letter:title)
    letter = std::toupper(letter);
  os << Foam::nl << Foam::setw(10) << Foam::setfill(' ')
     << title << Foam::nl << Foam::endl;
}

void Foam::CaseSummary::systemInfo(Foam::Ostream &os) const
{
  title("System Information");
  Foam::cpuInfo().write(Foam::Info);
  delimiter(os);
}

void Foam::CaseSummary::initials(Foam::Ostream &os) const
{
  title("Phisics - initial conditions");
  //Foam::Info << Foam::nl << "Initial Pressure: " << Foam::endl;
  delimiter(os);
}
