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
#include <st/Renderer.h>

#include <cassert>

namespace st {

  Path& Path::moveTo(Vector2 p) {
    m_elements.push_back(Element::MOVE_TO);
    m_points.push_back(p);
    return *this;
  }

  Path& Path::lineTo(Vector2 p) {
    m_elements.push_back(Element::LINE_TO);
    m_points.push_back(p);
    return *this;
  }

  Path& Path::curveTo(Vector2 p1, Vector2 p2, Vector2 p3) {
    m_elements.push_back(Element::CURVE_TO);
    m_points.push_back(p1);
    m_points.push_back(p2);
    m_points.push_back(p3);
    return *this;
  }

  void Path::close() {
    m_elements.push_back(Element::CLOSE);
  }



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

  void Renderer::translate(Vector2 vec) {
    cairo_translate(m_cr, vec.x, vec.y);
  }


  void Renderer::setLineJoinMiter(double limit) {
    cairo_set_line_join(m_cr, CAIRO_LINE_JOIN_MITER);
    cairo_set_miter_limit(m_cr, limit);
  }

  void Renderer::setLineJoinRound() {
    cairo_set_line_join(m_cr, CAIRO_LINE_JOIN_ROUND);
  }

  void Renderer::setLineCapRound() {
    cairo_set_line_cap(m_cr, CAIRO_LINE_CAP_ROUND);
  }

  void Renderer::lineStroke(Vector2 p1, Vector2 p2, double line_width, Color color) {
    Path path;
    path.moveTo(p1).lineTo(p2);
    pathStroke(path, line_width, color);
  }

  void Renderer::arcStroke(Vector2 center, double radius, double angle1, double angle2, double line_width, Color color) {
    cairo_arc(m_cr, center.x, center.y, radius, angle1, angle2);
    cairo_set_line_width(m_cr, line_width);
    cairo_set_source_rgba(m_cr, color.r, color.g, color.b, color.a);
    cairo_stroke(m_cr);
  }

  void Renderer::arcFill(Vector2 center, double radius, double angle1, double angle2, Color color) {
    cairo_arc(m_cr, center.x, center.y, radius, angle1, angle2);
    cairo_set_source_rgba(m_cr, color.r, color.g, color.b, color.a);
    cairo_fill(m_cr);
  }

  void Renderer::arcClip(Vector2 center, double radius, double angle1, double angle2) {
    cairo_arc(m_cr, center.x, center.y, radius, angle1, angle2);
    cairo_clip(m_cr);
  }

  static void pathDefine(cairo_t *cr, const Path& path) {
    auto it = path.points_begin();

    for (auto elt : path) {
      switch(elt) {
      case Path::Element::MOVE_TO: {
        auto p = *it++;
        cairo_move_to(cr, p.x, p.y);
        break;
      }

      case Path::Element::LINE_TO: {
        auto p = *it++;
        cairo_line_to(cr, p.x, p.y);
        break;
      }

      case Path::Element::CURVE_TO: {
        auto p1 = *it++;
        auto p2 = *it++;
        auto p3 = *it++;
        cairo_curve_to(cr, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
        break;
      }

      case Path::Element::CLOSE:
        cairo_close_path(cr);
        break;
      }
    }

    assert(it == path.points_end());
  }

  void Renderer::pathStroke(const Path& path, double line_width, Color color) {
    pathDefine(m_cr, path);
    cairo_set_line_width(m_cr, line_width);
    cairo_set_source_rgba(m_cr, color.r, color.g, color.b, color.a);
    cairo_stroke(m_cr);
  }

  void Renderer::pathFill(const Path& path, Color color) {
    pathDefine(m_cr, path);
    cairo_set_source_rgba(m_cr, color.r, color.g, color.b, color.a);
    cairo_fill(m_cr);
  }

  void Renderer::pathClip(const Path& path) {
    pathDefine(m_cr, path);
    cairo_clip(m_cr);
  }

  void Renderer::radialGradient(Vector2 p1, double radius1, Color color1, Vector2 p2, double radius2, Color color2) {
    cairo_pattern_t *pattern = cairo_pattern_create_radial(p1.x, p1.y, radius1, p2.x, p2.y, radius2);
    cairo_pattern_add_color_stop_rgba(pattern, 0.0, color1.r, color1.g, color1.b, color1.a);
    cairo_pattern_add_color_stop_rgba(pattern, 1.0, color2.r, color2.g, color2.b, color2.a);
    cairo_mask(m_cr, pattern);
    cairo_pattern_destroy(pattern);
  }

  void Renderer::resetClip() {
    cairo_reset_clip(m_cr);
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

