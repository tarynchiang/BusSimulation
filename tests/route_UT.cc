/*
 * route unit test
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>

#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/route.h"
#include "src/passenger_generator.h"
#include "src/random_passenger_generator.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class RouteTests : public ::testing::Test {
    protected:
        Route* route1;
        double* distances;
        Stop** stops;
        std::list<double> probs;
        std::list<Stop *> gStops;
        RandomPassengerGenerator* generator;

    virtual void SetUp() {
        distances = new double[2];
        stops = new Stop*[3];
        
        //Northrop Mall
        stops[0] = new Stop(0,44.976575, -93.235309);
        gStops.push_back(new Stop(0,44.976575, -93.235309));
        //Willy Hall
        stops[1] = new Stop(1,44.973204, -93.243640);
        gStops.push_back(new Stop(1,44.973204, -93.243640));
        //Carlson School of Management 
        stops[2] = new Stop(2,44.970598, -93.244726);
        gStops.push_back(new Stop(2,44.970598, -93.244726));

        distances[0] = 1.0;
        distances[1] = 1.0;
        
        probs.push_back(0.15);
        probs.push_back(0.20);
        probs.push_back(0.25);

        generator = new RandomPassengerGenerator(probs,gStops);
        route1 = new Route("University Avenue Circulator",stops,distances,3,generator);
    }
    
    virtual void TearDown() {
    }
};

TEST_F(RouteTests, Constructor){
    EXPECT_EQ(route1->IsAtEnd(),false);
    EXPECT_EQ(route1->GetTotalRouteDistance(),2);
}

TEST_F(RouteTests, isAtEnd){
    EXPECT_EQ(route1->IsAtEnd(),false);
}


