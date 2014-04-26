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
#include <st/Rock.h>

#include <cassert>
#include <algorithm>
#include <vector>

#include <st/Sprite.h>

#define LIGHT_GREY 0.7
#define MEDIUM_GREY 0.6
#define DARK_GREY 0.5

namespace st {

  void Rock::render(Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);
    renderer.translate(sprite.getCenter());

    double radius_max = sprite.getSize() / 2.0 * m_def.radius_max;
    double radius_min = sprite.getSize() / 2.0 * m_def.radius_min;

    std::uniform_real_distribution<double> dist_length(radius_min, radius_max);

    std::vector<Vector2> points;
    points.push_back({ dist_length(engine()), 0.0 });

    for (int i = 1; i < m_def.faces; ++i) {
      double length = dist_length(engine());

      auto p = Vector2::makePolar(length, i * 2.0 * M_PI / m_def.faces);
      points.push_back(p);
    }

#define EDGES_COUNT_MAX 2

    std::uniform_int_distribution<int> dist_edges_count(1, EDGES_COUNT_MAX);

    std::vector<int> edges_count;
    int edges_left = m_def.faces;

    for (;;) {
      int edges = dist_edges_count(engine());

      edges_count.push_back(edges);
      edges_left -= edges;

      if (edges_left <= EDGES_COUNT_MAX) {
        edges_count.push_back(edges_left);
        break;
      }
    }

    auto count = edges_count.size();

    std::uniform_real_distribution<double> dist_length2(radius_min * 0.4, radius_min * 0.8);

    std::vector<Vector2> points2;

    for (std::size_t i = 0; i < count; ++i) {
      double length = dist_length2(engine());

      auto p = Vector2::makePolar(length, i * 2.0 * M_PI / count);
      points2.push_back(p);
    }


    // draw

    Path path;
    path.moveTo(points[0]);

    for (int i = 1; i < m_def.faces; ++i) {
      path.lineTo(points[i]);
    }

    path.close();

    renderer.pathFill(path, Color::grey(MEDIUM_GREY));

    double line_width = sprite.getSize() / 40.0;
    renderer.pathStroke(path, line_width, Color::grey(DARK_GREY));


    Path path2;
    path2.moveTo(points2[0]);

    for (std::size_t i = 0; i < count; ++i) {
      path2.lineTo(points2[i]);
    }

    path2.close();

    renderer.pathFill(path2, Color::grey(LIGHT_GREY));

    line_width /= 2;
    renderer.pathStroke(path2, line_width, Color::grey(DARK_GREY));


    line_width /= 2;
    int j = 0; int k = 0;
    for (auto edges : edges_count) {
      renderer.lineStroke(points[j], points2[k], line_width, Color::grey(DARK_GREY));

      j += edges;
      k += 1;
    }

  }

}
