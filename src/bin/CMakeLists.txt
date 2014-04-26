include_directories(${CAIRO_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

add_executable(slowtree slowtree.cc)
target_link_libraries(slowtree st0)

add_executable(slowbushes slowbushes.cc)
target_link_libraries(slowbushes st0)

add_executable(slowrocks slowrocks.cc)
target_link_libraries(slowrocks st0)

install(
  TARGETS slowtree slowbushes slowrocks
  RUNTIME DESTINATION bin
)
