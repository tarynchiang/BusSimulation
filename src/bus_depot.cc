/**
 * @file bus_depot.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#include "src/bus_depot.h"

#include <string>
#include <iostream>
#include <ctime>

int BusDepot::state_ = 0;

BusDepot::BusDepot() {
  small_bus_factory_ = new BusFactory("small");
  medium_bus_factory_ = new BusFactory("medium");
  large_bus_factory_ = new BusFactory("large");
}

int BusDepot::GetBusSize() {
  int busSize;

  // Get the current military time
  int currentTime = 0;
  time_t rawtime;
  struct tm* timeinfo;
  struct tm buf;
  time(&rawtime);
  timeinfo = localtime_r(&rawtime, &buf);
  currentTime = (timeinfo->tm_hour * 100) + timeinfo->tm_min;
  std::cout << "Current military time: " << currentTime <<
                                            " hours" << std::endl;

  // Determine which strategy to use, then get the appropriate bus size
  if ((currentTime >= 600) && (currentTime < 800)) {
    std::cout << "Using Strategy 1\n";
    busSize = Strategy1();
  } else if ((currentTime >= 800) && (currentTime < 1500)) {
    std::cout << "Using Strategy 2\n";
    busSize = Strategy2();
  } else if ((currentTime >= 1500) && (currentTime < 2000)) {
    std::cout << "Using Strategy 3\n";
    busSize = Strategy3();
  } else {
    std::cout << "Using Strategy 4\n";
    busSize = Strategy4();
  }

  return busSize;
}

Bus* BusDepot::SendOutBus(std::string name, Route* outbound, Route* inbound,
                double speed) {
  int busSize = GetBusSize();
  Bus* new_bus_;

  switch (busSize) {
  case 0:
  std::cout << "Small Bus sent from depot" << std::endl;
      new_bus_ = small_bus_factory_->Generate(name, outbound, inbound, speed);
  break;
  case 1:
  std::cout << "Medium Bus sent from depot" << std::endl;
      new_bus_ = medium_bus_factory_->Generate(name, outbound, inbound, speed);
  break;
  case 2:
  std::cout << "Large Bus sent from depot" << std::endl;
      new_bus_ = large_bus_factory_->Generate(name, outbound, inbound, speed);
  break;
  default:
  std::cout << "Error: Bus size request unknown" << std::endl;
  }  // end switch

  return new_bus_;
}

int BusDepot::Strategy1() {
  int retval;

  if (state_ == 0) {
  retval = 0;  // small bus
  } else {
  retval = 1;  // medium bus
  }

  state_++;
  state_ = state_ % 2;
  return retval;
}

int BusDepot::Strategy2() {
  int retval;

  if (state_ == 0) {
  retval = 1;  // medium bus
  } else {
  retval = 2;  // large bus
  }

  state_++;
  state_ = state_ % 2;
  return retval;
}

int BusDepot::Strategy3() {
  int retval;

  if (state_ == 0) {
  retval = 0;  // small bus
  } else if (state_ == 1) {
  retval = 1;  // medium bus
  } else {
  retval = 2;  // large bus
  }

  state_++;
  state_ = state_ % 3;
  return retval;
}

int BusDepot::Strategy4() {
  return 0;  // small bus
}