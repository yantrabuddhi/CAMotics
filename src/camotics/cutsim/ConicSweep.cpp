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

#include "ConicSweep.h"

#include <cbang/log/Logger.h>

#include <limits>

using namespace std;
using namespace CAMotics;


ConicSweep::ConicSweep(real length, real radius1, real radius2) :
  l(length), rt(radius1), rb(radius2 == -1 ? radius1 : radius2),
  Tm((rt - rb) / l) {
}


void ConicSweep::getBBoxes(const Vector3R &start, const Vector3R &end,
                           vector<Rectangle3R> &bboxes, real tolerance) const {
  Sweep::getBBoxes(start, end, bboxes, rt < rb ? rb : rt, l, tolerance);
}


namespace {
  inline double sqr(double x) {return x * x;}
}


real ConicSweep::depth(const Vector3R &A, const Vector3R &B,
                       const Vector3R &P) const {
  const double Ax = A.x(), Ay = A.y(), Az = A.z();
  const double Bx = B.x(), By = B.y(), Bz = B.z();
  const double Px = P.x(), Py = P.y(), Pz = P.z();

  // Check z-height
  if (Pz < min(Az, Bz) || max(Az, Bz) + l < Pz) return -1;

  // epsilon * beta^2 + gamma * beta + rho = 0
  const double epsilon = sqr(Bx - Ax) + sqr(By - Ay) - sqr(Tm * (Bz - Az));
  const double gamma = (Ax - Px) * (Bx - Ax) + (Ay - Py) * (By - Ay) +
    (sqr(Tm) * (Az - Pz) - Tm * rb) * (Az - Bz);
  const double rho = sqr(Ax - Px) + sqr(Ay - Py) - sqr(Tm * (Az - Pz) - rb);
  const double sigma = sqr(gamma) - epsilon * rho;

  // Check if solution is valid
  if (epsilon == 0 || sigma < 0) return -1;

  double beta = (-gamma - sqrt(sigma)) / epsilon; // Quadradic equation

  // Check if z-heights make sense
  const double Qz = (Bz - Az) * beta + Az;

  // Check if the point is cut by the flat top or bottom
  if (Pz < Qz || Qz + l < Pz) {
    beta = Pz / (Bz - Az); // E is on AB at z-height

    // Compute squared distance to E on XY plane
    const double Ex = beta * (Bx - Ax) + Ax;
    const double Ey = beta * (By - Ay) + Ay;
    const double d2 = sqr(Ex - Px) + sqr(Ey - Py);

    if (Pz < Qz && rb * rb < d2) return -1;
    if (Qz + l < Pz && rt * rt < d2) return -1;
  }

  // Check that it's on the line segment
  if (beta < 0 || 1 < beta) return -1;

  return 1;
}
