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
#ifndef ST_TREE_H
#define ST_TREE_H

#include "Foliage.h"
#include "Fruits.h"
#include "Renderable.h"
#include "Trunk.h"

namespace st {

  class Tree : public Renderable {
  public:
    Tree(TrunkDef trunk, FoliageDef foliage, bool has_fruits = false, FruitsDef fruits = FruitsDef())
      : m_trunk(trunk), m_foliage(foliage), m_has_fruits(has_fruits), m_fruits(fruits)
    {
    }

    virtual void render(Engine& engine, Renderer& renderer, Sprite& sprite) override;

  private:
    Trunk m_trunk;
    Foliage m_foliage;
    bool m_has_fruits;
    Fruits m_fruits;
  };



}


#endif // ST_TREE_H
