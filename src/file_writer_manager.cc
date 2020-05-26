#include "src/file_writer_manager.h"

FileWriter* FileWriterManager::file_writer = 0;

FileWriter* FileWriterManager::GetInstance(){
      // if file_writer is not created then 
      // create a new one 
      // otherwise, return the original file_writer
      if(file_writer == 0){
          file_writer = new FileWriter();
      }
      return file_writer;
}