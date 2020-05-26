/*
 * bus unit test
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <random>
#include <vector>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "../src/data_structs.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BusTests : public ::testing::Test {
protected:
  Route* routeOut;
  double* distancesOut;
  Stop** stopsOut;
  std::list<double> probsOut;
  std::list<Stop *> gStopsOut;
  RandomPassengerGenerator* generatorOut;
  Route* routeIn;
  double* distancesIn;
  Stop** stopsIn;
  std::list<double> probsIn;
  std::list<Stop *> gStopsIn;
  RandomPassengerGenerator* generatorIn;
  Bus* bus;

  virtual void SetUp() {
    stopsOut = new Stop*[6];
    stopsIn = new Stop*[6];

    //Eastbound stops
    stopsOut[0] = new Stop(0, 43, -92.5); //West bank station
    gStopsOut.push_back(new Stop(0, 43, -92.5));
    stopsOut[1] = new Stop(1); //student union station
    gStopsOut.push_back(new Stop(1));
    stopsOut[2] = new Stop(2, 44.973820, -93.227117); //Oak St & Washington Ave
    gStopsOut.push_back(new Stop(2, 44.973820, -93.227117));
    stopsOut[3] = new Stop(3, 45, -94); //before transit
    gStopsOut.push_back(new Stop(3, 45, -94));
    stopsOut[4] = new Stop(4, 46, -95); //st paul 1
    gStopsOut.push_back(new Stop(4, 46, -95));
    stopsOut[5] = new Stop(5, 47, -96); //st paul 2
    gStopsOut.push_back(new Stop(5, 47, -96));
    
    //Westbound stops
    stopsIn[0] = new Stop(6, 47, -96); //st paul 2
    gStopsIn.push_back(new Stop(6, 47, -96));
    stopsIn[1] = new Stop(7, 46, -95); //st paul 1
    gStopsIn.push_back(new Stop(7, 46, -95));
    stopsIn[2] = new Stop(8, 45, -94); //before transit
    gStopsIn.push_back(new Stop(8, 45, -94));
    stopsIn[3] = new Stop(9, 44.973820, -93.227117); //Oak St & Washington Ave
    gStopsIn.push_back(new Stop(9, 44.973820, -93.227117));
    stopsIn[4] = new Stop(10); //student union station
    gStopsIn.push_back(new Stop(10));
    stopsIn[5] = new Stop(11, 43, -92.5); //West bank station
    gStopsIn.push_back(new Stop(11, 43, -92.5));

    distancesOut = new double[5];
    distancesIn = new double[5];

    distancesOut[0] = 5;
    distancesOut[1] = 4;
    distancesOut[2] = 3;
    distancesOut[3] = 10;
    distancesOut[4] = 6;

    distancesIn[0] = 6;
    distancesIn[1] = 10;
    distancesIn[2] = 3;
    distancesIn[3] = 4;
    distancesIn[4] = 5;

    probsOut.push_back(.15); //WB
    probsOut.push_back(.3); //CMU
    probsOut.push_back(.025); //O&W
    probsOut.push_back(.05); //Pre-transit
    probsOut.push_back(.05); //STP 1
    probsOut.push_back(0); //STP 1

    probsIn.push_back(.35); //stp 2
    probsIn.push_back(.05); //stp 1
    probsIn.push_back(.01); //post-transit
    probsIn.push_back(.01); //O&W
    probsIn.push_back(.02); //CMU
    probsIn.push_back(0); //WB

    generatorIn = new RandomPassengerGenerator(probsIn,gStopsIn);
    generatorOut = new RandomPassengerGenerator(probsOut,gStopsOut);

    routeOut = new Route("Campus Connector 1- Eastbound",stopsOut,distancesOut,6,generatorOut);
    routeIn = new Route("Campus Connector 1- Westbound",stopsIn,distancesIn,6,generatorIn);

    bus = new Bus("Campus Connector",routeOut,routeIn,60,1);
  }

  virtual void TearDown() {
    delete bus;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BusTests, Constructor) {
  bus->UpdateBusData();
	BusData bus_data = bus->GetBusData();
	EXPECT_EQ(bus_data.id, "Campus Connector");
	EXPECT_EQ(bus_data.num_passengers, 0);
	EXPECT_EQ(bus_data.capacity, 60);
};

TEST_F(BusTests, IsTripComplete) {
  EXPECT_EQ(bus->IsTripComplete(), false);
  for (int i = 0; i < 5; i++) {
      bus->Update();
  }
  EXPECT_EQ(bus->IsTripComplete(), false);
  for (int i = 0; i < 5; i++) {
      bus->Update();
  }
  EXPECT_EQ(bus->IsTripComplete(), true);
}

TEST_F(BusTests, LoadPassenger) {
  Passenger* passenger1;
  Passenger* passenger2;
  Passenger* passenger3;
  passenger1 = new Passenger(2,"student1");
  passenger2 = new Passenger(5,"student2");
  passenger3 = new Passenger(5,"student3");
  EXPECT_EQ(bus->LoadPassenger(passenger1),true);
  EXPECT_EQ(bus->GetNumPassengers(), 1);
  EXPECT_EQ(bus->LoadPassenger(passenger2),true);
  EXPECT_EQ(bus->GetNumPassengers(), 2);
  EXPECT_EQ(bus->LoadPassenger(passenger3),true);
  EXPECT_EQ(bus->GetNumPassengers(), 3);
}


TEST_F(BusTests, Move) {
  EXPECT_EQ(bus->Move(), true);
}
