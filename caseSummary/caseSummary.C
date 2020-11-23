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

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "argList.H"
//#include "profiling.H"
#include "Time.H"
#include "Fstream.H"
#include "etcFiles.H"
//#include "includeEntry.H"

#include "cpuInfo.H"
#include "IOstreams.H"

using namespace Foam;

//using namespace std;

void initials()
{
  Info<< "|------------------------------------------------------------------|\nPHYSICS - INITIAL CONDITIONS\n" << endl;
  Info<< nl << "Initial Pressure: " << endl;
}

int main(int argc, char *argv[])
{
  argList::addNote("Display OpenFOAM case settings and configuration");

  argList::noBanner();
  argList::noParallel();
  argList::noMandatoryArgs();

  //argList args(argc, argv);

  Info<< "|------------------------------------------------------------------|\n" << endl;
  cpuInfo().write(Info);

  #include "setRootCase.H"
  //#include "createTime.H"
  {
    const fileName inputFile
    {
      // etc/controlDict file is mandatory in every distribution
      findEtcFile("controlDict", true, 0007)
    };

    Info<< nl << "Test getLine" << nl << inputFile << nl;
  }

  initials();
  Info<< "\nEnd\n" << endl;
}
