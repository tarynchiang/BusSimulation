/*
 * file_writer unit test
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../src/file_writer_manager.h"
#include "../src/file_writer.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FileWriterTests : public ::testing::Test {
    protected:
        FileWriter* fw;
        
    virtual void SetUp() {
        fw = FileWriterManager::GetInstance();
    }
    
    virtual void TearDown() {
        delete fw;
    }
};

TEST_F(FileWriterTests, Write){
    vector<string> data1;
    data1.push_back("test1");
    data1.push_back("test2");
    vector<string> data2;
    data2.push_back("test3");
    data2.push_back("test4");

    fw->Clear("test.csv");
    fw->Write("test.csv",data1);
    fw->Write("test.csv",data2);
    
    ifstream inFile;
    inFile.open("test.csv");
    
    string actual1;
    inFile >> actual1;
    string expected1 = "test1,test2";
    EXPECT_EQ(actual1,expected1);

    string actual2;
    inFile >> actual2;
    string expected2 = "test3,test4";
    EXPECT_EQ(actual2,expected2);
}
