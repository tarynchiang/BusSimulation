#include <string>
#include <vector>
#include <fstream>
#include "src/file_writer.h"

void FileWriter::Write(std::string file_name,std::vector<std::string> data_){
    std::ofstream myFile;
    myFile.open(file_name,std::ios_base::app);

    for (std::vector<std::string>::iterator it = data_.begin(); it != data_.end(); it++) {
        myFile << (*it);
        if(it != data_.end()-1){
            myFile << ",";
        }

    }
    myFile << "\n";
    myFile.close();
}

void FileWriter::Clear(std::string file_name){
    std::ofstream myFile;
    myFile.open(file_name);
    myFile.close();
}