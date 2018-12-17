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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/74dbe21e/RS485.o \
	${OBJECTDIR}/_ext/74dbe21e/connection_handler.o \
	${OBJECTDIR}/_ext/74dbe21e/crc.o \
	${OBJECTDIR}/_ext/74dbe21e/ethernet.o \
	${OBJECTDIR}/_ext/74dbe21e/main.o \
	${OBJECTDIR}/_ext/74dbe21e/serial.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/_ext/eeab66f0/gtest_serial.o

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
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mbgate ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/74dbe21e/RS485.o: /root/mbgate/RS485.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/RS485.o /root/mbgate/RS485.cpp

${OBJECTDIR}/_ext/74dbe21e/connection_handler.o: /root/mbgate/connection_handler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/connection_handler.o /root/mbgate/connection_handler.cpp

${OBJECTDIR}/_ext/74dbe21e/crc.o: /root/mbgate/crc.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/crc.o /root/mbgate/crc.cpp

${OBJECTDIR}/_ext/74dbe21e/ethernet.o: /root/mbgate/ethernet.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/ethernet.o /root/mbgate/ethernet.cpp

${OBJECTDIR}/_ext/74dbe21e/main.o: /root/mbgate/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/main.o /root/mbgate/main.cpp

${OBJECTDIR}/_ext/74dbe21e/serial.o: /root/mbgate/serial.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/serial.o /root/mbgate/serial.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/eeab66f0/gtest_serial.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/_ext/eeab66f0/gtest_serial.o: /root/mbgate/tests/gtest_serial.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/eeab66f0
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/eeab66f0/gtest_serial.o /root/mbgate/tests/gtest_serial.cpp


${OBJECTDIR}/_ext/74dbe21e/RS485_nomain.o: ${OBJECTDIR}/_ext/74dbe21e/RS485.o /root/mbgate/RS485.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/74dbe21e/RS485.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/RS485_nomain.o /root/mbgate/RS485.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/74dbe21e/RS485.o ${OBJECTDIR}/_ext/74dbe21e/RS485_nomain.o;\
	fi

${OBJECTDIR}/_ext/74dbe21e/connection_handler_nomain.o: ${OBJECTDIR}/_ext/74dbe21e/connection_handler.o /root/mbgate/connection_handler.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/74dbe21e/connection_handler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/connection_handler_nomain.o /root/mbgate/connection_handler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/74dbe21e/connection_handler.o ${OBJECTDIR}/_ext/74dbe21e/connection_handler_nomain.o;\
	fi

${OBJECTDIR}/_ext/74dbe21e/crc_nomain.o: ${OBJECTDIR}/_ext/74dbe21e/crc.o /root/mbgate/crc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/74dbe21e/crc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/crc_nomain.o /root/mbgate/crc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/74dbe21e/crc.o ${OBJECTDIR}/_ext/74dbe21e/crc_nomain.o;\
	fi

${OBJECTDIR}/_ext/74dbe21e/ethernet_nomain.o: ${OBJECTDIR}/_ext/74dbe21e/ethernet.o /root/mbgate/ethernet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/74dbe21e/ethernet.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/ethernet_nomain.o /root/mbgate/ethernet.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/74dbe21e/ethernet.o ${OBJECTDIR}/_ext/74dbe21e/ethernet_nomain.o;\
	fi

${OBJECTDIR}/_ext/74dbe21e/main_nomain.o: ${OBJECTDIR}/_ext/74dbe21e/main.o /root/mbgate/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/74dbe21e/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/main_nomain.o /root/mbgate/main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/74dbe21e/main.o ${OBJECTDIR}/_ext/74dbe21e/main_nomain.o;\
	fi

${OBJECTDIR}/_ext/74dbe21e/serial_nomain.o: ${OBJECTDIR}/_ext/74dbe21e/serial.o /root/mbgate/serial.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/74dbe21e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/74dbe21e/serial.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/74dbe21e/serial_nomain.o /root/mbgate/serial.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/74dbe21e/serial.o ${OBJECTDIR}/_ext/74dbe21e/serial_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
