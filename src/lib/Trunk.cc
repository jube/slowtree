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
#include <st/Trunk.h>

#include <cmath>

#include <st/Sprite.h>

namespace st {

  void Trunk::render(Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);
    renderer.translate(sprite.getCenter());

    double radius_min = sprite.getSize() / 2.0 * m_def.radius_min;
    double radius_max = sprite.getSize() / 2.0 * m_def.radius_max;

    std::uniform_real_distribution<double> dist(radius_min, radius_max);

    Path path;
    path.moveTo({ dist(engine()), 0.0 });

    for (int i = 1; i < m_def.faces; ++i) {
      double radius = dist(engine());

      auto p = Vector2::makePolar(radius, 2.0 * M_PI * i / m_def.faces);
      path.lineTo(p);
    }

    path.close();

    renderer.pathFill(path, { 0.6, 0.3, 0.0, 1.0 });

    double line_width = sprite.getSize() / 40.0;
    renderer.setLineJoinMiter();
    renderer.pathStroke(path, line_width, { 0.3, 0.15, 0.0, 1.0 });
  }

}
