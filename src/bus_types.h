/**
 * @file bus_types.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#ifndef SRC_BUS_TYPES_H_
#define SRC_BUS_TYPES_H_

#include <string>

#include "src/bus.h"

class SmallBus : public BusBase {
 public:
  SmallBus(std::string name, Route* out, Route* in, double speed):
      BusBase(name, out, in, 30, speed, "Small") { }
};

class MediumBus : public BusBase {
 public:
  MediumBus(std::string name, Route* out, Route* in, double speed):
      BusBase(name, out, in, 60, speed, "Medium") { }
};

class LargeBus : public BusBase {
 public:
  LargeBus(std::string name, Route* out, Route* in, double speed):
      BusBase(name, out, in, 90, speed, "Large") { }
};

#endif  // SRC_BUS_TYPES_H_