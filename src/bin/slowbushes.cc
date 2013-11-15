#include <random>

#include <st/Tree.h>
#include <st/TileSet.h>

int main() {

  std::random_device dev;
  std::mt19937_64 gen(dev());

  st::FoliageDef foliage;
  foliage.faces = 5;
  foliage.radius_max = 0.8;
  foliage.radius_max = 1.0;
  foliage.transparency = 0.9;
  foliage.bubbles = 3;
  st::Foliage bush(foliage);

  st::TileSetDef def;
  def.width = 4;
  def.height = 4;
  def.size = 64;
  def.filename = "bushes.png";
  st::TileSet tileset(def);

  tileset.render(gen, bush);

  return 0;
}

