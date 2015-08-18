#///////////////////////////////////////////////////////////////////////////
#//
#//    Copyright 2010
#//
#//    This file has been adabted fromo the rootpwa project
#//
#//    rootpwa is free software: you can redistribute it and/or modify
#//    it under the terms of the GNU General Public License as published by
#//    the Free Software Foundation, either version 3 of the License, or
#//    (at your option) any later version.
#//
#//    rootpwa is distributed in the hope that it will be useful,
#//    but WITHOUT ANY WARRANTY; without even the implied warranty of
#//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#//    GNU General Public License for more details.
#//
#//    You should have received a copy of the GNU General Public License
#//    along with rootpwa.  If not, see <http://www.gnu.org/licenses/>.
#//
#///////////////////////////////////////////////////////////////////////////
#//-------------------------------------------------------------------------
#//
#// Description:
#//      main build file for ROOTPWA
#//
#//
#// Author List:
#//      Sebastian Neubert    TUM            (original author)
#//
#//
#//-------------------------------------------------------------------------


# check if cmake has the required version
cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)


# set verbosity
set(CMAKE_VERBOSE_MAKEFILE 0)  # if set to 1 compile and link commands are displayed during build
# the same effect can be achieved by calling 'make VERBOSE=1'


option(DEBUG_OUTPUT "en/disable debug output" OFF)


# define project
message(STATUS "")
message(STATUS ">>> Setting up project 'PRISMA'.")
project(PRISMA)


# load some common cmake macros
# set path, where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
message(STATUS "")
message(STATUS ">>> Setting up Cmake modules.")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakeModules")
message(STATUS "Using cmake module path '${CMAKE_MODULE_PATH}'.")
include(CommonMacros)
include(FeatureSummary)


# force out-of-source builds.
enforce_out_of_source_build()


# warn user if system is not UNIX
message(STATUS "")
message(STATUS ">>> Setting up system environment.")
if(NOT UNIX)
	message(FATAL_ERROR "This is an unsupported system.")
endif()
if(CMAKE_VERSION VERSION_GREATER 2.8.4)
	include(ProcessorCount)  # requires Cmake V2.8.5+
	ProcessorCount(NMB_CPU_CORES)
	message(STATUS "Detected host system '${CMAKE_HOST_SYSTEM_NAME}' version "
		"'${CMAKE_HOST_SYSTEM_VERSION}', architecture '${CMAKE_HOST_SYSTEM_PROCESSOR}', "
		"${NMB_CPU_CORES} CPU core(s).")
else()
	message(STATUS "Detected host system '${CMAKE_HOST_SYSTEM_NAME}' version "
		"'${CMAKE_HOST_SYSTEM_VERSION}', architecture '${CMAKE_HOST_SYSTEM_PROCESSOR}'.")
endif()
message(STATUS "Compiling for system '${CMAKE_SYSTEM_NAME}' version '${CMAKE_SYSTEM_VERSION}', "
	"architecture '${CMAKE_SYSTEM_PROCESSOR}'.")


# define build types
# predefined build types: "DEBUG" "RELEASE" "RELWITHDEBINFO" "MINSIZEREL"
# set a default build type for single-configuration CMake generators, if no build type is set.
message(STATUS "")
message(STATUS ">>> Setting up compiler environment.")
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type was specified. Setting build type to 'RELEASE'.")
	set(CMAKE_BUILD_TYPE RELEASE)
endif()
# common compiler flags
#set(CMAKE_CXX_FLAGS "-Wall -Woverloaded-virtual -Werror -Wextra -pedantic")
#set(CMAKE_CXX_FLAGS "-Wall -Woverloaded-virtual -Werror -Wextra")
#set(CMAKE_CXX_FLAGS "-Wall -Woverloaded-virtual -Werror -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn")

set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC -Wall -Woverloaded-virtual -Werror")

# flags for specific build types
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
# `gcc -march=native -Q --help=target` shows the relevant compiler switches
# consider adding -DNODEBUG (disables all asserts) and -ffast-math
#if(NOT CMAKE_COMPILER_IS_GNUCXX AND ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
	# use gcc instead of llvm compiler on MacOS 10.7 (Darwin 11.x.y)
#	if(${CMAKE_HOST_SYSTEM_VERSION} VERSION_GREATER "10.999.999" AND ${CMAKE_HOST_SYSTEM_VERSION} VERSION_LESS "12.0.0")
#		message(STATUS "Detected MacOS 10.7: using gcc instead of llvm compiler.")
#		set(CMAKE_C_COMPILER gcc-4.8)
#		set(CMAKE_CXX_COMPILER g++-4.8)
#		set(CMAKE_COMPILER_IS_GNUCXX TRUE)
#	endif()
#	# use gcc instead of llvm compiler on MacOS 10.8 (Darwin 12.x.y)
#	if(${CMAKE_HOST_SYSTEM_VERSION} VERSION_GREATER "11.999.999" AND ${CMAKE_HOST_SYSTEM_VERSION} VERSION_LESS "13.0.0")
#		message(STATUS "Detected MacOS 10.8: using gcc instead of llvm compiler.")
#		set(CMAKE_C_COMPILER gcc)
#		set(CMAKE_CXX_COMPILER g++)
#		set(CMAKE_COMPILER_IS_GNUCXX TRUE)
#	endif()
#endif()
if(CMAKE_COMPILER_IS_GNUCXX)
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
	# workaround for bug concerning -march=native switch in gcc 4.2.1 shipped with MacOS 10.7
	# see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=33144
	if(GCC_VERSION VERSION_EQUAL "4.2.1")
		message(STATUS "Detected gcc version 4.2.1; -march=native switch is disabled because of gcc bug.")
		set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	endif()
endif()
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_LDFLAGS_DEBUG "-g")
set(CMAKE_CXX_LDFLAGS_RELWITHDEBINFO "-g")
# report global build settings
foreach(_LANG "C" "CXX")
	message(STATUS "Using ${_LANG} compiler '${CMAKE_${_LANG}_COMPILER}'.")
	message(STATUS "Using ${_LANG} compiler flags '${CMAKE_${_LANG}_FLAGS}'.")
endforeach()
unset(_LANG)
message(STATUS "Build type is '${CMAKE_BUILD_TYPE}'.")
message(STATUS "Using CXX compiler flags '${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}' "
	"for build type ${CMAKE_BUILD_TYPE}.")
message(STATUS "Using linker flags '${CMAKE_CXX_LDFLAGS_${CMAKE_BUILD_TYPE}}' "
	"for build type ${CMAKE_BUILD_TYPE}.")
#include(CMakePrintSystemInformation)


# redirect output files
message(STATUS "")
message(STATUS ">>> Setting up output paths.")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
message(STATUS "Using library output path '${LIBRARY_OUTPUT_PATH}'.")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
message(STATUS "Using executable output path '${EXECUTABLE_OUTPUT_PATH}'.")

# setup Boost
# environment variable $BOOST_ROOT is expected to point to non-standard locations
message(STATUS "")
message(STATUS ">>> Setting up Boost library.")
set(_BOOST_COMPONENTS "mpi" "serialization" "python" "timer" "system")
# set(Boost_DEBUG 1)
set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_MULTITHREADED  OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
if(     ("$ENV{BOOST_ROOT}"       STREQUAL "")
		AND ("$ENV{BOOSTROOT}"        STREQUAL "")
		AND ("$ENV{Boost_DIR}"        STREQUAL "")
		AND ("$ENV{BOOST_INCLUDEDIR}" STREQUAL "")
		AND ("$ENV{BOOST_LIBRARYDIR}" STREQUAL ""))
	set(Boost_NO_SYSTEM_PATHS OFF)
else()
	set(Boost_NO_SYSTEM_PATHS ON)
endif()
# this is a somewhat ugly hack
# the problem is that components cannot be defined as optional while
# at the same time the library is required. the third find_package
# line is needed in case the components are not found, because
# Boost_FOUND is set to FALSE.
find_package(Boost 1.50.0 REQUIRED)
find_package(Boost 1.50.0 QUIET COMPONENTS ${_BOOST_COMPONENTS})
foreach(_BOOST_COMPONENT ${_BOOST_COMPONENTS})
	string(TOUPPER ${_BOOST_COMPONENT} _BOOST_COMPONENT)
	if(Boost_${_BOOST_COMPONENT}_FOUND)
		message(STATUS "    Found Boost component ${_BOOST_COMPONENT} at "
			"'${Boost_${_BOOST_COMPONENT}_LIBRARY}'.")
	endif()
endforeach()
unset(_BOOST_COMPONENT)
unset(_BOOST_COMPONENTS)
find_package(Boost 1.50.0 REQUIRED)
set_feature_info(Boost
	"C++ Template Library"
	"http://www.boost.org/"
	"required"
	)
if(Boost_FOUND)
	set(Boost_LIBRARY_VERSION "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
	message(STATUS "Using Boost ${Boost_LIBRARY_VERSION} include directories '${Boost_INCLUDE_DIRS}'.")
	message(STATUS "Using Boost ${Boost_LIBRARY_VERSION} library directories '${Boost_LIBRARY_DIRS}'.")
else()
	message(FATAL_ERROR "Could not find Boost installation. "
		"Is environment variable BOOST_ROOT=${BOOST_ROOT} set correctly? Please read INSTALL.")
endif()


# setup libconfig
# environment variable $LIBCONFIG is expected to point to libconfig location
# message(STATUS "")
# message(STATUS ">>> Setting up libconfig library.")
# find_package(Libconfig 1.4 REQUIRED)
# set_feature_info(Libconfig
#	"Simple C++ library for processing structured configuration files"
#	"http://www.hyperrealm.com/libconfig/"
#	"required"
#	)


# setup ROOT includes and libraries
message(STATUS "")
message(STATUS ">>> Setting up ROOT.")
set(_ROOT_COMPONENTS "Minuit2" "MathMore" "TreePlayer")
find_package(ROOT 5.34.04 REQUIRED ${_ROOT_COMPONENTS})
set_feature_info(ROOT
	"C++ HEP analysis framework"
	"http://root.cern.ch/"
	"required"
	)



# setup Python
message(STATUS "")
message(STATUS ">>> Setting up Python.")
option(USE_PYTHON "En/Disables Python bindings" OFF)
if(ROOT_VERSION VERSION_LESS "5.34.04")
	message(STATUS "Python bindings require ROOT version 5.34.04 or newer "
		"(found ${ROOT_VERSION}).")
	message(STATUS "No Python bindings will be generated")
	set(USE_PYTHON OFF)
else()
	find_package(Python 2.7)
	set_feature_info(Python
		"General-purpose, high-level programming language"
		"http://www.python.org"
		"optional"
		)
	if(NOT PYTHONLIBS_FOUND)
		set(USE_PYTHON OFF)
		message(STATUS "Cannot find Python libraries. No Python bindings will be generated.")
	else()
		set(USE_PYTHON ON)
		# check that Boost.Python library was found
		set(_BOOST_PYTHON_COMPONENTS "python")
		foreach(_BOOST_PYTHON_COMPONENT ${_BOOST_PYTHON_COMPONENTS})
			string(TOUPPER ${_BOOST_PYTHON_COMPONENT} _BOOST_PYTHON_COMPONENT)
			if(NOT Boost_${_BOOST_PYTHON_COMPONENT}_FOUND)
				set(USE_PYTHON OFF)
				message(STATUS "Cannot find Boost.Python library in "
					"'${Boost_LIBRARY_DIRS}'. Please read INSTALL on how to build Boost.Python.")
			else()
				list(APPEND Boost_PYTHON_LIBS ${Boost_${_BOOST_PYTHON_COMPONENT}_LIBRARY})
			endif()
		endforeach()
		unset(_BOOST_PYTHON_COMPONENTS)
		if(USE_PYTHON)
			message(STATUS "Setting up ROOT with PyROOT library.")
			find_package(ROOT 5.26 REQUIRED ${_ROOT_COMPONENTS} PyROOT)
			message(STATUS "Using Boost.Python libraries '${Boost_PYTHON_LIBS}'.")
			message(STATUS "Enabling compilation of Python components.")
			add_definitions(-DUSE_PYTHON)
			set(PYTHON_LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/pyLib")
			file(MAKE_DIRECTORY ${PYTHON_LIBRARY_OUTPUT_PATH})
			file(MAKE_DIRECTORY ${PYTHON_LIBRARY_OUTPUT_PATH}/pyRootPwa)
			message(STATUS "Using python bindings output path '${PYTHON_LIBRARY_OUTPUT_PATH}'.")
		else()
			disable_feature(Python)
			message(STATUS "Found Python installation, but Boost.Python is not built correctly (consult INSTALL). "
				"No Python bindings will be generated.")
		endif()
	endif()
endif()
unset(_ROOT_COMPONENTS)


# make git hash accessible via predefined macro GIT_HASH
message(STATUS "")
message(STATUS ">>> Setting up Git.")
find_package(Git)
set_feature_info(Subversion
	"Free and open source distributed version control system"
	"http://git-scm.com/"
	"needed only to determine repository commit sha"
	)
if(GIT_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} log --pretty="%H" -n1 -- ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_HASH
		RESULT_VARIABLE _GIT_LOG_RETURN
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	if(NOT _GIT_LOG_RETURN)
		message(STATUS "Git repository hash is '${GIT_HASH}'.")
	else()
		message(STATUS "Error running 'git'. Repository hash unknown.")
	endif()
endif()
if(GIT_HASH)
	add_definitions(-D'GIT_HASH=${GIT_HASH}')
else()
	add_definitions(-D'GIT_HASH=\"\"')
endif()


# setup doxygen
message(STATUS "")
message(STATUS ">>> Setting up Doxygen.")
find_package(Doxygen)
set_feature_info(Doxygen
	"Documentation generator"
	"http://www.doxygen.org/"
	"optional"
	)
if(NOT DOXYGEN_FOUND)
	message(WARNING "Cannot find Doxygen. Documentation cannot be generated.")
else()
	set(DOXYGEN_TARGET  "doxygen")
	set(DOXYGEN_DOC_DIR "${CMAKE_SOURCE_DIR}/html-doc")
	set(DOXYGEN_CONF    "${CMAKE_SOURCE_DIR}/rootpwaDoxyfile.conf")
	message(STATUS "Run 'make ${DOXYGEN_TARGET}' to create Doxygen documentation files "
		"in '${DOXYGEN_DOC_DIR}'.")
	add_custom_target(${DOXYGEN_TARGET}
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONF}
		DEPENDS ${DOXYGEN_CONF}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		)
endif()


# make some environment variables accessible via predefined macro variables
execute_process(COMMAND hostname
	OUTPUT_VARIABLE HOSTNAME
	RESULT_VARIABLE _HOSTNAME_RETURN
	OUTPUT_STRIP_TRAILING_WHITESPACE)
if(_HOSTNAME_RETURN)
	set(HOSTNAME "")
endif()
unset(_HOSTNAME_RETURN)
if(DEBUG_OUTPUT)
	message(STATUS "Adding definitions for internal variables:")
endif()
foreach(_CMAKEVAR
		"CMAKE_HOST_SYSTEM_NAME"
		"CMAKE_HOST_SYSTEM_PROCESSOR"
		"CMAKE_HOST_SYSTEM_VERSION"
		"NMB_CPU_CORES"
		"HOSTNAME"
		"CMAKE_SOURCE_DIR"
		"CMAKE_BUILD_TYPE"
		"Boost_LIBRARY_VERSION"
		"Boost_INCLUDE_DIRS"
		"Libconfig_VERSION"
		"Libconfig_DIR"
		"ROOTSYS"
		"CUDA_VERSION"
		"CUDA_LIB_DIRS"
		"PYTHONLIBS_VERSION_STRING"
		"PYTHON_INCLUDE_DIRS"
		)
	if(_CMAKEVAR)
		if(DEBUG_OUTPUT)
			message(STATUS "        ${_CMAKEVAR} = ${${_CMAKEVAR}}")
		endif()
		add_definitions(-D'${_CMAKEVAR}=\"${${_CMAKEVAR}}\"')
	else()
		add_definitions(-D'${_CMAKEVAR}=\"\"')
	endif()
endforeach()
unset(_CMAKEVAR)
if(DEBUG_OUTPUT)
	message(STATUS "Adding definitions for environment variables:")
endif()
foreach(_ENVVAR
		"USER"
		)
	set(_ENVVARVAL $ENV{${_ENVVAR}})
	if(_ENVVARVAL)
		if(DEBUG_OUTPUT)
			message(STATUS "        ${_ENVVAR} = ${_ENVVARVAL}")
		endif()
		add_definitions(-D'${_ENVVAR}=\"${_ENVVARVAL}\"')
	else()
		add_definitions(-D'${_ENVVAR}=\"\"')
	endif()
	unset(_ENVVARVAL)
endforeach()
unset(_ENVVAR)


enable_testing()


# set include and library paths
set(UTILITIES_INCLUDE_DIR
	${CMAKE_SOURCE_DIR}/utilities
	)

#set(TOOLS_INCLUDE_DIR
#	${CMAKE_SOURCE_DIR}/tools
#	)


# build subprojects



# DMatrix
add_subdirectory(DMatrix)


# print feature summary
message(STATUS "")
message(STATUS ">>> Feature summary:")
#if(CMAKE_VERSION VERSION_GREATER 2.8.4)
#	feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)  # requires Cmake V2.8.5+
#else()
print_enabled_features()
print_disabled_features()
#endif()


message(STATUS "")
message(STATUS ">>> Done.")
message(STATUS "Run 'make' to build the project.")
message(STATUS "On multi-core machines using 'make -j' can speedup compilation considerably.")
