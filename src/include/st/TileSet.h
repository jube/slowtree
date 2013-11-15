#ifndef ST_TILE_SET_H
#define ST_TILE_SET_H

#include <cairo.h>

#include "Renderable.h"

namespace st {

  struct TileSetDef {
    const char *filename = "tileset.png";
    int width = 1;
    int height = 1;
    int size = 256;
  };

  class TileSet {
  public:
    TileSet(const TileSetDef& def);
    ~TileSet();

    void render(std::mt19937_64& gen, Renderable& renderable);

    cairo_t *getContext() {
      return m_cr;
    }

  private:
    TileSetDef m_def;
    cairo_t *m_cr;
  };

}


#endif // ST_TILE_SET_H
