cmake_minimum_required(VERSION 3.13)

project(DuneTrigger)

set(DUNETRIGGER_MAJOR_VERSION "0")
set(DUNETRIGGER_MINOR_VERSION "0")
set(DUNETRIGGER_PATCH_VERSION "0")
set(DUNETRIGGER_VERSION ${DUNETRIGGER_MAJOR_VERSION}_${DUNETRIGGER_MINOR_VERSION}_${DUNETRIGGER_PATCH_VERSION})

# # Offer the user the choice of overriding the installation directories
# set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
# set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
# set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

# set(DEF_INSTALL_CMAKE_DIR CMake)

# set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# # make relative paths absolute (needed later on)
# foreach(p LIB BIN INCLUDE CMAKE)
#   set(var INSTALL_${p}_DIR)
#   if(NOT IS_ABSOLUTE "${${var}}")
#     set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
#   endif()
# endforeach()

# # set up include-directories
# include_directories("${PROJECT_SOURCE_DIR}")


# # SETUP BOOST
# execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
#   OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
#   OUTPUT_STRIP_TRAILING_WHITESPACE
#   )

# # if the distribution is scientific linux, then setup boost in a different way (not using the cmake file from boost)
# string(FIND "${LSB_RELEASE_ID_SHORT}" "Scientific" _cmp)
# if (_cmp GREATER -1)
#   set(Boost_NO_BOOST_CMAKE ON)
# else()
#   string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -std=c++1y")
# endif()

# find_package(Boost REQUIRED)
# set(BOOST_INCLUDE_DIRS $boost_installation_prefix/include)
# find_package(Threads REQUIRED)


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

  list(LENGTH ${CLASSDEF} SIZE_)
  # REALLY DONT UNDERSTAND WHY THIS DOESNT RETURN THE NUMBER OF MATCHES
  # IGNORE FOR NOW
  
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
      $<INSTALL_INTERFACE:include/>
      )
    target_compile_options(${ALGOLIBNAME} PRIVATE -Wall -Wextra -pedantic -Werror)

    install(TARGETS ${ALGOLIBNAME}
      EXPORT DuneTriggersTargets
      LIBRARY DESTINATION lib
      PUBLIC_HEADER DESTINATION include
      )

  else()
    ## CANT GET THIS TO WORK.
    ## DOING IT THE UGLY WAY @E#*)&1$%!!
    #   # This is the standard case, header only files -> we create an "interface library"
    add_library(${ALGOLIBNAME} INTERFACE)
    message(STATUS "Created INTERFACE (empty) lib: " ${ALGOLIBNAME})
    
    #   target_link_libraries(${ALGOLIBNAME} INTERFACE DuneTriggers)

    #   message(STATUS "Created INTERFACE lib: " ${ALGOLIBNAME})

    #   get_last_dir(${CMAKE_CURRENT_SOURCE_DIR})

    #   foreach (H ${HH_FILES})
    #     string (REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" H_RELAT ${H})
    #     message(STATUS "${H} -> ${H_RELAT}")
    #     list(APPEND HH_FILES_RELAT ${H_RELAT})
    #   endforeach()
    
    #   foreach (H ${HH_FILES_RELAT})
    #     message(STATUS "${H} -> realt")
    #   endforeach()
    
    #   target_sources(${ALGOLIBNAME} INTERFACE
    #     $<BUILD_INTERFACE:${HH_FILES_RELAT}>
    #     $<INSTALL_INTERFACE:include/>
    #     )
    
    #   target_include_directories(${ALGOLIBNAME} INTERFACE
    #     $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    #     $<INSTALL_INTERFACE:include/dune-triggers/${A}>
    #     )
    
    #   target_compile_options(${ALGOLIBNAME} INTERFACE -Wall -Wextra -pedantic -Werror)
    
    #   install(TARGETS ${ALGOLIBNAME}
    #     EXPORT DuneTriggersTargets
    #     LIBRARY DESTINATION lib
    #     PUBLIC_HEADER DESTINATION include
    #     )p
  endif()
endfunction()


glob_carefully("dune-triggers"   "*.h*" BASE_H)
glob_carefully("dune-triggers/*" "*.h*" ALGS_H)

install (FILES ${ALGS_H}
  DESTINATION include
  )

install (FILES ${BASE_H}
  DESTINATION include
  )

add_subdirectory(dune-triggers)
add_subdirectory(autogen)

install(EXPORT DuneTriggersTargets DESTINATION ${CMAKE_INSTALL_PREFIX})
# install(DIRECTORY dune-triggers DESTINATION ${CMAKE_INSTALL_PREFIX})

export(PACKAGE DuneTriggers)


# # # Create the DuneTriggersConfig.cmake and DuneTriggersConfigVersion files
# # file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}" "${INSTALL_INCLUDE_DIR}")

# # ... for the build tree
# set(CONF_INCLUDE_DIRS "${PROJECT_BINARY_DIR}")
# configure_file(DuneTriggersConfig.cmake.in "${PROJECT_BINARY_DIR}/DuneTriggersConfig.cmake" @ONLY)

# # ... for the install tree
# set(CONF_INCLUDE_DIRS "\${DUNETRIGGERS_CMAKE_DIR}/${REL_INCLUDE_DIR}")
# configure_file(DuneTriggersConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DuneTriggersConfig.cmake" @ONLY)

# # ... for both
# configure_file(DuneTriggersConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/DuneTriggersConfigVersion.cmake" @ONLY)

# # Install the DuneTriggersConfig.cmake and DuneTriggersConfigVersion.cmake
# install(FILES
#   "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/DuneTriggersConfig.cmake"
#   "${PROJECT_BINARY_DIR}/DuneTriggersConfigVersion.cmake"
#   DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# # Install the export set for use with the install-tree
# install(EXPORT DuneTriggersTargets DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
