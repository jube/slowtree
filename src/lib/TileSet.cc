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
#include <st/TileSet.h>

#include <cassert>

#include <st/Sprite.h>

namespace st {

  TileSet::TileSet(const TileSetDef& def)
    : m_def(def) {
    if (!m_def.filename) {
      m_def.filename = "sprite.png";
    }

    if (m_def.size <= 0) {
      m_def.size = 64;
    }

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, m_def.size * m_def.width, m_def.size * m_def.height);
    assert(surface);
    m_cr = cairo_create(surface);
    assert(m_cr);
  }

  TileSet::~TileSet() {
    cairo_surface_t *surface = cairo_get_target(m_cr);
    cairo_destroy(m_cr);

    cairo_surface_write_to_png(surface, m_def.filename);
    cairo_surface_destroy(surface);
  }

  void TileSet::render(std::mt19937_64& gen, Renderable& renderable) {
    cairo_t *cr = getContext();

    SpriteDef def;
    def.size = m_def.size;
    def.cr = cr;

    for (int x = 0; x < m_def.width; ++x) {
      for (int y = 0; y < m_def.height; ++y) {
        cairo_save(cr);
        cairo_translate(cr, x * m_def.size, y * m_def.size);

        Sprite sprite(def);
        renderable.render(gen, sprite);

        cairo_restore(cr);
      }
    }

  }

}
