cmake_minimum_required(VERSION 3.26)

project(WEBPP VERSION 0.0.1 DESCRIPTION "a lightweight c++ backend")

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

include(GNUInstallDirs)
include_directories(include)

add_library(${PROJECT_NAME} SHARED src/webpp.cpp)

target_sources(${PROJECT_NAME}
  PRIVATE
    src/Sockets/BaseSocket.cpp
    src/Sockets/BindingSocket.cpp
    src/Responder.cpp
    src/Router.cpp
    src/Server.cpp
    src/HttpHelpers.cpp
)

set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION 0
  PUBLIC_HEADER include/webpp.hpp
)

configure_file(WEBPP.pc.in WEBPP.pc @ONLY)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${CMAKE_BINARY_DIR}/webpp.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
