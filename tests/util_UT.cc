/*
 * util unit test
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "../src/util.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class UtilTests : public ::testing::Test {
    protected:
        
    virtual void SetUp() {

    }
    
    virtual void TearDown() {
        
    }
};

TEST_F(UtilTests, processOutput){
    ostringstream oss;
    oss << "Name: bus" << endl;
    oss << "Speed: 1"  << endl;
    oss << "Bus Type: Cool Bus"<< endl;
    oss << "Distance to next stop: 10"<< endl;

    vector<string> actual;
    actual = Util::processOutput(oss);

    vector<string> expected;
    expected = {"Name:","bus","Speed:","1","Bus","Type:","Cool","Bus","Distance","to","next","stop:","10"};

    for(unsigned int i=0;i<actual.size();i++){
        EXPECT_EQ(actual[i],expected[i]);
    }
}
