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
	${OBJECTDIR}/ByteStream.o \
	${OBJECTDIR}/DebugInfo.o \
	${OBJECTDIR}/EMVBase.o \
	${OBJECTDIR}/MyCallBack.o \
	${OBJECTDIR}/MyEmv.o \
	${OBJECTDIR}/MyWiFi.o \
	${OBJECTDIR}/appmain.o


# C Compiler Flags
CFLAGS="-I${SDKV3INC}" -fsigned-char -Wundef -Wstrict-prototypes -Wno-trigraphs -Wimplicit -Wformat 

# CC Compiler Flags
CCFLAGS="-I${SDKV3INC}" -fsigned-char -Wundef -Wno-trigraphs -Wimplicit -Wformat 
CXXFLAGS="-I${SDKV3INC}" -fsigned-char -Wundef -Wno-trigraphs -Wimplicit -Wformat 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lcaethernet -lcafont -lcafs -lcakms -lcalcd -lcamodem -lcapmodem -lcaprt -lcartc -lcauart -lcauldpm -lcausbh -lcagsm -lcabarcode -lpthread -ldl -lcaclvw -lcaclentry -lcaclmdl -lcatls -lctosapi -lcrypto -lcurl -lssl -lz -lfreetype -lcaemvl2 -lcaemvl2ap

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk dist/V3/App/V3_EMV.exe

dist/V3/App/V3_EMV.exe: ${OBJECTFILES}
	${MKDIR} -p dist/V3/App
	arm-brcm-linux-gnueabi-g++ -o dist/V3/App/V3_EMV ${OBJECTFILES} ${LDLIBSOPTIONS} -L . "-L${SDKV3LIB}" "-L${SDKV3LIBN}"

${OBJECTDIR}/ByteStream.o: ByteStream.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/ByteStream.o ByteStream.cpp

${OBJECTDIR}/DebugInfo.o: DebugInfo.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/DebugInfo.o DebugInfo.cpp

${OBJECTDIR}/EMVBase.o: EMVBase.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/EMVBase.o EMVBase.cpp

${OBJECTDIR}/MyCallBack.o: MyCallBack.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/MyCallBack.o MyCallBack.cpp

${OBJECTDIR}/MyEmv.o: MyEmv.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/MyEmv.o MyEmv.cpp

${OBJECTDIR}/MyWiFi.o: MyWiFi.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/MyWiFi.o MyWiFi.cpp

${OBJECTDIR}/appmain.o: appmain.cpp
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -DCTOS_API -I/cygdrive/C/Program\ Files/Castles/VEGA3000/include -I/cygdrive/C/Program\ Files\ \(x86\)/Castles/VEGA3000/include -o ${OBJECTDIR}/appmain.o appmain.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:
