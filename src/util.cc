#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include "src/util.h"
using namespace std;


std::vector<std::string> Util::processOutput(std::ostringstream& oss){
    //stores parsed data into a container

    vector<std::string> container;
    string temp = oss.str();

    stringstream ss(temp);
    string word;

    while (ss >> word) {
        container.push_back(word);
    }

    return container;
}

