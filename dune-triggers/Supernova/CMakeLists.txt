
add_library(SupernovaTrigger SHARED TriggerCandidateMaker_Supernova.cc)

target_include_directories(SupernovaTrigger PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>  
  $<INSTALL_INTERFACE:dune-triggers>
  )

install(TARGETS SupernovaTrigger
  EXPORT DuneTriggersTargets
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/Supernova"
  COMPONENT dev
  )
