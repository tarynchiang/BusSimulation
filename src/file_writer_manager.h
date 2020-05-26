/**
 * @file file_writer_manager.h
 *
 * @copyright 2019 Yi-ting Chiang, All rights reserved.
 */
#ifndef SRC_FILE_WRITER_MANAGER_H_
#define SRC_FILE_WRITER_MANAGER_H_

#include "src/file_writer.h"

class FileWriter;

/**
 * @brief class for implementing singleton pattern on file writer object
 */
class FileWriterManager {
 public:
    /**
     * getter method for file writer object
     * @return FileWriter object
    */
    static FileWriter* GetInstance();
 private:
    static FileWriter* file_writer; 
};


#endif  // SRC_FILE_WRITER_MANAGER_H_


