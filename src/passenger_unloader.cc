/**
 * @file passenger_unloader.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include <iostream>
#include <sstream>
#include "src/passenger_unloader.h"
#include "src/util.h"
#include "src/file_writer_manager.h"
#include "src/file_writer.h"


int PassengerUnloader::UnloadPassengers(std::list<Passenger*>* passengers,
                                        Stop * current_stop) {
  // TODO(wendt): may need to do end-of-life here
  // instead of in Passenger or Simulator
  int passengers_unloaded = 0;

  // variables for file writer 
  std::ostringstream oss;
  std::vector<std::string> data;
  FileWriter* file_writer;

  for (std::list<Passenger *>::iterator it = passengers->begin();
      it != passengers->end();
      it++) {
    if ((*it)->GetDestination() == current_stop->GetId()) {
      //write the info to the ostringsstream
      
      (*it)->Report(oss);
      data = Util::processOutput(oss);
      file_writer = FileWriterManager::GetInstance();
      file_writer->Write(passenger_file_name,data);
      oss.str("");

      // could be used to inform scheduler of end-of-life?
      // This could be a destructor issue as well.
      // *it->FinalUpdate();
      it = passengers->erase(it);
      // getting seg faults, probably due to reference deleted objects
      // here
      it--;
      passengers_unloaded++;
    }

    
  }
  return passengers_unloaded;
}
