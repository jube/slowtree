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
#include <cstdio>
#include <random>

#include <st/Tree.h>
#include <st/TileSet.h>

#include "config.h"

int main() {
  std::printf("SlowTree, a 2D top-down vegetation sprite generator\nVersion %s\n", SLOWTREE_VERSION);

  std::random_device dev;
  std::mt19937_64 gen(dev());

  st::TrunkDef trunk;
  st::FoliageDef foliage;

  st::Tree tree(trunk, foliage);


  st::TileSetDef def;
  def.width = 4;
  def.height = 4;
  def.filename = "trees.png";
  st::TileSet tileset(def);

  tileset.render(gen, tree);

  return 0;
}

