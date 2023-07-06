# Define Project and Required versions
cmake_minimum_required(VERSION 3.24)
project(WEBPP VERSION 0.0.1 DESCRIPTION "a lightweight c++ backend")

# Define included directories
include(GNUInstallDirs)
include_directories(include)
include_directories(src)

# Set Source Files, Header Files and Required libs
set(SOURCE_FILES
  src/BaseSocket.cpp
  src/BindingSocket.cpp
  src/Responder.cpp
  src/Server.cpp
  src/HttpHelpers.cpp
  src/Router.cpp
)

set(HEADER_FILES
  include/BaseSocket.hpp
  include/BindingSocket.hpp
  include/Responder.hpp
  include/Server.hpp
  include/HttpHelpers.hpp
	include/webpp.hpp
  include/Router.hpp
)

set(REQUIRED_LIBRARIES
  ...
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_sources(${PROJECT_NAME}
  PRIVATE
    src/BaseSocket.cpp
    src/BindingSocket.cpp
    src/Responder.cpp
    src/Server.cpp
    src/HttpHelpers.cpp
)

set_target_properties(
	${PROJECT_NAME}
PROPERTIES
	VERSION ${PROJECT_VERSION}
  SOVERSION 0
  PUBLIC_HEADER "${HEADER_FILES}"
	ARCHIVE_OUTPUT_DIRECTORY "lib"
	LIBRARY_OUTPUT_DIRECTORY "lib"
	OUTPUT_NAME ${PROJECT_NAME}
)

configure_file(webpp.pc.in webpp.pc @ONLY)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(FILES ${CMAKE_BINARY_DIR}/webpp.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
