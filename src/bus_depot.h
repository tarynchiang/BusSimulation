/**
 * @file bus_depot.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#ifndef SRC_BUS_DEPOT_H_
#define SRC_BUS_DEPOT_H_

#include <string>

#include "src/bus_factory.h"

class BusDepot {
 public:
  BusDepot();
  Bus* SendOutBus(std::string name, Route* outbound, Route* inbound,
                  double speed);
 private:
  static int state_;
  BusFactory* small_bus_factory_;
  BusFactory* medium_bus_factory_;
  BusFactory* large_bus_factory_;

  int GetBusSize();
  int Strategy1();
  int Strategy2();
  int Strategy3();
  int Strategy4();
};

#endif  // SRC_BUS_DEPOT_H_