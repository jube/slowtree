#ifndef ST_TREE_H
#define ST_TREE_H

#include "Renderable.h"
#include "Trunk.h"
#include "Foliage.h"

namespace st {

  class Tree : public Renderable {
  public:
    Tree(TrunkDef trunk, FoliageDef foliage)
      : m_trunk(trunk), m_foliage(foliage)
    {
    }

    virtual void render(std::mt19937_64& gen, Sprite& sprite) override;

  private:
    Trunk m_trunk;
    Foliage m_foliage;
  };



}


#endif // ST_TREE_H
