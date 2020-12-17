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
#include "IOdictionary.H"   // constructor from IOobject with readData/writeData functions
#include "timeSelector.H"   // list of scalarRange for selecting times

#include "controlDict.H"
#include "turbulenceProperties.H"
#include "caseSummary.H"
#include "multiRegionProperties.H"
#include "transportProperties.H"

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
  Foam::argList::addBoolOption("solver", "Display solver settings");
  Foam::argList::addBoolOption("", "Display all collected information");

  // Create an argList Object ("setRootCase.H")
  const Foam::argList args(argc, argv);
  // Check root path and case path
  if (!args.checkRootCase())
    Foam::FatalError.exit();

  // select multiple times. First option adds explicitly -constant, second removes -withZero
  Foam::timeSelector::addOptions(true, false);

  // Create run Time Object from default controlDict ("createTime.H")
  Foam::Time runTime {Foam::Time::controlDictName, args};

  // Allow overwrite of times and set runTime to the first instance
  Foam::instantList times = Foam::timeSelector::selectIfPresent(runTime, args);

  // Crate a caseSummary object
  const Foam::caseSummary caseSummary {};

  // Default display (no specific options provided)
  if (args.options().empty())
    caseSummary.all(Foam::Info, args, runTime);

  // Display initial conditions only
  if (args.found("initials"))
    caseSummary.initials(Foam::Info, args);

  // Display cpu info
  if (args.found("system"))
    caseSummary.systemInfo(Foam::Info);

  // Display case info
  if (args.found("general"))
    caseSummary.generalInfo(Foam::Info, args);

  // Display solver info
  if (args.found("solver"))
    caseSummary.solver(Foam::Info, runTime);

  Foam::Info << "\nEnd\n" << Foam::endl;
}

void Foam::caseSummary::delimiter(Foam::Ostream &os) const
{
  os << Foam::setw(120) << Foam::setfill('-') << Foam::endl;
}

void Foam::caseSummary::title(Foam::string title, Foam::Ostream& os = Foam::Info) const
{
  for (char &letter:title)
    letter = std::toupper(letter);
  os << Foam::nl << Foam::setw(10) << Foam::setfill(' ')
     << title << Foam::nl << Foam::endl;
}

void Foam::caseSummary::systemInfo(Foam::Ostream &os) const
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

void Foam::caseSummary::initials(Foam::Ostream &os, const Foam::argList &args) const
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

void Foam::caseSummary::generalInfo(Foam::Ostream &os, const Foam::argList &args) const
{
  title("Current Case");
  os.writeEntry("Case basename", args.caseName());
  os.writeEntry("Case root path", args.rootPath());

  delimiter(os);
}

void Foam::caseSummary::solver(Foam::Ostream &os, const Foam::Time &runTime) const
{
  title("Solver settings");

  // write controlDict solver data
  Foam::controlDict(runTime).write(os);

  // write turbulenceProperties data
  if (Foam::fileHandler().isFile(runTime.constant()/"turbulenceProperties"))
  {
    os << "Turbulence properties:" << Foam::endl;
    Foam::turbulenceProperties(runTime).write(os);
    os << Foam::endl;
  }

  // write multi region turbulenceProperties data
  if (Foam::fileHandler().isFile(runTime.constant()/"regionProperties"))
  {
    os << "Defined regions:" << Foam::endl;
    Foam::multiRegionProperties(runTime).write(os);
  }

  if (Foam::fileHandler().isFile(runTime.constant()/"transportProperties"))
    Foam::transportProperties(runTime).write(os);

  delimiter(os);
}

void Foam::caseSummary::all(Foam::Ostream &os, const Foam::argList &args, const Foam::Time &runTime) const
{
  systemInfo(os);
  generalInfo(os, args);
  initials(os, args);
  solver(os, runTime);
}
