#include <st/Foliage.h>

#include <algorithm>
#include <vector>

#include <st/Sprite.h>

namespace st {

  namespace {

    struct Point {
      double x;
      double y;
    };

    struct Ball {
      double length;
      double radius;
      double angle;
    };

  }

  static void shadow(cairo_t *cr, double radius_max) {
    cairo_pattern_t *pattern = cairo_pattern_create_radial(
      0.0, 0.0, 0.0, 0.0, 0.0, radius_max);
    cairo_pattern_add_color_stop_rgba(pattern, 0.0, 0.3, 0.0, 0.1, 1.0);
    cairo_pattern_add_color_stop_rgba(pattern, 1.0, 0.3, 0.0, 0.1, 0.0);

    cairo_mask(cr, pattern);

    cairo_pattern_destroy(pattern);
  }

  static void simple_foliage(const FoliageDef& def, std::mt19937_64& gen, Sprite& sprite) {
    cairo_t *cr = sprite.getContext();
    cairo_save(cr);

    double radius_min = sprite.getSize() / 2.0 * def.radius_min;
    double radius_max = sprite.getSize() / 2.0 * def.radius_max;

    std::uniform_real_distribution<double> dist1(radius_min, (2.0 * radius_min + radius_max) / 3.0);

    std::vector<Point> points;

    for (int i = 0; i < def.faces; ++i) {
      double radius = dist1(gen);
      double x = radius * std::cos(2.0 * M_PI * i / def.faces);
      double y = radius * std::sin(2.0 * M_PI * i / def.faces);

      points.push_back({ x, y });
    }

    std::uniform_real_distribution<double> dist2((radius_min + 2.0 * radius_max) / 3.0, radius_max);

    cairo_move_to(cr, points[0].x, points[0].y);

    for (std::size_t i = 1; i < points.size(); ++i) {
      double radius = dist2(gen);
      double x1 = radius * std::cos(2.0 * M_PI * (i - 0.7) / def.faces);
      double y1 = radius * std::sin(2.0 * M_PI * (i - 0.7) / def.faces);
      double x2 = radius * std::cos(2.0 * M_PI * (i - 0.3) / def.faces);
      double y2 = radius * std::sin(2.0 * M_PI * (i - 0.3) / def.faces);

      cairo_curve_to(cr, x1, y1, x2, y2, points[i].x, points[i].y);
    }

    {
      double radius = dist2(gen);
      double x = radius * std::cos(2.0 * M_PI * -0.5 / def.faces);
      double y = radius * std::sin(2.0 * M_PI * -0.5 / def.faces);

      cairo_curve_to(cr, x, y, x, y, points[0].x, points[0].y);
    }

    cairo_close_path(cr);

    cairo_set_source_rgba(cr, 0.0, 0.75, 0.0, def.transparency);
    cairo_fill_preserve(cr);

    cairo_set_line_join(cr, CAIRO_LINE_JOIN_MITER);
    cairo_set_miter_limit(cr, 1e3);

    double lw = sprite.getSize() / 40.0;
    cairo_set_line_width(cr, lw);

    cairo_set_source_rgba(cr, 0.0, 0.55, 0.0, def.transparency);
    cairo_stroke_preserve(cr);

    /*
     * add some shape
     */

    cairo_clip(cr);
    shadow(cr, radius_max);

    cairo_restore(cr);
  }

  static void ball_foliage(const FoliageDef& def, std::mt19937_64& gen, Sprite& sprite) {
    cairo_t *cr = sprite.getContext();
    cairo_save(cr);

    double radius_min = sprite.getSize() / 2.0 * def.radius_min;
    double radius_max = sprite.getSize() / 2.0 * def.radius_max;

    std::vector<Ball> balls;
    int nballs = def.bubbles;

    std::uniform_real_distribution<double> dist_length(radius_min * 0.1, (2.0 * radius_min + radius_max) / 3.0);
    std::uniform_real_distribution<double> dist_angle(2.0 * M_PI / nballs, 4.0 * M_PI / nballs);

    double lw = sprite.getSize() / 40.0;

    double angle = 0.;
    for (int i = 0; i < nballs; ++i) {
      double length = dist_length(gen);
      angle += dist_angle(gen);

      double local_radius_max = std::min(radius_max - length - 2.0 * lw, 1.5 * length);
      std::uniform_real_distribution<double> dist_radius(local_radius_max * 0.8, local_radius_max);
      double radius = dist_radius(gen);

      balls.push_back({ length, radius, angle });
    }

    std::sort(balls.begin(), balls.end(), [](const Ball& lhs, const Ball& rhs) {
      return lhs.length > rhs.length;
    });


    cairo_set_line_width(cr, lw);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);

    for (auto ball : balls) {
      cairo_reset_clip(cr);

      double x = ball.length * std::cos(ball.angle);
      double y = ball.length * std::sin(ball.angle);

      cairo_arc(cr, x, y, ball.radius, 0.0, 2.0 * M_PI);
      cairo_set_source_rgba(cr, 0.0, 0.75, 0.0, def.transparency);
      cairo_fill(cr);

      cairo_arc(cr, x, y, ball.radius, ball.angle - M_PI_2, ball.angle + M_PI_2);
      cairo_set_source_rgba(cr, 0.0, 0.55, 0.0, def.transparency);
      cairo_stroke(cr);

      cairo_arc(cr, x, y, ball.radius, 0.0, 2.0 * M_PI);
      cairo_clip(cr);
      shadow(cr, radius_max);
    }

    cairo_restore(cr);
  }

  void Foliage::render(std::mt19937_64& gen, Sprite& sprite) {
    cairo_t *cr = sprite.getContext();
    cairo_save(cr);

    double center = sprite.getSize() / 2.0;
    cairo_translate(cr, center, center);

    simple_foliage(m_def, gen, sprite);
    ball_foliage(m_def, gen, sprite);

    cairo_restore(cr);
  }

}
