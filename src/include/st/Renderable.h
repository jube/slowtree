#ifndef ST_RENDERABLE_H
#define ST_RENDERABLE_H

#include <random>

namespace st {
  class Sprite;

  class Renderable {
  public:
    virtual ~Renderable();

    virtual void render(std::mt19937_64& gen, Sprite& sprite) = 0;

  };


}


#endif // ST_RENDERABLE_H
