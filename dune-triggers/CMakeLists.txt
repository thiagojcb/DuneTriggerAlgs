

add_library(DuneTriggers INTERFACE)

target_include_directories(DuneTriggers INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
  $<INSTALL_INTERFACE:dune-triggers>
  )

add_subdirectory(Supernova)

install(
  TARGETS DuneTriggers
  EXPORT DuneTriggersTargets
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  COMPONENT dev
  )

install(DIRECTORY
  ${PROJECT_SOURCE_DIR}/dune-triggers
  DESTINATION dune-triggers
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hh"
  PATTERN "*.hpp"
  PATTERN "*.hxx"
  )
