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
#include <st/Fruits.h>

#include <algorithm>
#include <vector>

#include <st/Sprite.h>

namespace st {

  void Fruits::render(Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);
    renderer.translate(sprite.getCenter());

    double radius_max = sprite.getSize() / 2.0 * m_def.radius_max;
    double local_radius = sprite.getSize() / 2.0 * m_def.local_radius;
    int nfruits = m_def.numbers;

    std::uniform_real_distribution<double> dist_length(0.1 * radius_max, 0.9 * radius_max);
    std::uniform_real_distribution<double> dist_angle(2.0 * M_PI / nfruits, 4.0 * M_PI / nfruits);

    double angle = 0.;

    for (int i = 0; i < nfruits; ++i) {
      double length = dist_length(engine());
      angle += dist_angle(engine());

      auto p = Vector2::makePolar(length, angle);
      renderer.arcFill(p, local_radius, 0.0, 2.0 * M_PI, m_def.color);
    }
  }

}
