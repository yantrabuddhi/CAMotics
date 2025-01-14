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


#include "SurfaceTask.h"

#include <camotics/cutsim/SimulationRun.h>
#include <camotics/contour/Surface.h>

#include <cbang/String.h>
#include <cbang/time/TimeInterval.h>
#include <cbang/log/Logger.h>

using namespace cb;
using namespace CAMotics;


SurfaceTask::SurfaceTask(const SmartPointer<Simulation> &sim) :
  simRun(new SimulationRun(sim)) {}


SurfaceTask::SurfaceTask(const SmartPointer<SimulationRun> &simRun) :
  simRun(simRun) {}


SurfaceTask::~SurfaceTask() {}


const SmartPointer<Surface> &SurfaceTask::getSurface() const {
  return simRun->getSurface();
}


void SurfaceTask::run() {
  Task::begin();

  simRun->compute(SmartPointer<Task>::Phony(this));

  // Time
  if (shouldQuit()) {
    Task::end();
    LOG_INFO(1, "Render aborted");
    return;
  }

  // Done
  SmartPointer<Surface> surface = simRun->getSurface();
  double delta = Task::end();
  LOG_INFO(1, "Time: " << TimeInterval(delta)
           << " Triangles: " << surface->getCount()
           << " Triangles/sec: "
           << String::printf("%0.2f", surface->getCount() / delta));
}
