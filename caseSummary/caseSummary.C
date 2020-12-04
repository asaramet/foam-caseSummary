 /*---------------------------------------------------------------------------*\
 Application
     caseSummary

 Description
     Display OpenFOAM case settings and configuration

 Usage
     \b caseSummary [OPTIONS]

       - \par -system
         Display system information

       - \par -initials
         Display initial conditions only

       - \par
         Display all the data
 \*---------------------------------------------------------------------------*/
#include <cctype>
//#include <memory>

#include "cpuInfo.H"
#include "foamVersion.H"
#include "clock.H"

#include "Ostream.H"        // ostream
#include "IOmanip.H"        // iomanip
#include "Time.H"

#include "etcFiles.H"
//#include "IOstream.H"     // iostream
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
  Foam::argList::addBoolOption("system", "Display system information");
  Foam::argList::addBoolOption("general", "Display general case information");
  Foam::argList::addBoolOption("initials", "Display initial conditions only");

  // Create an argList Object ("setRootCase.H")
  Foam::argList args(argc, argv);
  // Check root path and case path
  if (!args.checkRootCase())
    Foam::FatalError.exit();

  //#include "createTime.H"
  {
    const Foam::fileName inputFile { Foam::findEtcFile("controlDict", true, 0007) };
    Foam::Info << Foam::nl << "Test getLine" << Foam::nl << inputFile << Foam::nl;
  }

  // Crate a CaseSummary object
  Foam::CaseSummary caseSummary {};

  // Default display (no specific options provided)
  if (args.options().empty())
    caseSummary.all(Foam::Info, args);

  // Display initial conditions only
  if (args.found("initials"))
    caseSummary.initials(Foam::Info, args);

  // Display cpu info
  if (args.found("system"))
    caseSummary.systemInfo(Foam::Info);

  // Display case info
  if (args.found("general"))
    caseSummary.generalInfo(Foam::Info, args);

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
  title("About");
  Foam::string of {"OpenFOAM-"};
  of += Foam::FOAMversion;
  os.writeEntry("Module", of);
  os.writeEntry("Build", Foam::FOAMbuild);
  os.writeEntry("Architecture", Foam::FOAMbuildArch);
  os.writeEntry("Current Time", Foam::clock::dateTime());

  title("System CPU Information");
  Foam::cpuInfo().write(os);

  delimiter(os);
}

void Foam::CaseSummary::initials(Foam::Ostream &os, const Foam::argList &args) const
{
  title("Phisics - initial conditions");

  // TODO
  Foam::Info << "Case Regions: \n i.e U, p, rho etc\n" << Foam::nl;
  Foam::Info << "Case Patches\n" << Foam::nl;
  Foam::Info << "Use IOobject ??\n" << Foam::nl;

  // create an unique pointer to the case endTime (using root/case path)
  std::unique_ptr<Foam::Time> zero_time { new Foam::Time(args.rootPath(), args.caseName()) };
  if (!zero_time) return;

  //auto obj = Foam::objectRegistry(*zero_time);
  //auto ioobj = IOobject()

  delimiter(os);

  //delete(zero_time);
}

void Foam::CaseSummary::generalInfo(Foam::Ostream &os, const Foam::argList &args) const
{
  title("Current Case");
  os.writeEntry("Case basename", args.caseName());
  os.writeEntry("Case root path", args.rootPath());

  delimiter(os);
}

void Foam::CaseSummary::all(Foam::Ostream &os, const Foam::argList &args) const
{
  systemInfo(os);
  generalInfo(os, args);
  initials(os, args);
}
