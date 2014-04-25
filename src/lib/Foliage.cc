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
#include <st/Foliage.h>

#include <algorithm>
#include <vector>

#include <st/Geometry.h>
#include <st/Sprite.h>

namespace st {

  static void shadow(Renderer& renderer, double radius_max) {
    renderer.radialGradient(
      { 0.0, 0.0 }, 0.0,        { 0.3, 0.0, 0.1, 1.0 },
      { 0.0, 0.0 }, radius_max, { 0.3, 0.0, 0.1, 0.0 });
  }

  static void simple_foliage(const FoliageDef& def, Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);

    double radius_min = sprite.getSize() / 2.0 * def.radius_min;
    double radius_max = sprite.getSize() / 2.0 * def.radius_max;

    std::uniform_real_distribution<double> dist1(radius_min, (2.0 * radius_min + radius_max) / 3.0);

    std::vector<Vector2> points;

    for (int i = 0; i < def.faces; ++i) {
      double radius = dist1(engine());

      points.push_back(Vector2::makePolar(radius, 2.0 * M_PI * i / def.faces));
    }

    std::uniform_real_distribution<double> dist2((radius_min + 2.0 * radius_max) / 3.0, radius_max);

    Path path;

    path.moveTo(points[0]);

    for (std::size_t i = 1; i < points.size(); ++i) {
      double radius = dist2(engine());

      auto p1 = Vector2::makePolar(radius, 2.0 * M_PI * (i - 0.7) / def.faces);
      auto p2 = Vector2::makePolar(radius, 2.0 * M_PI * (i - 0.3) / def.faces);
      path.curveTo(p1, p2, points[i]);
    }

    {
      double radius = dist2(engine());
      auto p = Vector2::makePolar(radius, 2.0 * M_PI * -0.5 / def.faces);

      path.curveTo(p, p, points[0]);
    }

    path.close();

    renderer.pathFill(path, Color::green(0.75, def.transparency));

    double line_width = sprite.getSize() / 40.0;
    renderer.setLineJoinMiter();
    renderer.pathStroke(path, line_width, Color::green(0.55, def.transparency));

    /*
     * add some shape
     */

    renderer.pathClip(path);
    shadow(renderer, radius_max);
  }

  namespace {

    struct Ball {
      double length;
      double radius;
      double angle;
    };

  }

  static void ball_foliage(const FoliageDef& def, Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);

    double radius_min = sprite.getSize() / 2.0 * def.radius_min;
    double radius_max = sprite.getSize() / 2.0 * def.radius_max;

    double line_width = sprite.getSize() / 40.0;

    std::vector<Ball> balls;
    int nballs = def.bubbles;

    std::uniform_real_distribution<double> dist_length(radius_min * 0.1, (2.0 * radius_min + radius_max) / 3.0);
    std::uniform_real_distribution<double> dist_angle(2.0 * M_PI / nballs, 4.0 * M_PI / nballs);

    double angle = 0.;
    for (int i = 0; i < nballs; ++i) {
      double length = dist_length(engine());
      angle += dist_angle(engine());

      double local_radius_max = std::min(radius_max - length - 2.0 * line_width, 1.5 * length);
      std::uniform_real_distribution<double> dist_radius(local_radius_max * 0.8, local_radius_max);
      double radius = dist_radius(engine());

      balls.push_back({ length, radius, angle });
    }

    std::sort(balls.begin(), balls.end(), [](const Ball& lhs, const Ball& rhs) {
      return lhs.length > rhs.length;
    });

    renderer.setLineCapRound();

    for (auto ball : balls) {
      renderer.resetClip();

      auto p = Vector2::makePolar(ball.length, ball.angle);

      renderer.arcFill(p, ball.radius, 0.0, 2.0 * M_PI, Color::green(0.75, def.transparency));
      renderer.arcStroke(p, ball.radius, ball.angle - M_PI_2, ball.angle + M_PI_2, line_width, Color::green(0.55, def.transparency));
      renderer.arcClip(p, ball.radius, 0.0, 2.0 * M_PI);
      shadow(renderer, radius_max);
    }

  }

  void Foliage::render(Engine& engine, Renderer& renderer, Sprite& sprite) {
    RendererStateGuard guard(renderer);
    renderer.translate(sprite.getCenter());

    simple_foliage(m_def, engine, renderer, sprite);
    ball_foliage(m_def, engine, renderer, sprite);

  }

}
