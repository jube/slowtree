#ifndef ST_TRUNK_H
#define ST_TRUNK_H

#include "Renderable.h"

namespace st {

  struct TrunkDef {
    int faces = 30;
    double radius_min = 0.2;
    double radius_max = 0.25;
    int branches = 10;
    double branch_radius_max = 1.0;
  };

  class Trunk : public Renderable {
  public:
    Trunk(const TrunkDef& def)
      : m_def(def) {
    }

    virtual void render(std::mt19937_64& gen, Sprite& sprite) override;


  private:
    TrunkDef m_def;
  };


}

#endif // ST_TRUNK_H
