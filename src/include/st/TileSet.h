/*
 * SlowTree
 * a 2D top-down vegetation sprite generator
 *
 * Copyright (c) 2013, Julien Bernard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

    void render(Engine& engine, Renderable& renderable);

    cairo_t *getContext() {
      return m_cr;
    }

  private:
    TileSetDef m_def;
    cairo_t *m_cr;
  };

}


#endif // ST_TILE_SET_H
