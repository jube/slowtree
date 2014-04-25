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
#include <st/Rock.h>

#include <algorithm>
#include <vector>

#include <st/Sprite.h>

#define LIGHT_GREY 0.7
#define MEDIUM_GREY 0.6
#define DARK_GREY 0.5

namespace st {

  void Rock::render(Engine& engine, Sprite& sprite) {
    cairo_t *cr = sprite.getContext();
    cairo_save(cr);

    double center = sprite.getSize() / 2.0;
    cairo_translate(cr, center, center);

    double lw = sprite.getSize() / 40.0;
    cairo_set_line_width(cr, lw);

    double radius_max = sprite.getSize() / 2.0 * m_def.radius_max;
    double radius_min = sprite.getSize() / 2.0 * m_def.radius_min;

    std::uniform_real_distribution<double> dist_length(radius_min, radius_max);

    cairo_move_to(cr, dist_length(engine()), 0.0);

    for (int i = 1; i < m_def.faces; ++i) {
      double length = dist_length(engine());

      double x = length * std::cos(i * 2.0 * M_PI / m_def.faces);
      double y = length * std::sin(i * 2.0 * M_PI / m_def.faces);

      cairo_line_to(cr, x, y);
    }

    cairo_close_path(cr);

    cairo_set_source_rgb(cr,LIGHT_GREY, LIGHT_GREY, LIGHT_GREY);
    cairo_fill_preserve(cr);

    cairo_set_source_rgb(cr,DARK_GREY, DARK_GREY, DARK_GREY);
    cairo_stroke_preserve(cr);

    cairo_clip(cr);

    cairo_pattern_t *pattern = cairo_pattern_create_radial(
      0.0, 0.0, 0.0, 0.0, 0.0, radius_max);
    cairo_pattern_add_color_stop_rgba(pattern, 0.0, DARK_GREY, DARK_GREY, DARK_GREY, 1.0);
    cairo_pattern_add_color_stop_rgba(pattern, 1.0, LIGHT_GREY, LIGHT_GREY, LIGHT_GREY, 0.0);

    cairo_mask(cr, pattern);
    cairo_pattern_destroy(pattern);

    cairo_restore(cr);
  }

}
