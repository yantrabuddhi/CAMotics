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

#include "View.h"
#include "GL.h"

#include <camotics/cutsim/MoveLookup.h>

#include <cbang/Math.h>
#include <cbang/log/Logger.h>
#include <cbang/config/Options.h>

using namespace std;
using namespace cb;
using namespace CAMotics;


View::View(ValueSet &valueSet) :
  values(valueSet), flags(SHOW_PATH_FLAG | SHOW_TOOL_FLAG | SHOW_SURFACE_FLAG |
                          SHOW_WORKPIECE_BOUNDS_FLAG | PATH_VBOS_FLAG |
                          SURFACE_VBOS_FLAG),
  speed(1), reverse(false), lastTime(0), path(new ToolPathView(valueSet)),
  workpiece(new CuboidView) {

  values.add("play_speed", speed);
  values.add("play_direction", reverse);
  values.add("view_flags", flags);
}


View::~View() {}


void View::incSpeed() {
  if (speed < (1 << 16)) speed <<= 1;
  values.updated();
}


void View::decSpeed() {
  if (1 < speed) speed >>= 1;
  values.updated();
}


void View::setToolPath(const SmartPointer<ToolPath> &toolPath) {
  path->setPath(toolPath, flags & PATH_VBOS_FLAG);
}


void View::setWorkpiece(const Rectangle3R &bounds) {
  workpiece->setBounds(bounds);
}


void View::setSurface(const SmartPointer<Surface> &surface) {
  this->surface = surface;
}


void View::setMoveLookup(const SmartPointer<MoveLookup> &moveLookup) {
  this->moveLookup = moveLookup;
}


bool View::update() {
  // Animate
  if (isFlagSet(PLAY_FLAG)) {
    double now = Timer::now();

    if (lastTime) {
      double delta = (now - lastTime) * speed;

      if (reverse) path->decTime(delta);
      else path->incTime(delta);

      if ((reverse && path->atStart()) || (!reverse && path->atEnd()))
        clearFlag(PLAY_FLAG);

      return true;

    } else if (!reverse && path->atEnd()) {
      path->setByRatio(0);
      return true;

    } else if (reverse && path->atStart()) {
      path->setByRatio(1);
      return true;

    } else lastTime = now;

  } else lastTime = 0;

  return false;
}


void View::clear() {
  setToolPath(0);
  setWorkpiece(Rectangle3R());
  setSurface(0);
  setMoveLookup(0);
  resetView();
}
