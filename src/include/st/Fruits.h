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
#ifndef ST_FRUITS_H
#define ST_FRUITS_H

#include "Renderable.h"

namespace st {

  struct FruitsDef {
    double radius_max = 0.8;
    double local_radius = 0.03;
    double transparency = 0.3;
    int numbers = 30;
    double color[3] = { 1.0, 0.0, 0.0 }; // RGB
  };

  class Fruits : public Renderable {
  public:

    Fruits(const FruitsDef& def)
      : m_def(def)
    {
    }

    virtual void render(Engine& engine, Sprite& sprite) override;

  private:
    FruitsDef m_def;
  };


}

#endif // ST_FRUITS_H
