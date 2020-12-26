 /*---------------------------------------------------------------------------*\
 Application
     caseSummary

 Description
     Display OpenFOAM case settings and configuration

 Usage
     \b caseSummary [OPTIONS]

       - \par -system
         Display system information

       - \par -caseInfo
         Display case information

       - \par -phisics
         Display case phisics

       - \par -solver
         Display solver settings

       - \par -initials
         Display initial conditions

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
#include "IOdictionary.H"   // constructor from IOobject with readData/writeData functions
#include "timeSelector.H"   // list of scalarRange for selecting times

#include "helperFunctions.H"
#include "controlDict.H"
#include "turbulenceProperties.H"
#include "caseSummary.H"
#include "multiRegionProperties.H"
#include "transportProperties.H"
#include "thermophysicalProperties.H"
#include "extraFields.H"
#include "boundaryConditions.H"

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
  Foam::argList::addBoolOption("caseInfo", "Display case information");
  Foam::argList::addBoolOption("phisics", "Display case phisics");
  Foam::argList::addBoolOption("solver", "Display solver settings");
  Foam::argList::addBoolOption("initials", "Display initial conditions");
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

  // Display initial conditions
  if (args.found("initials"))
    caseSummary.initials(Foam::Info, runTime);

  // Display case physics
  if (args.found("phisics"))
    caseSummary.phisics(Foam::Info, args, runTime);

  // Display cpu info
  if (args.found("system"))
    caseSummary.systemInfo(Foam::Info);

  // Display case info
  if (args.found("caseInfo"))
    caseSummary.caseInfo(Foam::Info, args);

  // Display solver info
  if (args.found("solver"))
    caseSummary.solver(Foam::Info, runTime);

  Foam::Info << "\nEnd\n" << Foam::endl;
}

void Foam::caseSummary::delimiter(Foam::Ostream &os) const
{
  os << Foam::endl;
  os << Foam::setw(70) << Foam::setfill('-') << Foam::endl;
}

void Foam::caseSummary::systemInfo(Foam::Ostream &os) const
{
  Foam::title_("About", os);
  Foam::string of {"OpenFOAM-"};
  of += Foam::FOAMversion;
  os.writeEntry("Module", of);
  os.writeEntry("Build", Foam::FOAMbuild);
  os.writeEntry("Architecture", Foam::FOAMbuildArch);
  os.writeEntry("Current Time", Foam::clock::dateTime());

  Foam::title_("System CPU Information", os);
  Foam::cpuInfo().write(os);

  delimiter(os);
}

void Foam::caseSummary::initials(Foam::Ostream &os, const Foam::Time &runTime) const
{
  // display initial conditions
  if (Foam::fileHandler().isDir(runTime.timeName(0)))
  {
    Foam::title_("Phisics - initial conditions", os);
    Foam::boundaryConditions(runTime).write(os);
    delimiter(os);
  }
}

void Foam::caseSummary::phisics(Foam::Ostream &os, const Foam::argList &args, const Foam::Time &runTime) const
{
  // display turbulenceProperties data
  if (Foam::fileHandler().isFile(runTime.constant()/"turbulenceProperties"))
  {
    Foam::title_("Phisics - Turbulence Properties", os);
    Foam::turbulenceProperties(runTime).write(os);
    delimiter(os);
  }

  // display multi region turbulenceProperties data
  if (Foam::fileHandler().isFile(runTime.constant()/"regionProperties"))
  {
    Foam::title_("Phisics - Regions Turbulence Properties", os);
    Foam::multiRegionProperties(runTime).write(os);
    delimiter(os);
  }

  // display transport properties
  if (Foam::fileHandler().isFile(runTime.constant()/"transportProperties"))
  {
    Foam::title_("Phisics - Transport Properties", os);
    Foam::transportProperties(runTime).write(os);
    delimiter(os);
  }

  #if 0
  // display thermophysical properties
  if (Foam::fileHandler().isFile(runTime.constant()/"thermophysicalProperties"))
  {
    Foam::title_("Phisics - Thermophysical Properties", os);
    Foam::thermophysicalProperties(runTime).write(os);
    delimiter(os);
  }
  #endif

  // display gravity
  if (Foam::fileHandler().isFile(runTime.constant()/"g"))
  {
    Foam::title_("Phisics - Extra fields", os);
    Foam::extraFields(runTime).write(os);
    delimiter(os);
  }


}

void Foam::caseSummary::caseInfo(Foam::Ostream &os, const Foam::argList &args) const
{
  Foam::title_("Current Case", os);
  os.writeEntry("Case basename", args.caseName());
  os.writeEntry("Case root path", args.rootPath());

  delimiter(os);
}

void Foam::caseSummary::solver(Foam::Ostream &os, const Foam::Time &runTime) const
{
  Foam::title_("Solver settings", os);

  // write controlDict solver data
  Foam::controlDict(runTime).write(os);

  delimiter(os);
}

void Foam::caseSummary::all(Foam::Ostream &os, const Foam::argList &args, const Foam::Time &runTime) const
{
  systemInfo(os);
  caseInfo(os, args);
  initials(os, runTime);
  phisics(os, args, runTime);
  solver(os, runTime);
}
