/******************************************************************************\

    CAMotics is an Open-Source simulation and CAM software.
    Copyright (C) 2011-2015 Joseph Coffland <joseph@cauldrondevelopment.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

#ifndef CAMOTICS_GRID_TREE_NODEH
#define CAMOTICS_GRID_TREE_NODEH

#include "GridTreeBase.h"


namespace CAMotics {
  class GridTreeNode : public GridTreeBase {
  protected:
    GridTreeBase *left;
    GridTreeBase *right;

    unsigned axis;
    unsigned split;

    unsigned count;

  public:
    GridTreeNode(const cb::Vector3U &steps);
    ~GridTreeNode();

    // From GridTreeBase
    unsigned getCount() const {return count;}
    void insertLeaf(GridTreeLeaf *leaf, const cb::Vector3U &steps,
                    const cb::Vector3U &offset);
    void gather(std::vector<float> &vertices,
                std::vector<float> &normals) const;
  };
}

#endif // CAMOTICS_GRID_TREE_NODEH

