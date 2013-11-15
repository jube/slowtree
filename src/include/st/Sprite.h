#ifndef ST_SPRITE_H
#define ST_SPRITE_H

#include <cairo.h>

namespace st {

  struct SpriteDef {
    int size = 256;
    cairo_t *cr = nullptr;
  };

  class Sprite {
  public:
    Sprite(const SpriteDef& def);

    int getSize() {
      return m_def.size;
    }

    cairo_t *getContext() {
      return m_def.cr;
    }

  private:
    SpriteDef m_def;
  };
}

#endif // ST_SPRITE_H
