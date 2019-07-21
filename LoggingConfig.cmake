get_filename_component(Logging_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

list(APPEND CMAKE_MODULE_PATH ${Logging_CMAKE_DIR})

list(REMOVE_AT CMAKE_MODULE_PATH -1)

if(NOT TARGET Logging::Logging)
    include("${Logging_CMAKE_DIR}/LoggingTargets.cmake")
endif()

set(Logging_LIBRARIES Logging::Logging)
