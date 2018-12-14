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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/79b25175/RS485.o \
	${OBJECTDIR}/_ext/79b25175/connection_handler.o \
	${OBJECTDIR}/_ext/79b25175/crc.o \
	${OBJECTDIR}/_ext/79b25175/ethernet.o \
	${OBJECTDIR}/_ext/79b25175/serial.o \
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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mbgate

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mbgate: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mbgate ${OBJECTFILES} ${LDLIBSOPTIONS} -lpthread -lgtest

${OBJECTDIR}/_ext/79b25175/RS485.o: /home/pi/mbgate/RS485.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/79b25175
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/pi/mbgate -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/79b25175/RS485.o /home/pi/mbgate/RS485.cpp

${OBJECTDIR}/_ext/79b25175/connection_handler.o: /home/pi/mbgate/connection_handler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/79b25175
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/pi/mbgate -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/79b25175/connection_handler.o /home/pi/mbgate/connection_handler.cpp

${OBJECTDIR}/_ext/79b25175/crc.o: /home/pi/mbgate/crc.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/79b25175
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/pi/mbgate -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/79b25175/crc.o /home/pi/mbgate/crc.cpp

${OBJECTDIR}/_ext/79b25175/ethernet.o: /home/pi/mbgate/ethernet.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/79b25175
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/pi/mbgate -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/79b25175/ethernet.o /home/pi/mbgate/ethernet.cpp

${OBJECTDIR}/_ext/79b25175/serial.o: /home/pi/mbgate/serial.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/79b25175
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/pi/mbgate -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/79b25175/serial.o /home/pi/mbgate/serial.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/home/pi/mbgate -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
