#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Logging::Logging" for configuration ""
set_property(TARGET Logging::Logging APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Logging::Logging PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liblogger.so.0.0.2"
  IMPORTED_SONAME_NOCONFIG "liblogger.so.0.0.2"
  )

list(APPEND _IMPORT_CHECK_TARGETS Logging::Logging )
list(APPEND _IMPORT_CHECK_FILES_FOR_Logging::Logging "${_IMPORT_PREFIX}/lib/liblogger.so.0.0.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
