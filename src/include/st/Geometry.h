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
#ifndef ST_GEOMETRY_H
#define ST_GEOMETRY_H

#include <cmath>

namespace st {

  constexpr double lerp(double a, double b, double t) {
    return a + (b - a) * t;
  }

  struct Vector2 {
    double x;
    double y;

    static constexpr Vector2 makePolar(double rho, double theta) {
      return { rho * std::cos(theta), rho * std::sin(theta) };
    }
  };

}

#endif // ST_GEOMETRY_H
