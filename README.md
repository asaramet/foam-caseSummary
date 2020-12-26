# OpenFOAM utility to display Foam case structure and configuration.

The application is developed under the OpenFOAM Project (https://openfoam.com/). It may be compiled with any OpenFOAM version and used to display some OpenFOAM case structure configuration and additional info.  

## About OpenFOAM

OpenFOAM is a free, open source CFD software that has a large user base across multiple areas of engineering and science. It has features to solve anything from complex fluid flows involving chemical reactions, turbulence and heat transfer to acoustics, solid mechanics and electromagnetism.  

## About caseSummary utility, developed here

OpenFOAM being a C++ open source software uses dictionaries in form of text files to provide solver specific data such as boundary and initial conditions, turbulence models, fluid properties, solver variables etc to OpenFOAM cases.

For a new user it may be challenging to understand how the cases are build, which data is already provided and need to be modified to let the solver properly run. Many times the user will have to look for an error or find out what's wrong with the case, by going through all the text dictionaries line by line.

'caseSummary' is developed to provide a quick view of the current OpenFOAM case structure and data through OpenFOAM'ish command lines. It uses standard OpenFOAM libraries, functions and objects.

## Useful websites

1. Official OpenFOAM ESI's webpage: https://openfoam.com/

2. OpenFOAM user guide: https://www.openfoam.com/documentation/guides/latest/doc/index.html

3. This project on GitHUB: https://github.com/asaramet/foam-caseSummary

## Installation

If you have OpenFOAM installed on your system, the utility will be installed as a user developed application in $FOAM_USER_APPBIN, once you compile it from 'caseSummary' folder with:

```
  cd caseSummary
  wmake
```

## Sandbox

It is possible to create a sandbox for testing or additional development.

1. Get the source code of any OpenFOAM on your machine. Although OpenFOAM versions grater or equal to v2006 are recommended.

2. Set the path to OpenFOAM source code as 'OF_SOURCE_FOLDER' variable in 'scripts.sh/build_sandbox.sh'.

3. Run the script
```
  ./scripts.sh/build_sandbox.sh
```

4. Compile created 'OpenFOAM-src'
```
  ./OpenFOAM-src/Allwmake -j
```

5. Source your OpenFOAM sandbox
```
  source OpenFOAM-src/etc/bashrc
```

**Note: To use your sandbox, it will have to first be sourced as shown in (5)**

## Requirements

To successfully compile OpenFOAM-src libraries you'll need:

- gcc compiler > 5.2.1
- OpenMPI library > 1.8.8  
- GNU m4
