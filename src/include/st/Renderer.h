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
#ifndef ST_RENDERER_H
#define ST_RENDERER_H

#include <string>

#include <cairo.h>

namespace st {
  class Renderer {
  public:
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    void save();
    void restore();


    void saveToFile(std::string filename);

    static Renderer create(int width, int height);

  private:
    Renderer(cairo_t *cr, cairo_surface_t *surface)
    : m_cr(cr)
    , m_surface(surface)
    {
    }

    cairo_t *m_cr;
    cairo_surface_t *m_surface;
  };

  class RendererStateGuard {
  public:
    explicit RendererStateGuard(Renderer& renderer)
    : m_renderer(renderer) {
      m_renderer.save();
    }

    RendererStateGuard(const RendererStateGuard&) = delete;

    ~RendererStateGuard() {
      m_renderer.restore();
    }

  private:
    Renderer& m_renderer;
  };

}

#endif // ST_RENDERER_H
