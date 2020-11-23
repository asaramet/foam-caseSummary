#!/usr/bin/env bash

: << 'END'
  This script will bild a new clean OpenFOAM sandbox to be able to create and test your
  OpenFOAM code on your working machine. If you have OpenFOAM installed on your machine,
  you may just use it directly working with user defined 'wmake', 'wclean' etc.

  To build an OF sandbox with this script you'll need:

    1. OpenFOAM >= v1912 source code to build the sandbox from, with the path set in "OF_SOURCE_FOLDER" variable.

END

OF_VERSION="v2006"
MD="`dirname $(readlink -f ${0})`/.."
OF_SOURCE_FOLDER="${MD}/../OpenFOAM-${OF_VERSION}"

[[ ! -d ${OF_SOURCE_FOLDER} ]] &&
echo "Error: Source folder: ${OF_SOURCE_FOLDER} doesn't exist!" &&
exit 1;

BUILD_FOLDER="${MD}/OpenFOAM-src"
[[ ! -d ${BUILD_FOLDER} ]] && mkdir -p ${BUILD_FOLDER}

copy_data()
{
  cp -rf ${OF_SOURCE_FOLDER}/{META-INFO,Allwmake,wmake} ${BUILD_FOLDER}
  sed -i s:"^applications/Allwmake":"#applications/Allwmake":g ${BUILD_FOLDER}/Allwmake

  bin_folder="${BUILD_FOLDER}/bin"
  [[ ! -d ${bin_folder:?} ]] && mkdir -p ${bin_folder}
  cp -f ${OF_SOURCE_FOLDER}/bin/{foamCleanPath,foamEtcFile} ${bin_folder:?}

  etc_folder="${BUILD_FOLDER}/etc"
  [[ ! -d ${etc_folder} ]] && mkdir -p ${etc_folder}
  cp -f ${OF_SOURCE_FOLDER}/etc/controlDict ${etc_folder}

  config_folder="${BUILD_FOLDER}/etc/config.sh"
  [[ ! -d ${config_folder:?} ]] && mkdir -p ${config_folder}
  cp -f ${OF_SOURCE_FOLDER}/etc/config.sh/{functions,settings,setup} ${config_folder:?}

  src_folder="${BUILD_FOLDER}/src"
  [[ ! -d ${src_folder} ]] && mkdir -p ${src_folder}
  cp -rf ${OF_SOURCE_FOLDER}/src/{OpenFOAM,OSspecific,Pstream} ${src_folder}
}

create_bashrc()
{
  [[ ! -d "${BUILD_FOLDER}/etc" ]] && mkdir -p "${BUILD_FOLDER}/etc"
  bashrc_file="${BUILD_FOLDER}/etc/bashrc"

  cp -f ${OF_SOURCE_FOLDER}/etc/bashrc ${bashrc_file}

  sed -i s:"^projectDir=\"\${BASH_SOURCE.*$:SCRIPT_DIR=\"\$( cd \"\$( dirname \"\${BASH_SOURCE[0]}\" )\" >/dev/null 2>\&1 \&\& pwd )\"":g ${bashrc_file}
  sed -i s:"^projectDir=\"\$HOME.*$:projectDir=\"\$(dirname \${SCRIPT_DIR})\"":g ${bashrc_file}
}

print_src_Allwmake()
{
  cat << EOF
#!/bin/sh
# Run from OPENFOAM src/ directory only
cd "\${0%/*}" || exit
wmakeCheckPwd "\$WM_PROJECT_DIR/src" 2>/dev/null || {
    echo "Error (\${0##*/}) : not located in \$WM_PROJECT_DIR/src"
    echo "    Check your OpenFOAM environment and installation"
    exit 1
}
[ -d "\$WM_PROJECT_DIR" -a -f "\$WM_PROJECT_DIR/etc/bashrc" ] || {
    echo "Error (\${0##*/}) : WM_PROJECT_DIR appears to be incorrect"
    echo "    Check your OpenFOAM environment and installation"
    exit 1
}

. "\$WM_PROJECT_DIR"/wmake/scripts/AllwmakeParseArguments

#------------------------------------------------------------------------------

wmakeLnInclude -u OpenFOAM
wmakeLnInclude -u OSspecific/"\${WM_OSTYPE:-POSIX}"

OSspecific/"\${WM_OSTYPE:-POSIX}"/Allwmake \$targetType \$*

Pstream/Allwmake \$targetType \$*

# Update version info (as required)
OpenFOAM/Alltouch -check 2>/dev/null

wmake \$targetType OpenFOAM
EOF
}

copy_data
create_bashrc
print_src_Allwmake > "${BUILD_FOLDER}/src/Allwmake"
chmod u+x ${BUILD_FOLDER}/src/Allwmake
