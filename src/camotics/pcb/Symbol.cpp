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

#include "Symbol.h"

#include <cbang/Exception.h>

using namespace std;
using namespace cb;
using namespace CAMotics::PCB;


void Symbol::write(ostream &stream) const {
  stream << "Symbol('" << c << "' " << delta << ")\n(";
  Layout::write(stream);
  stream << ")";
}


void Symbol::read(istream &stream) {
  readWS(stream);
  int x = stream.get();
  if (x != '\'')  THROW("missing ')' on Symbol");
  c = stream.get();
  x = stream.get();
  if (x != '\'')  THROW("missing ')' on Symbol");

  stream >> delta;
    
  readWS(stream);
  int c = stream.get();
  if (c != ')')  THROW("missing ')' on Symbol");

  readWS(stream);
  c = stream.get();
  if (c != '(')  THROW("missing '(' on Symbol");

  Layout::read(stream);
}
