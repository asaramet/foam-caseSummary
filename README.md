# caseSummary

An OpenFOAM utility to display Foam case structure and configuration.

## Installation

If you have OpenFOAM installed on your system, the utility will be installed in $FOAM_USER_APPBIN, once you compile it from 'caseSummary' folder with:

```
  cd caseSummary
  wmake
```

To test the utility without installing OpenFOAM, you'll first have to compile base OpenFOAM libraries collected in 'OpenFOAM-src' folder from official [OpenFOAM v1912](https://openfoam.com) distribution.

To do so:

1. source the 'bashrc' file to set the required environment variables and paths.
```
  source OpenFOAM-src/etc/bashrc
```

2. Compile basic OpenFOAM libraries:
```
  ./OpenFOAM-src/Allwmake -j
```

3. Compile the utility
```
  cd caseSummary
  wmake
```

## Requirements

To successfully compile OpenFOAM-src libraries you'll need:

- gcc compiler > 5.2.1
- OpenMPI library > 1.8.8  
- GNU m4
