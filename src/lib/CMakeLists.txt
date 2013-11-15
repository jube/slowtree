include_directories(${CAIRO_INCLUDE_DIRS})

set(LIBST_SRC
  Foliage.cc
  Renderable.cc
  Sprite.cc
  TileSet.cc
  Tree.cc
  Trunk.cc
)

add_library(st0 SHARED
  ${LIBST_SRC}
)

target_link_libraries(st0 ${CAIRO_LIBRARIES})

install(
  TARGETS st0
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
