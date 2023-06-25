# Define Project and Required versions
cmake_minimum_required(VERSION 3.26)
project(WEBPP VERSION 0.0.1 DESCRIPTION "a lightweight c++ backend")

# Define included directories
include(GNUInstallDirs)
include_directories(include)
include_directories(src)# Set dependencies

# Set Source Files, Header Files and Required libs
set(SOURCE_FILES
  src/BaseSocket.cpp
  src/BindingSocket.cpp
  src/Responder.cpp
  src/Server.cpp
  src/HttpHelpers.cpp
)

set(HEADER_FILES
  include/BaseSocket.hpp
  include/BindingSocket.hpp
  include/Responder.hpp
  include/Server.hpp
  include/HttpHelpers.hpp
)

set(REQUIRED_LIBRARIES
  openssl
)

add_library(${PROJECT_NAME}
  SHARED
    ${SOURCE_FILES}
)

target_sources(${PROJECT_NAME}
  PRIVATE
    ${SOURCE_FILES}
)

find_package(OpenSSL REQUIRED)

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

configure_file(WEBPP.pc.in WEBPP.pc @ONLY)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Link OPENSSL
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::applink)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(FILES ${CMAKE_BINARY_DIR}/webpp.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
