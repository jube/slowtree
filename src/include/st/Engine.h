/*
 * SlowTree
 * a 2D top-down vegetation sprite generator
 *
 * Copyright (c) 2013, Julien Bernard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ST_ENGINE_H
#define ST_ENGINE_H

#include <random>

namespace st {

  class Engine {
  public:
    typedef std::mt19937_64 Type;

    Engine(typename Type::result_type seed)
    : m_generator(seed)
    {
    }

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Type& operator()() {
      return m_generator;
    }

  private:
    Type m_generator;
  };

}

#endif // ST_ENGINE_H
