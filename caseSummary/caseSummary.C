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
#include "cpuInfo.H"
#include "etcFiles.H"
//#include "IOstream.H"     // iostream
#include "Ostream.H"        // ostream
#include "IOmanip.H"        // iomanip
//#include "profiling.H"
//#include "Time.H"
//#include "Fstream.H"
//#include "includeEntry.H"
//#include "IOstreams.H"

#include "caseSummary.H"

int main(int argc, char *argv[])
{
  // Manage command arguments
  //- add short description
  Foam::argList::addNote("Display OpenFOAM case settings and configuration");

  //- do not emit the banner information
  Foam::argList::noBanner();

  //- disable parallel options
  Foam::argList::noParallel();

  //- flag command arguments as being optional
  Foam::argList::noMandatoryArgs();

  //- add options (command arguments)
  Foam::argList::addBoolOption("cpu", "Display system's CPU information");
  Foam::argList::addBoolOption("initials", "Display initial conditions only");

  // Create an argList Object ("setRootCase.H")
  Foam::argList args(argc, argv);
  // Check root path and case path
  if (!args.checkRootCase())
    Foam::FatalError.exit();

  //#include "createTime.H"
  {
    const Foam::fileName inputFile
    {
      // etc/controlDict file is mandatory in every distribution
      Foam::findEtcFile("controlDict", true, 0007)
    };

    Foam::Info << Foam::nl << "Test getLine" << Foam::nl << inputFile << Foam::nl;
  }

  // Crate a CaseSummary object
  Foam::CaseSummary caseSummary {};

  // Display initial conditions only
  if (args.found("initials"))
    caseSummary.initials(Foam::Info);

  // Display cpu info
  if (args.found("cpu"))
    caseSummary.cpuInfo(Foam::Info);

  // Default display (no specific options provided)
  if (args.options().empty())
    caseSummary.all(Foam::Info);

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

void Foam::CaseSummary::cpuInfo(Foam::Ostream &os) const
{
  title("System CPU Information");
  Foam::cpuInfo().write(Foam::Info);
  delimiter(os);
}

void Foam::CaseSummary::initials(Foam::Ostream &os) const
{
  title("Phisics - initial conditions");
  //Foam::Info << Foam::nl << "Initial Pressure: " << Foam::endl;
  delimiter(os);
}

void Foam::CaseSummary::all(Foam::Ostream &os) const
{
  cpuInfo(os);
  initials(os);
}
