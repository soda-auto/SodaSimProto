cmake_minimum_required(VERSION 3.5)

if(NOT PROJECT_VERSION)
  set(PROJECT_VERSION 0.0.0.1)
endif()

project(generic-msgs VERSION ${PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(FULL_PROJECT_NAME soda-sim-proto)

add_library(${PROJECT_NAME} STATIC
  Private/LidarSserialization.cpp
  Private/RadarSerialization.cpp
  Private/PoseSerialization.cpp
  Private/UltrasonicSerialization.cpp
)
add_library(SodaSim::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>"
    "$<INSTALL_INTERFACE:include/>"
)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    OUTPUT_NAME ${FULL_PROJECT_NAME}
    POSITION_INDEPENDENT_CODE TRUE
)

## Installation
install(TARGETS ${PROJECT_NAME}
  EXPORT soda-sim-proto-targets
  ARCHIVE DESTINATION "lib" COMPONENT dev
)
install(DIRECTORY Public/ DESTINATION include COMPONENT dev)

export(
  EXPORT      soda-sim-proto-targets
  FILE        soda-sim-proto-targets.cmake
  NAMESPACE   SodaSim::
)
install(
  EXPORT      soda-sim-proto-targets
  FILE        soda-sim-proto-targets.cmake
  NAMESPACE   SodaSim::
  DESTINATION lib/cmake/SodaSimProto
  COMPONENT   dev
)

## Packaging
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/SodaSimProtoConfig.cmake.in
  ${PROJECT_BINARY_DIR}/SodaSimProtoConfig.cmake
  INSTALL_DESTINATION lib/cmake/SodaSimProto
)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/SodaSimProtoConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    ${PROJECT_BINARY_DIR}/SodaSimProtoConfig.cmake
    ${PROJECT_BINARY_DIR}/SodaSimProtoConfigVersion.cmake
  DESTINATION lib/cmake/SodaSimProto
  COMPONENT dev
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Version)
include(Packaging)

