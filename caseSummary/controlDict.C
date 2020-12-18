/*---------------------------------------------------------------------------*\

\*---------------------------------------------------------------------------*/

#include "Time.H"
#include "Ostream.H"

#include "controlDict.H"

// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

Foam::controlDict::controlDict(const Foam::Time& runTime)
:
  runTime_ { runTime }
{}

// * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * * * //

void Foam::controlDict::write(Foam::Ostream& os) const
{

  // temporary objects for collecting and proovig if data exists
  word tempWord;
  scalar tempScalar;

  // display solver name
  if (controlDict_.readIfPresent("application", tempWord))
    os.writeEntry("Solver", tempWord);
  else
    os << "\nWarning: missing 'application' in 'controlDict'\n";
  os << endl;

  // display run time control settings
  if (controlDict_.readIfPresent("startTime", tempScalar))
  {
    os.writeEntry("Start time", tempScalar);
  }

  os.writeEntry("Start from", runTime_.startTimeIndex());

  // display stop criteria
  //- get the stopAt flag from 0 to 4
  const Time::stopAtControls stopAtIndex {runTime_.stopAt()};

  //- define the array of stopAt indexed values
  const word stopAtValues [5] {
    "when reaching prescribed end time",
    "immediattly without writing",
    "immediattly with writing",
    "at the next data interval",
    "Unknown"
  };

  // display end time if mentioned
  if (controlDict_.readIfPresent("endTime", tempScalar))
    os.writeEntry("End time", runTime_.endTime().value());

  os.writeEntry("Time step", runTime_.deltaT().value());

  //- display the corresponding value
  os.writeEntry("Stop", stopAtValues[stopAtIndex]);

  // display transient simulation controls if any
  if (controlDict_.readIfPresent("adjustTimeStep", tempWord))
  {
    os << endl;
    os << "Transient simulation control:" << endl;
    os << " ";
    os.writeEntry("Adjust T step", tempWord);
  }
  if (controlDict_.readIfPresent("maxCo", tempScalar))
  {
    os << " ";
    os.writeEntry("Max Courant nr", tempScalar);
  }
  if (controlDict_.readIfPresent("maxDeltaT", tempScalar))
  {
    os << " ";
    os.writeEntry("Max time step", tempScalar);
  }

  os << endl;
  // display write settings
  os << "Write settings:" << endl;
  if (controlDict_.readIfPresent("writeControl", tempWord))
  {
    os << " ";
    os.writeEntry("Control", tempWord);
  }
  if (controlDict_.readIfPresent("writeInterval", tempScalar))
  {
    os << " ";
    os.writeEntry("Interval", tempScalar);
  }
  if (controlDict_.readIfPresent("writeFormat", tempWord))
  {
    os << " ";
    os.writeEntry("Data format", tempWord);
  }
  if (controlDict_.readIfPresent("writePrecision", tempScalar))
  {
    os << " ";
    os.writeEntry("Precision", tempScalar);
  }
  if (controlDict_.readIfPresent("purgeWrite", tempScalar))
  {
    os << " ";
    os.writeEntry("Store folders", tempScalar);
  }
  if (controlDict_.readIfPresent("writeCompression", tempWord))
  {
    os << " ";
    os.writeEntry("Compression", tempWord);
  }
  if (controlDict_.readIfPresent("timeFormat", tempWord))
  {
    os << " ";
    os.writeEntry("Naming format", tempWord);
  }
  if (controlDict_.readIfPresent("timePrecision", tempScalar))
  {
    os << " ";
    os.writeEntry("Naming prec", tempScalar);
  }
  if (controlDict_.readIfPresent("graphFormat", tempWord))
  {
    os << " ";
    os.writeEntry("Graph data", tempWord);
  }

  // display data reading
  if (controlDict_.readIfPresent("runTimeModifiable", tempWord))
  {
    os << endl;
    os << "Data reading:" << endl;
    os << " ";
    os.writeEntry("Re-read dicts", tempWord);
  }
}
