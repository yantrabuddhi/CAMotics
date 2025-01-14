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

#ifndef CAMOTICS_TRIANGLE_H
#define CAMOTICS_TRIANGLE_H

#include <camotics/Geom.h>


namespace CAMotics {
  struct Triangle : public cb::Triangle3F {
    cb::Vector3F normal;
    float time;

    Triangle(const cb::Triangle3F &t = cb::Triangle3F(cb::Vector3F(0.0)),
             const cb::Vector3F &n = cb::Vector3F(0.0 / 0.0),
             float time = 0) :
      cb::Triangle3F(t), normal(n), time(time) {}

    void updateNormal();
    cb::Vector3F computeNormal() const;
  };
}

#endif // CAMOTICS_TRIANGLE_H

