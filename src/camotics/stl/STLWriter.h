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

#ifndef CAMOTICS_STL_WRITER_H
#define CAMOTICS_STL_WRITER_H

#include "STLSink.h"

#include <cbang/io/OutputSink.h>


namespace CAMotics {
  class STLWriter : public STLSink {
    cb::OutputSink sink;
    std::ostream &stream;
    bool binary;

  public:
    STLWriter(const cb::OutputSink &sink, bool binary) :
      sink(sink), stream(sink.getStream()), binary(binary) {}

    void writeHeader(const std::string &name, uint32_t count,
                     const std::string &hash = std::string());
    void writeFacet(const cb::Vector3F &v1, const cb::Vector3F &v2,
                    const cb::Vector3F &v3, const cb::Vector3F &normal);
    void writeFooter(const std::string &name,
                     const std::string &hash = std::string());
  };
}

#endif // CAMOTICS_STL_WRITER_H

