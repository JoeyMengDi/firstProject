#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=arm-brcm-linux-gnueabi-gcc
CCC=arm-brcm-linux-gnueabi-g++
CXX=arm-brcm-linux-gnueabi-g++
FC=gfortran.exe
AS=as

# Macros
CND_PLATFORM=Gnueabi-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include NbMakefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/511dc4f5/DebugInfo.o \
	${OBJECTDIR}/appmain.o


# C Compiler Flags
CFLAGS="-I${SDKUPT1000INC}" -fsigned-char -Wundef -Wstrict-prototypes -Wno-trigraphs -Wimplicit -Wformat 

# CC Compiler Flags
CCFLAGS="-I${SDKUPT1000INC}" -fsigned-char -Wundef -Wno-trigraphs -Wimplicit -Wformat 
CXXFLAGS="-I${SDKUPT1000INC}" -fsigned-char -Wundef -Wno-trigraphs -Wimplicit -Wformat 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lcaethernet -lcafont -lcafs -lcakms -lcalcd -lcamodem -lcapmodem -lcaprt -lcartc -lcauart -lcauldpm -lcausbh -lcagsm -lcabarcode -lpthread -ldl -lcaclvw -lcatls -lctosapi -lcrypto -lcurl -lssl -lz -lfreetype -lcaclentry -lcaclmdl ./LibVKBD.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk dist/upt1000/App/VirtualKBD_test.exe

dist/upt1000/App/VirtualKBD_test.exe: ./LibVKBD.so

dist/upt1000/App/VirtualKBD_test.exe: ${OBJECTFILES}
	${MKDIR} -p dist/upt1000/App
	arm-brcm-linux-gnueabi-g++ -o dist/upt1000/App/VirtualKBD_test ${OBJECTFILES} ${LDLIBSOPTIONS} -L . "-L${SDKUPT1000LIB}" "-L${SDKUPT1000LIBN}"

${OBJECTDIR}/_ext/511dc4f5/DebugInfo.o: ../SRC/DebugInfo.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511dc4f5
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/UPT1000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/UPT1000/include -o ${OBJECTDIR}/_ext/511dc4f5/DebugInfo.o ../SRC/DebugInfo.cpp

${OBJECTDIR}/appmain.o: appmain.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/UPT1000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/UPT1000/include -o ${OBJECTDIR}/appmain.o appmain.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r dist/upt1000/App/LibVKBD.so
	${RM} dist/upt1000/App/VirtualKBD_test.exe

# Subprojects
.clean-subprojects:
