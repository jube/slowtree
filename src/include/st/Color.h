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
#ifndef ST_COLOR_H
#define ST_COLOR_H

namespace st {

  struct Color {
    double r;
    double g;
    double b;
    double a;

    static constexpr Color red(double value = 1.0, double alpha = 1.0) {
      return { value, 0.0, 0.0, alpha };
    }

    static constexpr Color green(double value = 1.0, double alpha = 1.0) {
      return { 0.0, value, 0.0, alpha };
    }

    static constexpr Color blue(double value = 1.0, double alpha = 1.0) {
      return { 0.0, 0.0, value, alpha };
    }

    static constexpr Color grey(double value, double alpha = 1.0) {
      return { value, value, value, alpha };
    }

  };

}

#endif // ST_COLOR_H
