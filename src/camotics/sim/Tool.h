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

#ifndef CAMOTICS_TOOL_H
#define CAMOTICS_TOOL_H

#include "ToolShape.h"
#include "ToolUnits.h"

#include <camotics/machine/Axes.h>

#include <cbang/json/Serializable.h>


namespace cb {
  namespace JSON {class Sink;}

  class XMLWriter;
  class XMLAttributes;
}


namespace CAMotics {
  class Sweep;

  class Tool : public Axes, cb::JSON::Serializable {
  protected:
    unsigned number;
    unsigned pocket;
    ToolUnits units;
    ToolShape shape;
    double vars[4];
    double snubDiameter;
    std::string description;

  public:
    static const char *VARS;
    static Tool null;

    Tool(unsigned number = 0, unsigned pocket = 0,
         ToolUnits units = ToolUnits::UNITS_MM);

    unsigned getNumber() const {return number;}
    void setNumber(unsigned number) {this->number = number;}
    unsigned getPocket() const {return pocket;}
    void setPocket(unsigned pocket) {this->pocket = pocket;}

    double get(char c) const {return getIndex(toIndex(c));}
    void set(char c, double value) {setIndex(toIndex(c), value);}

    double getIndex(unsigned i) const
    {return i < 9 ? Axes::getIndex(i) : vars[i - 9];}
    void setIndex(unsigned i, double value)
    {if (i < 9) Axes::setIndex(i, value); else vars[i - 9] = value;}

    ToolUnits getUnits() const {return units;}
    void setUnits(ToolUnits units) {this->units = units;}
    ToolShape getShape() const {return shape;}
    void setShape(ToolShape shape) {this->shape = shape;}
    const std::string &getDescription() const {return description;}
    void setDescription(const std::string &x) {this->description = x;}
    std::string getSizeText() const;
    std::string getText() const;

    double getLength() const {return getZ();}
    double getRadius() const {return vars[0];}
    double getDiameter() const {return vars[0] * 2;}
    double getSnubDiameter() const {return snubDiameter;}
    double getFrontAngle() const {return vars[1];}
    double getBackAngle() const {return vars[2];}
    double getOrientation() const {return vars[3];}

    void setLength(double value) {setZ(value);}
    void setRadius(double value) {vars[0] = value;}
    void setDiameter(double value) {vars[0] = value / 2;}
    void setSnubDiameter(double value) {snubDiameter = value;}
    void setFrontAngle(double value) {vars[1] = value;}
    void setBackAngle(double value) {vars[2] = value;}
    void setOrientation(double value) {vars[3] = value;}

    cb::SmartPointer<Sweep> getSweep() const;

    std::ostream &print(std::ostream &stream) const;

    void read(const cb::XMLAttributes &attrs);
    void write(cb::XMLWriter &writer) const;

    void write(cb::JSON::Sink &sink, bool withNumber) const;

    // From cb::JSON::Serializable
    void read(const cb::JSON::Value &value);
    void write(cb::JSON::Sink &sink) const {write(sink, true);}

    inline static unsigned toIndex(char var) {
      switch (std::toupper(var)) {
      case 'R': return 9;
      case 'I': return 10;
      case 'J': return 11;
      case 'Q': return 12;
      default: return Axes::toIndex(var);
      }
    }

    
    inline static char toVar(unsigned i) {
      switch (i) {
      case 9: return 'R';
      case 10: return 'I';
      case 11: return 'J';
      case 12: return 'Q';
      default: return Axes::toAxis(i);
      }
    }
  };

  inline static
  std::ostream &operator<<(std::ostream &stream, const Tool &t) {
    return t.print(stream);
  }
}

#endif // CAMOTICS_TOOL_H

