#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Logging::Logging" for configuration ""
set_property(TARGET Logging::Logging APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Logging::Logging PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblogger.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Logging::Logging )
list(APPEND _IMPORT_CHECK_FILES_FOR_Logging::Logging "${_IMPORT_PREFIX}/lib/liblogger.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
