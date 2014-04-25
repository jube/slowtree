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

  void Rock::render(Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);
    renderer.translate(sprite.getCenter());

    double radius_max = sprite.getSize() / 2.0 * m_def.radius_max;
    double radius_min = sprite.getSize() / 2.0 * m_def.radius_min;

    std::uniform_real_distribution<double> dist_length(radius_min, radius_max);

    Path path;
    path.moveTo({ dist_length(engine()), 0.0 });

    for (int i = 1; i < m_def.faces; ++i) {
      double length = dist_length(engine());

      auto p = Vector2::makePolar(length, i * 2.0 * M_PI / m_def.faces);
      path.lineTo(p);
    }

    path.close();

    renderer.pathFill(path, Color::grey(LIGHT_GREY));

    double line_width = sprite.getSize() / 40.0;
    renderer.pathStroke(path, line_width, Color::grey(DARK_GREY));

    renderer.pathClip(path);
    renderer.radialGradient(
      { 0.0, 0.0 }, 0.0,        Color::grey(DARK_GREY, 1.0),
      { 0.0, 0.0 }, radius_max, Color::grey(LIGHT_GREY, 0.0)
    );
  }

}
