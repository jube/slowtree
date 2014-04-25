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
#include <st/Renderer.h>

#include <cassert>

namespace st {
  Renderer::~Renderer() {
    cairo_destroy(m_cr);
    cairo_surface_destroy(m_surface);
  }

  void Renderer::save() {
    cairo_save(m_cr);
  }

  void Renderer::restore() {
    cairo_restore(m_cr);
  }

  void Renderer::saveToFile(std::string filename) {
    cairo_surface_write_to_png(m_surface, filename.c_str());
  }

  Renderer Renderer::create(int width, int height) {
    auto surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    assert(surface);
    auto cr = cairo_create(surface);
    assert(cr);
    return Renderer(cr, surface);
  }

}

