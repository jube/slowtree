/*
 * SlowTree
 * a 2D top-down vegetation sprite generator
 *
 * Copyright (c) 2013-2014, Julien Bernard
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
  }

  TileSet::~TileSet() {
  }

  void TileSet::render(Engine& engine, Renderable& renderable) {
    Renderer renderer = Renderer::create(m_def.size * m_def.width, m_def.size * m_def.height);

    SpriteDef def;
    def.size = m_def.size;

    for (int x = 0; x < m_def.width; ++x) {
      for (int y = 0; y < m_def.height; ++y) {
        RendererStateGuard guard(renderer);

        Vector2 origin{ static_cast<double>(x) * m_def.size, static_cast<double>(y) * m_def.size };
        renderer.translate(origin);

        Sprite sprite(def);
        renderable.render(engine, renderer, sprite);
      }
    }

    renderer.saveToFile(m_def.filename);
  }

}
