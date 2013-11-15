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
#include <st/Trunk.h>

#include <cmath>

#include <st/Sprite.h>

namespace st {

  void Trunk::render(std::mt19937_64& gen, Sprite& sprite) {
    cairo_t *cr = sprite.getContext();
    cairo_save(cr);

    double center = sprite.getSize() / 2.0;
    cairo_translate(cr, center, center);

    double radius_min = sprite.getSize() / 2.0 * m_def.radius_min;
    double radius_max = sprite.getSize() / 2.0 * m_def.radius_max;

    double lw = sprite.getSize() / 40.0;

    std::uniform_real_distribution<double> dist(radius_min, radius_max);

    cairo_move_to(cr, dist(gen), 0.0);

    for (int i = 1; i < m_def.faces; ++i) {
      double radius = dist(gen);
      double x = radius * std::cos(2.0 * M_PI * i / m_def.faces);
      double y = radius * std::sin(2.0 * M_PI * i / m_def.faces);

      cairo_line_to(cr, x, y);
    }

    cairo_close_path(cr);

//     cairo_arc(cr, 0.0, 0.0, radius, 0.0, 2.0 * M_PI);

    cairo_set_source_rgb(cr, 0.6, 0.3, 0.0);
    cairo_fill_preserve(cr);

    cairo_set_line_width(cr, lw);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    cairo_set_miter_limit(cr, 1e3);

    cairo_set_source_rgb(cr, 0.3, 0.15, 0.0);
    cairo_stroke(cr);

    /*
     * Add branches
     */

    int branches = m_def.branches;
    double branch_radius_max = sprite.getSize() / 2.0 * m_def.branch_radius_max;

    std::uniform_real_distribution<double> dist_angle(2.0 * M_PI / branches, 4.0 * M_PI / branches);
    std::uniform_real_distribution<double> dist_length(radius_min * 2.0, branch_radius_max);

    std::uniform_int_distribution<int> dist_breaks(2, 4);
    std::uniform_real_distribution<double> dist_break_angle(-0.2, 0.2);

    lw /= 2.0;
    cairo_set_line_width(cr, lw);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);

#define ANGLE_DIFF_TRUNK 0.12
#define ANGLE_DIFF_BRANCH 0.05

    double angle = 0.0;
    for (int i = 0; i < branches; ++i) {
      angle += dist_angle(gen);
      double length = dist_length(gen);

      int breaks = dist_breaks(gen);

      double break_angles[breaks];

      for (int j = 0; j < breaks; ++j) {
        break_angles[j] = dist_break_angle(gen);
      }

      double x1 = radius_min * std::cos(angle - ANGLE_DIFF_TRUNK);
      double y1 = radius_min * std::sin(angle - ANGLE_DIFF_TRUNK);

      cairo_move_to(cr, x1, y1);

      for (int j = 1; j < breaks; ++j) {
        double radius = (radius_min * (breaks - j + 1) + length * j) / (breaks + 1);
        double x = radius * std::cos(angle + break_angles[j] - ANGLE_DIFF_BRANCH);
        double y = radius * std::sin(angle + break_angles[j] - ANGLE_DIFF_BRANCH);
        cairo_line_to(cr, x, y);
      }

      double x2 = length * std::cos(angle);
      double y2 = length * std::sin(angle);

      cairo_line_to(cr, x2, y2);

      for (int j = breaks - 1; j >= 1; --j) {
        double radius = (radius_min * (breaks - j + 1) + length * j) / (breaks + 1);
        double x = radius * std::cos(angle + break_angles[j] + ANGLE_DIFF_BRANCH);
        double y = radius * std::sin(angle + break_angles[j] + ANGLE_DIFF_BRANCH);
        cairo_line_to(cr, x, y);
      }

      double x3 = radius_min * std::cos(angle + ANGLE_DIFF_TRUNK);
      double y3 = radius_min * std::sin(angle + ANGLE_DIFF_TRUNK);

      cairo_line_to(cr, x3, y3);
//       cairo_stroke_preserve(cr);

      cairo_close_path(cr);
      cairo_fill(cr);

    }

    cairo_restore(cr);
  }

}
