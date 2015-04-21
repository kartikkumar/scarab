# Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
# Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
# Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
# Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

# Include script to build external library with CMake.
include(ExternalProject)

if(NOT BUILD_DEPENDENCIES)
  find_package(Spot)
endif(NOT BUILD_DEPENDENCIES)

if(NOT SPOT_FOUND)
  message(STATUS "Spot will be downloaded when ${CMAKE_PROJECT_NAME} is built")
  ExternalProject_Add(spot-lib
    PREFIX ${EXTERNAL_PATH}/Spot
    #--Download step--------------
    URL https://github.com/kartikkumar/spot/archive/master.zip
    TIMEOUT 120
    #--Update/Patch step----------
    #--Configure step-------------
    #--Build step-----------------
    BUILD_IN_SOURCE 1
    #--Install step---------------
    INSTALL_COMMAND ""
    #--Output logging-------------
    LOG_DOWNLOAD ON
  )
  ExternalProject_Get_Property(spot-lib source_dir)
  set(SPOT_INCLUDE_DIRS ${source_dir}/include
    CACHE INTERNAL "Path to Spot include folder")
  set(SPOT_LIBRARY_DIR ${source_dir}/lib
    CACHE INTERNAL "Path to Spot library")
  set(SPOT_LIBRARY "spot")
endif(NOT SPOT_FOUND)

if(NOT APPLE)
  include_directories(SYSTEM AFTER "${SPOT_INCLUDE_DIRS}")
else(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${SPOT_INCLUDE_DIRS}\"")
endif(NOT APPLE)
link_directories(${SPOT_LIBRARY_DIR})

# -------------------------------

if(BUILD_TESTS)
  if(NOT BUILD_DEPENDENCIES)
    find_package(CATCH)
  endif(NOT BUILD_DEPENDENCIES)

  if(NOT CATCH_FOUND)
    message(STATUS "Catch will be downloaded when ${CMAKE_PROJECT_NAME} is built")
    ExternalProject_Add(catch
      PREFIX ${EXTERNAL_PATH}/Catch
      #--Download step--------------
      URL https://github.com/kartikkumar/Catch/archive/master.zip
      TIMEOUT 30
      #--Update/Patch step----------
      UPDATE_COMMAND ""
      PATCH_COMMAND ""
      #--Configure step-------------
      CONFIGURE_COMMAND ""
      #--Build step-----------------
      BUILD_COMMAND ""
      #--Install step---------------
      INSTALL_COMMAND ""
      #--Output logging-------------
      LOG_DOWNLOAD ON
    )
    ExternalProject_Get_Property(catch source_dir)
    set(CATCH_INCLUDE_DIRS ${source_dir}/include CACHE INTERNAL "Path to include folder for Catch")
  endif(NOT CATCH_FOUND)

  if(NOT APPLE)
    include_directories(SYSTEM AFTER "${CATCH_INCLUDE_DIRS}")
  else(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${CATCH_INCLUDE_DIRS}\"")
  endif(NOT APPLE)
endif(BUILD_TESTS)
