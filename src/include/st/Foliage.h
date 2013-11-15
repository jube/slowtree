#ifndef ST_FOLIAGE_H
#define ST_FOLIAGE_H

#include "Renderable.h"

namespace st {

  struct FoliageDef {
    int faces = 7;
    double radius_min = 0.7;
    double radius_max = 1.1;
    double transparency = 0.7;
    int bubbles = 10;
  };

  class Foliage : public Renderable {
  public:

    Foliage(const FoliageDef& def)
      : m_def(def)
    {
    }

    virtual void render(std::mt19937_64& gen, Sprite& sprite) override;

  private:
    FoliageDef m_def;
  };


}

#endif // ST_FOLIAGE_H
