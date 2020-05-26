/*
 * stop unit test
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/bus.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class StopTests : public ::testing::Test {
    protected:
        Stop* stop1;
        Stop* stop2;
        Stop* stop3;

    virtual void SetUp() {
        //Northrop Mall
        stop1 = new Stop(0,44.976575, -93.235309);
        //Willy Hall
        stop2 = new Stop(1,44.973204, -93.243640);
        //Carlson School of Management 
        stop3 = new Stop(2,44.970598, -93.244726);
    }
    
    virtual void TearDown() {
        delete stop1;
        delete stop2;
        delete stop3;
    }
};

TEST_F(StopTests, Constructor){
    EXPECT_EQ(stop1->GetId(), 0);
    EXPECT_EQ(stop2->GetId(), 1);
	EXPECT_EQ(stop3->GetId(), 2);
}
