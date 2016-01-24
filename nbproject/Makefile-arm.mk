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
CC=arm-linux-gnueabihf-gcc
CCC=arm-linux-gnueabihf-g++
CXX=arm-linux-gnueabihf-g++
FC=gfortran
AS=arm-linux-gnueabihf-as

# Macros
CND_PLATFORM=arm-Linux-x86
CND_DLIB_EXT=so
CND_CONF=arm
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Camera.o \
	${OBJECTDIR}/Log.o \
	${OBJECTDIR}/Synapsis.o \
	${OBJECTDIR}/SynapsisBase.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/lib/arm-linux-gnueabihf -L/usr/arm-linux-gnueabihf/lib -L/usr/arm-linux-gnueabihf/libsf -lwebsockets -lopencv_core -lopencv_video -ljsoncpp

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/domalgo

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/domalgo: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/domalgo ${OBJECTFILES} ${LDLIBSOPTIONS} -lopencv_imgproc

${OBJECTDIR}/Camera.o: nbproject/Makefile-${CND_CONF}.mk Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/arm-linux-gnueabihf/include/ -include /usr/arm-linux-gnueabihf/include/libwebsockets.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Camera.o Camera.cpp

${OBJECTDIR}/Log.o: nbproject/Makefile-${CND_CONF}.mk Log.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/arm-linux-gnueabihf/include/ -include /usr/arm-linux-gnueabihf/include/libwebsockets.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Log.o Log.cpp

${OBJECTDIR}/Synapsis.o: nbproject/Makefile-${CND_CONF}.mk Synapsis.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/arm-linux-gnueabihf/include/ -include /usr/arm-linux-gnueabihf/include/libwebsockets.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Synapsis.o Synapsis.cpp

${OBJECTDIR}/SynapsisBase.o: nbproject/Makefile-${CND_CONF}.mk SynapsisBase.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/arm-linux-gnueabihf/include/ -include /usr/arm-linux-gnueabihf/include/libwebsockets.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SynapsisBase.o SynapsisBase.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/arm-linux-gnueabihf/include/ -include /usr/arm-linux-gnueabihf/include/libwebsockets.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/domalgo

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
