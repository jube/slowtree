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
#ifndef ST_ROCK_H
#define ST_ROCK_H

#include "Renderable.h"

namespace st {

  struct RockDef {
    int faces = 7;
    double radius_min = 0.7;
    double radius_max = 1.0;
  };

  class Rock : public Renderable {
  public:

    Rock(const RockDef& def)
      : m_def(def)
    {
    }

    virtual void render(Engine& engine, Renderer& renderer, Sprite& sprite) override;

  private:
    RockDef m_def;
  };


}

#endif // ST_ROCK_H
