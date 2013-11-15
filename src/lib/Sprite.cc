#include <st/Sprite.h>

#include <cassert>

namespace st {

  Sprite::Sprite(const SpriteDef& def)
    : m_def(def) {

    if (m_def.size <= 0) {
      m_def.size = 64;
    }

    assert(m_def.cr);
  }

}
