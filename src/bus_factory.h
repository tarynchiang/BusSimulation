/**
 * @file bus_factory.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#ifndef SRC_BUS_FACTORY_H_
#define SRC_BUS_FACTORY_H_

#include <string>
#include <vector>
#include <random>

#include "./bus.h"
#include "./bus_types.h"

class BusFactory {
 public:
  explicit BusFactory(std::string type) : type_(type) { };
  Bus* Generate(std::string name, Route* outbound, Route* inbound,
            double speed);
 private:
  int GetRandomInteger();
  std::string type_;
};

#endif  // SRC_BUS_FACTORY_H_