cmake_minimum_required(VERSION 2.6)

project(ST CXX)

# include(CPackConfig.cmake)

find_package(PkgConfig REQUIRED)

pkg_check_modules(CAIRO REQUIRED cairo cairo-png)


add_definitions(-Wall -g -O2 -std=c++11)
include_directories("${ST_SOURCE_DIR}/include")

include_directories(${CAIRO_INCLUDE_DIRS})


add_subdirectory(lib)
add_subdirectory(bin)

# find_package(Doxygen)
#
# if(DOXYGEN_FOUND)
#   configure_file("${ST_SOURCE_DIR}/Doxyfile.cmake" "${ST_BINARY_DIR}/Doxyfile" @ONLY)
#   add_custom_target(doc ${DOXYGEN_EXECUTABLE} "${ST_BINARY_DIR}/Doxyfile")
# endif(DOXYGEN_FOUND)

configure_file("${ST_SOURCE_DIR}/libst0.pc.in" "${ST_BINARY_DIR}/libst0.pc" @ONLY)
install(
  FILES "${ST_BINARY_DIR}/libst0.pc"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig"
)

# install(
#   DIRECTORY "${ST_SOURCE_DIR}/include/st"
#   DESTINATION include
# )
