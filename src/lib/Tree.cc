#include <st/Tree.h>

namespace st {

  void Tree::render(std::mt19937_64& gen, Sprite& sprite) {
    m_trunk.render(gen, sprite);
    m_foliage.render(gen, sprite);
  }

}
