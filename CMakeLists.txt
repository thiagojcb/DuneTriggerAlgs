cmake_minimum_required(VERSION 3.13)

project(DuneTrigger)

set(DUNETRIGGER_MAJOR_VERSION "0")
set(DUNETRIGGER_MINOR_VERSION "0")
set(DUNETRIGGER_PATCH_VERSION "0")
set(DUNETRIGGER_VERSION ${DUNETRIGGER_MAJOR_VERSION}_${DUNETRIGGER_MINOR_VERSION}_${DUNETRIGGER_PATCH_VERSION})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/DuneTriggers)
endif()

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}" 
  "${PROJECT_BINARY_DIR}")

execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
  OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

# if the distribution is scientific linux, then setup boost in a different way (not using the cmake file from boost)
string(FIND "${LSB_RELEASE_ID_SHORT}" "Scientific" _cmp)
if (_cmp GREATER -1)
  set(Boost_NO_BOOST_CMAKE ON)
else()
  string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -std=c++1y")
endif()

find_package(Boost REQUIRED)
set(BOOST_INCLUDE_DIRS $boost_installation_prefix/include)
find_package(Threads REQUIRED)

add_subdirectory(dune-triggers)
add_subdirectory(exec)

export(TARGETS SupernovaTrigger
  FILE "${PROJECT_BINARY_DIR}/DuneTriggersTargets.cmake"
  )

export(PACKAGE DuneTriggers)

# Create the DuneTriggersConfig.cmake and DuneTriggersConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(DuneTriggersConfig.cmake.in
  "${PROJECT_BINARY_DIR}/DuneTriggersConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${DUNETRIGGERS_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(DuneTriggersConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DuneTriggersConfig.cmake" @ONLY)
# ... for both
configure_file(DuneTriggersConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/DuneTriggersConfigVersion.cmake" @ONLY)

# Install the DuneTriggersConfig.cmake and DuneTriggersConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DuneTriggersConfig.cmake"
  "${PROJECT_BINARY_DIR}/DuneTriggersConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT DuneTriggersTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
