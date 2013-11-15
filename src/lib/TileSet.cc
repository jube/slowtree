#include <st/TileSet.h>

#include <cassert>

#include <st/Sprite.h>

namespace st {

  TileSet::TileSet(const TileSetDef& def)
    : m_def(def) {
    if (!m_def.filename) {
      m_def.filename = "sprite.png";
    }

    if (m_def.size <= 0) {
      m_def.size = 64;
    }

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, m_def.size * m_def.width, m_def.size * m_def.height);
    assert(surface);
    m_cr = cairo_create(surface);
    assert(m_cr);
  }

  TileSet::~TileSet() {
    cairo_surface_t *surface = cairo_get_target(m_cr);
    cairo_destroy(m_cr);

    cairo_surface_write_to_png(surface, m_def.filename);
    cairo_surface_destroy(surface);
  }

  void TileSet::render(std::mt19937_64& gen, Renderable& renderable) {
    cairo_t *cr = getContext();

    SpriteDef def;
    def.size = m_def.size;
    def.cr = cr;

    for (int x = 0; x < m_def.width; ++x) {
      for (int y = 0; y < m_def.height; ++y) {
        cairo_save(cr);
        cairo_translate(cr, x * m_def.size, y * m_def.size);

        Sprite sprite(def);
        renderable.render(gen, sprite);

        cairo_restore(cr);
      }
    }

  }

}
