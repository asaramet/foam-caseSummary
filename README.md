# OpenFOAM utility to display Foam case structure and configuration.

The application is developed under the OpenFOAM Project. It may be compiled with any OpenFOAM version and used to display some OpenFOAM case structure configuration and additional info.  

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
