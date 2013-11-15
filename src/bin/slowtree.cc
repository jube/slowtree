#include <random>

#include <st/Tree.h>
#include <st/TileSet.h>

int main() {

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

