# Copyright Siemens AG, 2014
# Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
# 
# and Contributors.
#
# SPDX-License-Identifier:	BSL-1.0
#
# Collection of common functionality for Hypha CMake

# Find the Microsoft mc.exe message compiler
#
#  CMAKE_MC_COMPILER - where to find mc.exe
if (WIN32)
  # cmake has CMAKE_RC_COMPILER, but no message compiler
  if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
    # this path is only present for 2008+, but we currently require PATH to
    # be set up anyway
    get_filename_component(sdk_dir "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows;CurrentInstallFolder]" REALPATH)
    get_filename_component(kit_dir "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot]" REALPATH)
    if (X64)
      set(sdk_bindir "${sdk_dir}/bin/x64")
      set(kit_bindir "${kit_dir}/bin/x64")
    else (X64)
      set(sdk_bindir "${sdk_dir}/bin")
      set(kit_bindir "${kit_dir}/bin/x86")
    endif (X64)
  endif ()
  find_program(CMAKE_MC_COMPILER mc.exe HINTS "${sdk_bindir}" "${kit_bindir}"
    DOC "path to message compiler")
  if (NOT CMAKE_MC_COMPILER)
    message(FATAL_ERROR "message compiler not found: required to build")
  endif (NOT CMAKE_MC_COMPILER)
  message(STATUS "Found message compiler: ${CMAKE_MC_COMPILER}")
  mark_as_advanced(CMAKE_MC_COMPILER)
endif(WIN32)

#===============================================================================
# Macros for Source file management
#
#  HYPHA_SOURCES_PLAT - Adds a list of files to the sources of a components
#    Usage: HYPHA_SOURCES_PLAT( out name platform sources)
#      INPUT:
#           out             the variable the sources are added to
#           name:           the name of the components
#           platform:       the platform this sources are for (ON = All, OFF = None, WIN32, UNIX ...)
#           sources:        a list of files to add to ${out}
#    Example: HYPHA_SOURCES_PLAT( SRCS Foundation ON src/Foundation.cpp )
#
#  HYPHA_SOURCES - Like HYPHA_SOURCES_PLAT with platform = ON (Built on all platforms)
#    Usage: HYPHA_SOURCES( out name sources)
#    Example: HYPHA_SOURCES( SRCS Foundation src/Foundation.cpp)
#
#  HYPHA_SOURCES_AUTO - Like HYPHA_SOURCES but the name is read from the file header // Package: X
#    Usage: HYPHA_SOURCES_AUTO( out sources)
#    Example: HYPHA_SOURCES_AUTO( SRCS src/Foundation.cpp)
#
#  HYPHA_SOURCES_AUTO_PLAT - Like HYPHA_SOURCES_PLAT but the name is read from the file header // Package: X
#    Usage: HYPHA_SOURCES_AUTO_PLAT(out platform sources)
#    Example: HYPHA_SOURCES_AUTO_PLAT( SRCS WIN32 src/Foundation.cpp)
#
#
#  HYPHA_HEADERS - Adds a list of files to the headers of a components
#    Usage: HYPHA_HEADERS( out name headers)
#      INPUT:
#           out             the variable the headers are added to
#           name:           the name of the components
#           headers:        a list of files to add to HDRSt
#    Example: HYPHA_HEADERS( HDRS Foundation include/hypha/hypha.h )
#
#  HYPHA_HEADERS_AUTO - Like HYPHA_HEADERS but the name is read from the file header // Package: X
#    Usage: HYPHA_HEADERS_AUTO( out headers)
#    Example: HYPHA_HEADERS_AUTO( HDRS src/Foundation.cpp)
#
#
#  HYPHA_MESSAGES - Adds a list of files to the messages of a components
#                  and adds the generated headers to the header list of the component.
#                  On platforms other then Windows this does nothing
#    Usage: HYPHA_MESSAGES( out name messages)
#      INPUT:
#           out             the variable the message and the resulting headers are added to
#           name:           the name of the components
#           messages:       a list of files to add to MSGS
#    Example: HYPHA_MESSAGES( HDRS Foundation include/hypha/hypha.mc )
#


macro(HYPHA_SOURCES_PLAT out name platform)
    source_group("${name}\\Source Files" FILES ${ARGN})
    list(APPEND ${out} ${ARGN})
    if(NOT (${platform}))
        set_source_files_properties(${ARGN} PROPERTIES HEADER_FILE_ONLY TRUE)
    endif()
endmacro()

macro(HYPHA_SOURCES out name)
    HYPHA_SOURCES_PLAT( ${out} ${name} ON ${ARGN})
endmacro()

macro(HYPHA_SOURCES_AUTO out)
    HYPHA_SOURCES_AUTO_PLAT( ${out} ON ${ARGN})
endmacro()

macro(HYPHA_SOURCES_AUTO_PLAT out platform)
    foreach( f ${ARGN})

        get_filename_component(fname ${f} NAME)

        # Read the package name from the source file
        file(STRINGS ${f} package REGEX "// Package: (.*)")
        if(package)
            string(REGEX REPLACE ".*: (.*)" "\\1" name ${package})

            # Files of the Form X_UNIX.cpp are treated as headers
            if(${fname} MATCHES ".*_.*\\..*")
                #message(STATUS "Platform: ${name} ${f} ${platform}")
                HYPHA_SOURCES_PLAT( ${out} ${name} OFF ${f})
            else()
                #message(STATUS "Source: ${name} ${f} ${platform}")
                HYPHA_SOURCES_PLAT( ${out} ${name} ${platform} ${f})
            endif()
        else()
            #message(STATUS "Source: Unknown ${f} ${platform}")
            HYPHA_SOURCES_PLAT( ${out} Unknown ${platform} ${f})
        endif()
    endforeach()
endmacro()


macro(HYPHA_HEADERS_AUTO out)
    foreach( f ${ARGN})

        get_filename_component(fname ${f} NAME)

        # Read the package name from the source file
        file(STRINGS ${f} package REGEX "// Package: (.*)")
        if(package)
            string(REGEX REPLACE ".*: (.*)" "\\1" name ${package})
            #message(STATUS "Header: ${name} ${f}")
            HYPHA_HEADERS( ${out} ${name} ${f})
        else()
            #message(STATUS "Header: Unknown ${f}")
            HYPHA_HEADERS( ${out} Unknown ${f})
        endif()
    endforeach()
endmacro()

macro(HYPHA_HEADERS out name)
    set_source_files_properties(${ARGN} PROPERTIES HEADER_FILE_ONLY TRUE)
    source_group("${name}\\Header Files" FILES ${ARGN})
    list(APPEND ${out} ${ARGN})
endmacro()


macro(HYPHA_MESSAGES out name)
    if (WIN32)
        foreach(msg ${ARGN})
            get_filename_component(msg_name ${msg} NAME)
            get_filename_component(msg_path ${msg} ABSOLUTE)
            string(REPLACE ".mc" ".h" hdr ${msg_name})
            set_source_files_properties(${hdr} PROPERTIES GENERATED TRUE)
            add_custom_command(
                OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${hdr}
                DEPENDS ${msg}
                COMMAND ${CMAKE_MC_COMPILER}
                ARGS
                    -h ${CMAKE_CURRENT_BINARY_DIR}
                    -r ${CMAKE_CURRENT_BINARY_DIR}
                    ${msg_path}
                VERBATIM # recommended: p260
            )

            # Add the generated file to the include directory
            include_directories(${CMAKE_CURRENT_BINARY_DIR})

            # Add the generated headers to HYPHA_HEADERS of the component
            HYPHA_HEADERS( ${out} ${name} ${CMAKE_CURRENT_BINARY_DIR}/${hdr})

        endforeach()

        set_source_files_properties(${ARGN} PROPERTIES HEADER_FILE_ONLY TRUE)
        source_group("${name}\\Message Files" FILES ${ARGN})
        list(APPEND ${out} ${ARGN})

    endif (WIN32)
endmacro()


#===============================================================================
# Macros for Package generation
#
#  HYPHA_GENERATE_PACKAGE - Generates *Config.cmake
#    Usage: HYPHA_GENERATE_PACKAGE(target_name)
#      INPUT:
#           target_name             the name of the target. e.g. Utils for HYPHAUtils
#    Example: HYPHA_GENERATE_PACKAGE(Foundation)
macro(HYPHA_GENERATE_PACKAGE target_name)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)
export(EXPORT "${target_name}Targets"
  FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Targets.cmake"
  NAMESPACE "${PROJECT_NAME}::"
)
configure_file("cmake/Hypha${target_name}Config.cmake"
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Config.cmake"
  @ONLY
)

set(ConfigPackageLocation "lib/cmake/${PROJECT_NAME}")

install(
    EXPORT "${target_name}Targets"
    FILE "${PROJECT_NAME}${target_name}Targets.cmake"
    NAMESPACE "${PROJECT_NAME}::"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
    )

install(
    FILES
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Config.cmake"
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}ConfigVersion.cmake"
    DESTINATION "lib/cmake/${PROJECT_NAME}"
    COMPONENT Devel
    )

endmacro()

#===============================================================================
# Macros for simplified installation
#
#  HYPHA_INSTALL - Install the given target
#    Usage: HYPHA_INSTALL(target_name)
#      INPUT:
#           target_name             the name of the target. e.g. Utils for HYPHAUtils
#    Example: HYPHA_INSTALL(Foundation)
macro(HYPHA_INSTALL target_name)
install(
    DIRECTORY include/hypha
    DESTINATION include
    COMPONENT Devel
    PATTERN ".svn" EXCLUDE
    )

install(
    TARGETS "${target_name}" EXPORT "${target_name}Targets"
    LIBRARY DESTINATION lib${LIB_SUFFIX}
    ARCHIVE DESTINATION lib${LIB_SUFFIX}
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )

if (MSVC)
# install the targets pdb
  HYPHA_INSTALL_PDB(${target_name})
endif()
  
endmacro()

#  HYPHA_INSTALL_PDB - Install the given target's companion pdb file (if present)
#    Usage: HYPHA_INSTALL_PDB(target_name)
#      INPUT:
#           target_name             the name of the target. e.g. Utils for HyphaUtils
#    Example: HYPHA_INSTALL_PDB(Foundation)
#
#    This is an internal macro meant only to be used by HYPHA_INSTALL.
macro(HYPHA_INSTALL_PDB target_name)

    get_property(type TARGET ${target_name} PROPERTY TYPE)
    if ("${type}" STREQUAL "SHARED_LIBRARY" OR "${type}" STREQUAL "EXECUTABLE")
        install(
            FILES $<TARGET_PDB_FILE:${target_name}>
            DESTINATION bin
            COMPONENT Devel
            OPTIONAL
            )
    endif()
endmacro()
