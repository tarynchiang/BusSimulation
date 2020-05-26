/**
 * @file util.h
 *
 * @copyright 2019 Yi-ting Chiang, All rights reserved.
 */
#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>


/**
 * @brief class for turning data to a vector of strings
 */
class Util {
 public:
    /**
     * turning data to a vector of strings
     * @param oss string stream
     * @return vector of strings
    */
    static std::vector<std::string> processOutput(std::ostringstream& oss);

};
#endif  // SRC_UTIL_H_
