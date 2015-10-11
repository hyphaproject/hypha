cmake_minimum_required(VERSION 3.0.0)
project(Hypha)
file(STRINGS "${PROJECT_SOURCE_DIR}/libversion" SHARED_LIBRARY_VERSION)
file (STRINGS "${PROJECT_SOURCE_DIR}/VERSION" PACKAGE_VERSION )
message(STATUS "Hypha package version: ${PACKAGE_VERSION}")
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})
set(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(RELEASE_NAME "Unstable-trunk")
set(PROJECT_VERSION ${COMPLETE_VERSION})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#################################################################################
# Setup C/C++ compiler options
#################################################################################
if(NOT MSVC_IDE)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
        "Choose the type of build, options are: None Debug Release" FORCE)
    endif()
    message(STATUS "Setting Poco build type - ${CMAKE_BUILD_TYPE}")
endif()
if (CMAKE_BUILD_TYPE STREQUAL "")
    set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
endif()


ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

include(HyphaMacros)

include_directories( "utils/include" "core/include" "plugin/include" "handler/include" ${Boost_INCLUDE_DIRS} )

if(WIN32)
    find_library(POCO_NET PocoNet)
    find_library(POCO_UTIL PocoUtil)
    find_library(POCO_FOUNDATION PocoFoundation)
    find_library(POCO_DATA PocoData)
    find_library(POCO_MYSQL PocoMySQL)
    find_package(Boost COMPONENTS signals thread system filesystem REQUIRED)
    include_directories( "utils/include" "core/include" "plugin/include" "handler/include" ${Boost_INCLUDE_DIRS} "C:/poco/Net/include" "C:/poco/Foundation/include"
        "C:/poco/Util/include" "C:/poco/Data/include" "C:/poco/Data/MySQL/include")
    link_directories( "C:/poco/lib" $ENV{BOOST_LIBRARYDIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()

if(HYPHA_STATIC)
add_definitions( -DHYPHA_STATIC -DHYPHA_NO_AUTOMATIC_LIBS)
set( LIB_MODE STATIC )
message(STATUS "Building static libraries")
else(HYPHA_STATIC)
set( LIB_MODE SHARED )
message(STATUS "Building dynamic libraries")
endif(HYPHA_STATIC)

set(Hypha_COMPONENTS "")

add_subdirectory(utils)
list(APPEND Hypha_COMPONENTS "Utils")
add_subdirectory(core)
list(APPEND Hypha_COMPONENTS "Core")
add_subdirectory(plugin)
list(APPEND Hypha_COMPONENTS "Plugin")
add_subdirectory(handler)
list(APPEND Hypha_COMPONENTS "Handler")


#############################################################
# Enable packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hypha Libraries")
set(CPACK_PACKAGE_VENDOR "chriamue")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/local")
include(CPack)
#############################################################

foreach(component ${Hypha_COMPONENTS})
message(STATUS "Building: ${component}")
endforeach()

add_subdirectory( doc )
