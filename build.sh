echo "***************************** COMPILING JAGUAR SDK *****************************"

echo "*** Setting up environment variables"
SCRIPT="${BASH_SOURCE[0]}"
JAGSDK="`dirname "${SCRIPT}"`"
JAGSDK="`readlink -f "${JAGSDK}"`"
export JAGSDK

echo "*** Setting up Jaguar SDK paths using: ${JAGSDK}"

echo "*** Setting up compilation paths"
export RDBRC="${JAGSDK}/sdk/bin/rdb.rc"
export DBPATH="${JAGSDK}/sdk/bin"
export ALNPATH="${JAGSDK}/sdk/bin"
export RMACPATH="${JAGSDK}/sdk/include;${JAGSDK}/sdk/skunk/include"
export MACPATH="${JAGSDK}/sdk/include;${JAGSDK}/sdk/skunk/include"
export PATH="${JAGSDK}/tools/bin:${JAGSDK}/sdk/bin/linux:${PATH}"
export PYTHONPATH="${JAGSDK}/tools/lib/python:${PYTHONPATH}"

#echo $(echo "$2" | sed 's|\\|/|g') | awk -F'/' '{print $(NF-1)"/"$NF}'
project=$(echo $(echo "$2" | sed 's|\\|/|g') | awk -F'/' '{print $(NF-1)"/"$NF}')
projectshort=$(basename $(echo "$2" | sed 's|\\|/|g'))

#================================
#          CLEAN COMMAND
#================================
if [ "${1:-0}" == 'clean' ]; 
then
echo "*** Cleaning Project ${project}"

if [ -z "${project}" ];
then
echo "*** Error: project name not defined"
else

JAGFOLDER="${JAGSDK}/${project}"
make clean -C ${JAGFOLDER}

fi

#================================
# 			MAKE COMMAND
#================================
elif [ "${1:-0}" == 'make' ];
then
echo "*** Compiling Project ${project}"

if [ -z "${project}" ];
then
echo "*** Error: project name not defined"
else

if [ -z "${3}" ]; 
then PROJECTNAME=${projectshort}; 
else PROJECTNAME=${3};
fi

JAGFOLDER="${JAGSDK}/${project}"
JAGROM="${PROJECTNAME}.cof"
JAGWIN="/mnt/c/Projects/Jaguar/roms/dev"
JAGWIN2="/mnt/c/Projects/Jaguar/roms/homebrews/"

# Actually compiling
make --silent -B -C ${JAGFOLDER}

echo "*** Copying rom file to ${JAGWIN}"
mkdir -p ${JAGWIN}
cp "${JAGFOLDER}/${JAGROM}" ${JAGWIN}

echo "*** Copying rom file to ${JAGWIN2}"
mkdir -p ${JAGWIN2}
cp ${JAGFOLDER}/${JAGROM} ${JAGWIN2}

echo "*** Compilation over!"

fi

#================================
# 		UNKNOWN COMMAND
#================================
else
echo "*** Unknown Command: ${1}"
fi

read -p "************************** PRESS ANY KEY TO CONTINUE ***************************"
