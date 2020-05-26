/**
 * @file bus_factory.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#include "src/bus_factory.h"

Bus* BusFactory::Generate(std::string name, Route* outbound, Route* inbound,
              double speed) {
    int rand_int = GetRandomInteger();

    if (type_ == "small" || (type_ == "random" && rand_int == 1)) {
        return new SmallBus(name, outbound, inbound, speed);
    } else if (type_ == "medium" || (type_ == "random" && rand_int == 2)) {
        return new MediumBus(name, outbound, inbound, speed);
    } else if (type_ == "large" || (type_ == "random" && rand_int == 3)) {
        return new LargeBus(name, outbound, inbound, speed);
    } else {
        std::cout << "type_: " << type_ << std::endl;
        throw "Type must be small, medium, large or random";
    }
}

int BusFactory::GetRandomInteger() {
  // Random integer generation to determine the bus type.
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist1(1, 3);
  int rand_int = dist1(rng);
  return rand_int;
}