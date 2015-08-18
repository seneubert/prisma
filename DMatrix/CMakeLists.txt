#///////////////////////////////////////////////////////////////////////////
#//
#//    Copyright 2010
#//
#//    This file was adapted from the rootpwa project
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
#//      build file for DMatrix
#//
#//
#// Author List:
#//      Sebastian Neubert    TUM            (original author)
#//
#//
#//-------------------------------------------------------------------------


message(STATUS "")
message(STATUS ">>> Setting up 'DMatrix' directory.")


# set include directories
set(INCLUDE_DIRECTORIES
	${ROOT_INCLUDE_DIR}
	${DMATRIX_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${UTILITIES_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}/numeric/ublas/
	)
include_directories(${INCLUDE_DIRECTORIES})


# source files that are compiled into library
set(SOURCES
	nBodyPhaseSpaceGen.cc
	decayChannels.cc
	mcPhaseSpace.cc
	cauchyIntegral.cc
	dMatrixAmp.cc
	dMatrixSet.cc
	dynMassDep.cc
	TCMatrix.cc
	)


# ROOT dictionary
set(DMATRIX_DICTIONARY ${CMAKE_CURRENT_BINARY_DIR}/DMatrixDict.cc)
set(DMATRIX_DICT_INCLUDE_DIRS
        ${ROOT_INCLUDE_DIR}
        ${UTILITIES_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )
root_generate_dictionary(
        "${DMATRIX_DICTIONARY}"
        "${DMATRIX_DICT_INCLUDE_DIRS}"
        "nBodyPhaseSpaceGen.h;TCMatrix.h"
        "DMatrixLinkDef.h"
        )

set(SOURCES ${SOURCES} ${DMATRIX_DICTIONARY})


# library
set(THIS_LIB "prismaDMatrix")
set(GSL_LIBS
	libgsl.a
	libgslcblas.a
	)
make_shared_library(
	"${THIS_LIB}"
	"${SOURCES}"
	"${GSL_LIBS}"
	)



# executables
make_executable(testMassDep testMassDep.cc ${THIS_LIB} ${ROOT_LIBS} )
make_executable(testKMatrix testKMatrix.cc ${THIS_LIB} ${ROOT_LIBS} )
make_executable(testRescat  testRescat.cc  ${THIS_LIB} ${ROOT_LIBS} ${GSL_LIBS})
make_executable(testDMatrix testDMatrix.cc ${THIS_LIB} ${ROOT_LIBS} ${GSL_LIBS})
make_executable(mixingRes   mixingRes.cc   ${THIS_LIB} ${ROOT_LIBS} ${GSL_LIBS})

