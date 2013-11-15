
add_executable(slowtree slowtree.cc)
target_link_libraries(slowtree st0)

add_executable(slowbushes slowbushes.cc)
target_link_libraries(slowbushes st0)

install(
  TARGETS slowtree slowbushes
  RUNTIME DESTINATION bin
)
