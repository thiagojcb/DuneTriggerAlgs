cmake_minimum_required(VERSION 3.13)

project(DuneTriggerAlgs)
include(CMakePackageConfigHelpers)
set(DUNETRIGGERALGS_MAJOR_VERSION "0")
set(DUNETRIGGERALGS_MINOR_VERSION "0")
set(DUNETRIGGERALGS_PATCH_VERSION "0")
set(DUNETRIGGERALGS_VERSION ${DUNETRIGGERALGS_MAJOR_VERSION}_${DUNETRIGGERALGS_MINOR_VERSION}_${DUNETRIGGERALGS_PATCH_VERSION})

set(LIBRARIES_INSTALL "lib")
set(INCLUDES_INSTALL "include")

function(get_last_dir FILEPATH)
  # This function get the latest directory name before the file
  # get_filename_component(DIRNAME ${FILEPATH} DIRECTORY)
  string(FIND ${FILEPATH} "/" P REVERSE)
  string(LENGTH ${FILEPATH} L)
  # The beauty of cmake exposed right here
  math(EXPR L "${L}-${P}")
  math(EXPR P "${P}+1")
  
  string(SUBSTRING ${FILEPATH} ${P} ${L} LASTDIR)
  set(LASTDIR ${LASTDIR} PARENT_SCOPE)
endfunction()


function(get_libname FILEPATH)
  get_last_dir(${FILEPATH})
  
  # now grabs the library name
  set(ALGOLIBNAME "${LASTDIR}Trigger" PARENT_SCOPE)
endfunction()

function (glob_carefully FILEPATH REGEX RET)
  file(GLOB FILES "${FILEPATH}/${REGEX}")
  
  foreach (F ${FILES})
    string(REGEX MATCH ".*~" CHECK ${F})

    if (NOT CHECK STREQUAL "")
      list(REMOVE_ITEM FILES ${F})
    endif()
  endforeach()
  
  set(${RET} ${FILES} PARENT_SCOPE)
endfunction()

function (glob_recursive_relat_carefully FILEPATH REGEX RET)
  file(GLOB_RECURSE FILES
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${FILEPATH}/${REGEX}")
  
  foreach (F ${FILES})
    string(REGEX MATCH ".*~" CHECK ${F})

    if (NOT CHECK STREQUAL "")
      list(REMOVE_ITEM FILES ${F})
    endif()
  endforeach()
  
  set(${RET} ${FILES} PARENT_SCOPE)
endfunction()


function (set_alg_type_name_lib FILEPATH)
  set(ALGONAME "" PARENT_SCOPE)
  set(ALGOTYPE "" PARENT_SCOPE)
  set(ALGOLIBNAME "" PARENT_SCOPE)
  
  #grabs the header only
  string(REGEX MATCH ".*h.*" CHECK ${FILEPATH})
  if (${CHECK} STREQUAL "")
    return()
  endif()
  
  #rids of the temp files
  string(REGEX MATCH ".*\\~" CHECK ${FILEPATH})
  if (NOT ${CHECK} STREQUAL "")
    message(STATUS "Ignoring " ${FILEPATH} " temporary file")
    return()
  endif()

  file(READ ${FILEPATH} WHOLEFILE)
  string(REGEX MATCHALL "class.*:[ \t\r\n]*public[ \t\r\n]*Trigger.*Maker[ \t\r\n]*[,a-zA-Z0-1 ]*[ \t\r\n]*{"
    CLASSDEF "${WHOLEFILE}"
    )
  
  if ("${CLASSDEF}" STREQUAL "")
    message(STATUS "Couldn't work out which trigger maker type from file " ${FILEPATH}
      " This is because the cmake script looks for the pattern \"class *: public Trigger*Maker *{\" and couldn't encounter it in this file, maybe this is fine and it's just another included file which doesn't actually have Trigger*Maker class inside it?")
    return()
  endif ()

  string(REGEX MATCH "public[ \t\r\n]*Trigger.*Maker"
    ALGOTYPE "${CLASSDEF}"
    )
  
  string(REGEX MATCH "Trigger.*Maker"
    ALGOTYPE "${ALGOTYPE}"
    )

  string(LENGTH ${ALGOTYPE} L)

  # "trigger" has 7 letters and "maker" has 5 letters, such ugly syntax
  math(EXPR L "${L}-7-5")

  string(SUBSTRING ${ALGOTYPE} 7 ${L} ALGOTYPE)
  # NOW WE HAVE THE TYPE (Candidate, Primitive, Decision) OF THE ALGORITHM
  
  string(REGEX MATCH "class.*:" ALGONAME ${CLASSDEF})

  string(REGEX REPLACE "[ \n\t\r]" "" ALGONAME ${ALGONAME} )
  string(LENGTH ${ALGONAME} L)
  math(EXPR L "${L}-1-5") # "class" has 5 letters + 1 letter for the semicolon
  string(SUBSTRING ${ALGONAME} 5 ${L} ALGONAME)

  # GREAT! NOW WE HAVE THE NAME OF THE ALGORITHM
  get_filename_component(DIRNAME ${FILEPATH} DIRECTORY)
  get_libname(${DIRNAME})

  set(ALGONAME ${ALGONAME} PARENT_SCOPE)
  set(ALGOTYPE ${ALGOTYPE} PARENT_SCOPE)
  set(ALGOLIBNAME ${ALGOLIBNAME} PARENT_SCOPE)
endfunction()


function (add_dune_trigger_lib)
  get_libname(${CMAKE_CURRENT_SOURCE_DIR})
    
  # grabs the .cc, .cxx, .c, .cpp files
  glob_carefully("." "*.h*" HH_FILES)
  glob_carefully("." "*.c*" CC_FILES)

  if (CC_FILES)
    # This is the standard case, header+cc files -> we create a library
    add_library(${ALGOLIBNAME} SHARED ${HH_FILES} ${CC_FILES})

    set_target_properties(${ALGOLIBNAME}
      PROPERTIES
      LINKER_LANGUAGE CXX
      )
    
    message(STATUS "Created lib: " ${ALGOLIBNAME})

    list(APPEND ALL_LIBS $ENV{ALL_LIBS} ${ALGOLIBNAME})

    get_last_dir(${CMAKE_CURRENT_SOURCE_DIR})
    
    target_include_directories(${ALGOLIBNAME} PUBLIC
      $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
      $<INSTALL_INTERFACE:${INCLUDES_INSTALL}/>
      )

    target_compile_options(${ALGOLIBNAME} PRIVATE -Wall -Wextra -pedantic -Werror)

    install(TARGETS ${ALGOLIBNAME}
      EXPORT DuneTriggerAlgsTargets
      LIBRARY DESTINATION ${LIBRARIES_INSTALL}
      PUBLIC_HEADER DESTINATION ${INCLUDES_INSTALL}/dune-triggers-algs/${ALGOLIBNAME}
      )

  else()
    # This is the standard case, header only files -> we create an "interface library"
    add_library(${ALGOLIBNAME} INTERFACE)
    message(STATUS "Created INTERFACE (empty) lib: " ${ALGOLIBNAME})

    install(FILES ${HH_FILES} DESTINATION ${INCLUDES_INSTALL}/dune-triggers-algs/${ALGOLIBNAME})
  endif()
endfunction()

glob_recursive_relat_carefully(${CMAKE_CURRENT_SOURCE_DIR}/dune-trigger-algs "*.h*" HEADERS)

foreach(F ${HEADERS})
  message(STATUS ${F})
  get_filename_component(INC ${F} DIRECTORY)
  install(FILES ${F} DESTINATION ${INCLUDES_INSTALL}/${INC})
endforeach()

CONFIGURE_PACKAGE_CONFIG_FILE(DuneTriggerAlgsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/DuneTriggerAlgsConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}
  PATH_VARS INCLUDES_INSTALL LIBRARIES_INSTALL
  )

add_subdirectory(dune-trigger-algs)
add_subdirectory(autogen)

install(EXPORT DuneTriggerAlgsTargets DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DuneTriggerAlgsConfig.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  )


export(PACKAGE DuneTriggerAlgs)
