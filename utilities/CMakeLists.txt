#///////////////////////////////////////////////////////////////////////////
#//
#//    Copyright 2010
#//
#//    This file is part of rootpwa
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
#//      build file for utilities
#//
#//
#// Author List:
#//      Boris Grube          TUM            (original author)
#//
#//
#//-------------------------------------------------------------------------


message(STATUS "")
message(STATUS ">>> Setting up 'utilities' directory.")


# # set include directories
# set(INCLUDE_DIRECTORIES
# 	${Boost_INCLUDE_DIRS}
# 	${ROOT_INCLUDE_DIR}
# 	${PWA2000_INCLUDE_DIR}
# 	${CMAKE_CURRENT_SOURCE_DIR}
# 	)
# include_directories(${INCLUDE_DIRECTORIES})


# # source files that are compiled into library
# set(SOURCES
#   indentStream.cc
#   )


# # library
# set(THIS_LIB "RootPwaUtil")
# make_shared_library(
# 	"${THIS_LIB}"
# 	"${SOURCES}"
#   "${BOOST_LIBS}"
#   "${ROOT_LIBS}"
#   "${PWA2000_LIBS}"
#   )


# executables
# make_executable(testSumAccumulators testSumAccumulators.cc)
# make_executable(testSpinUtils       testSpinUtils.cc)
# make_executable(testFileUtils       testFileUtils.cc)
# if(USE_PWA2000)
# 	make_executable(testLibppFunctions testLibppFunctions.cc "${ROOT_LIBS};${PWA2000_LIBS}")
# else()
# 	message(STATUS "PWA2000 disabled. Skipping build of testLibppFunctions.")
# endif()


# build tests
add_subdirectory(test)
