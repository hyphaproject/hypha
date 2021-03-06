
# 
# Executable name and options
# 

# Target name
set(target hyphacore-test)
message(STATUS "Test ${target}")


# 
# Sources
# 

set(sources
    main.cpp
    cache_test.cpp
    controller_test.cpp
    core_test.cpp
    database_test.cpp
    settings_test.cpp
)


# 
# Create executable
# 

# Build executable
add_executable(${target}
    ${sources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${PROJECT_BINARY_DIR}/source/include
)


# 
# Libraries
# 

if("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
include(CodeCoverage)
set(libgcov "gcov")

setup_target_for_coverage(${target}_coverage ${target} coverage)
endif()

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::controller
    ${META_PROJECT_NAME}::core
    libgmock
    ${libgcov}
)


# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
