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

#ifndef CAMOTICS_PCB_SYMBOL_H
#define CAMOTICS_PCB_SYMBOL_H

#include "Layout.h"
#include "Point.h"

namespace CAMotics {
  namespace PCB {
    class Symbol : public Layout {
    public:
      char c;
      int delta;

      // From Object
      const char *getName() const {return "Symbol";}
      void write(std::ostream &stream) const;
      void read(std::istream &stream);
    };
  }
}

#endif // CAMOTICS_PCB_SYMBOL_H

