/*
 * SlowTree
 * a 2D top-down vegetation sprite generator
 *
 * Copyright (c) 2014, Julien Bernard
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
#include <vector>

#include <cairo.h>

#include <st/Color.h>
#include <st/Geometry.h>

namespace st {

  class Path {
  public:
    enum class Element {
      MOVE_TO,
      LINE_TO,
      CURVE_TO,
      CLOSE,
    };

    Path& moveTo(Vector2 p);
    Path& lineTo(Vector2 p);
    Path& curveTo(Vector2 p1, Vector2 p2, Vector2 p3);
    void close();

    typedef typename std::vector<Vector2>::const_iterator points_const_iterator;

    points_const_iterator points_begin() const {
      return m_points.begin();
    }

    points_const_iterator points_end() const {
      return m_points.end();
    }

    typedef typename std::vector<Element>::const_iterator const_iterator;

    const_iterator begin() const {
      return m_elements.begin();
    }

    const_iterator end() const {
      return m_elements.end();
    }

  private:
    std::vector<Element> m_elements;
    std::vector<Vector2> m_points;
  };

  class Renderer {
  public:
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    void save();
    void restore();

    void translate(Vector2 vec);

    void setLineJoinMiter(double limit = 1e3);
    void setLineJoinRound();

    void setLineCapRound();

    void lineStroke(Vector2 p1, Vector2 p2, double line_width, Color color);

    void arcStroke(Vector2 center, double radius, double angle1, double angle2, double line_width, Color color);
    void arcFill(Vector2 center, double radius, double angle1, double angle2, Color color);
    void arcClip(Vector2 center, double radius, double angle1, double angle2);

    void pathStroke(const Path& path, double line_width, Color color);
    void pathFill(const Path& path, Color color);
    void pathClip(const Path& path);

    void radialGradient(Vector2 p1, double radius1, Color color1, Vector2 p2, double radius2, Color color2);

    void resetClip();

    template<class Func>
    void tweakContext(Func func) {
      func(m_cr);
    }

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
