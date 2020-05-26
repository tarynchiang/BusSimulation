/**
 * @file file_writwr.h
 *
 * @copyright 2019 Yi-ting Chiang, All rights reserved.
 */
#ifndef SRC_FILE_WRITER_H_
#define SRC_FILE_WRITER_H_

#include <string>
#include <vector>

/**
 * @brief class for writing data to file 
 */
class FileWriter {
 public:
  /**
   * write data to file 
   * @param file_name the name of file we should write into
   * @param data_ vector of string 
   * @return void
  */
  void Write(std::string file_name,std::vector<std::string>data_);
  /**
   * clearing all data in file 
   * @param file_name the name of file we should clear
   * @return void
  */
  void Clear(std::string file_name);
};

#endif  // SRC_FILE_WRITER_H_

