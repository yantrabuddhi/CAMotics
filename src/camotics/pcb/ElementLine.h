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

#ifndef CAMOTICS_PCB_ELEMENT_LINE_H
#define CAMOTICS_PCB_ELEMENT_LINE_H

#include "Object.h"
#include "Point.h"

#include <camotics/Geom.h>

namespace CAMotics {
  namespace PCB {
    class ElementLine : public Object {
      Point p1;
      Point p2;
      int thickness;

    public:
      ElementLine();
      ElementLine(const Point &p1, const Point &p2, int thickness);

      cb::Segment2D getSegment() const {return cb::Segment2D(p1, p2);}
      int getThickness() const {return thickness;}

      // From Object
      const char *getName() const {return "ElementLine";}
      void rotate(const Point &center, double angle);
      void translate(const Point &t);
      void multiply(double m);
      void round(int i);
      void write(std::ostream &stream) const;
      void read(std::istream &stream);
      void bounds(Point &min, Point &max) const;
      void flipX(double x);
      void flipY(double x);
      void lineSize(int size);
    };
  }
}

#endif // CAMOTICS_PCB_ELEMENT_LINE_H

