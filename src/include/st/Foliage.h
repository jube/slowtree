/*
 * slowtree
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
#ifndef ST_FOLIAGE_H
#define ST_FOLIAGE_H

#include "Renderable.h"

namespace st {

  struct FoliageDef {
    int faces = 7;
    double radius_min = 0.7;
    double radius_max = 1.1;
    double transparency = 0.7;
    int bubbles = 10;
  };

  class Foliage : public Renderable {
  public:

    Foliage(const FoliageDef& def)
      : m_def(def)
    {
    }

    virtual void render(std::mt19937_64& gen, Sprite& sprite) override;

  private:
    FoliageDef m_def;
  };


}

#endif // ST_FOLIAGE_H
