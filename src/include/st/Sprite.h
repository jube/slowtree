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
#ifndef ST_SPRITE_H
#define ST_SPRITE_H

#include <st/Geometry.h>

namespace st {

  struct SpriteDef {
    int size = 256;
  };

  class Sprite {
  public:
    Sprite(const SpriteDef& def);

    int getSize() const {
      return m_def.size;
    }

    Vector2 getCenter() const {
      return { m_def.size * 0.5, m_def.size * 0.5 };
    }

  private:
    SpriteDef m_def;
  };
}

#endif // ST_SPRITE_H
