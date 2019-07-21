cmake_minimum_required(VERSION 3.14.5)
project(liblogger VERSION 1.0.0.0 LANGUAGES CXX DESCRIPTION "Logger for C++ projects." HOMEPAGE_URL "")

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

set(libsrc src/logger.cpp)
add_library(objlib OBJECT ${libsrc})

set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(logger_shared SHARED $<TARGET_OBJECTS:objlib>)
add_library(logger STATIC $<TARGET_OBJECTS:objlib>)

add_library(Logging::logger ALIAS logger)

target_compile_features(logger PUBLIC cxx_std_17)

target_include_directories(logger
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Logging)

install(TARGETS logger
    EXPORT logger-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

#This is required so that the exported target has the name Logging and not logger
set_target_properties(logger PROPERTIES EXPORT_NAME Logging)
set_target_properties(logger PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(logger PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT logger-targets
  FILE
    LoggingTargets.cmake
  NAMESPACE
    Logging::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LoggingConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/LoggingConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/LoggingConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LoggingConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/LoggingConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree

export(EXPORT logger-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/LoggingTargets.cmake NAMESPACE Logging::)

#Register package in user's package registry
export(PACKAGE Logging)