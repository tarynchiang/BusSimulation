
/**
 * @file visualization_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include <iostream>
#include <sstream>

#include "web_code/web/visualization_simulator.h"

#include "src/bus.h"
#include "src/route.h"
#include "src/file_writer.h"
#include "src/util.h"
#include "src/file_writer_manager.h"
#include "src/iobserver.h"

VisualizationSimulator::VisualizationSimulator(WebInterface* webI,
              ConfigManager* configM) {
    webInterface_ = webI;
    configManager_ = configM;
    paused_ = false;
}

VisualizationSimulator::~VisualizationSimulator() {
    delete bus_depot_;
}

void VisualizationSimulator::ClearListeners() {
    std::cout << "//////////Clearing listeners//////////" << std::endl;
    for (int i = 0; i < static_cast<int>(busses_.size()); i++) {
        busses_[i]->ClearObservers();
    }

    for (std::vector<int>::size_type i = 0; i < prototypeRoutes_.size(); i++) {
        std::list<Stop *> stoplist = prototypeRoutes_.at(i)->GetStops();
        
        for (std::list<Stop*>::iterator it = stoplist.begin(); it != stoplist.end(); it++) {
            (*it)->ClearObservers();
        }
    }
}

void VisualizationSimulator::AddListener(std::string* id, IObserver<BusData>* observer) {
    for (int i = 0; i < static_cast<int>(busses_.size()); i++) {
        if (*id == busses_[i]->GetName()) {
            busses_[i]->RegisterObserver(observer);
        }
    }
}

void VisualizationSimulator::AddListenerStop(std::string* id, IObserver<StopData>* observer) {

    for (std::vector<int>::size_type i = 0; i < prototypeRoutes_.size(); i++) {
        std::list<Stop *> stoplist = prototypeRoutes_.at(i)->GetStops();
        
        for (std::list<Stop*>::iterator it = stoplist.begin(); it != stoplist.end(); it++) {
            if (*id == std::to_string((*it)->GetId())) {
                (*it)->RegisterObserver(observer);
            }
        }
    }
}

void VisualizationSimulator::TogglePause() {
    std::cout << "Toggling Pause" << std::endl;
    paused_ = !paused_;
}

void VisualizationSimulator::Start(const std::vector<int>& busStartTimings,
              const int& numTimeSteps) {
    busStartTimings_ = busStartTimings;
    numTimeSteps_ = numTimeSteps;
    bus_depot_ = new BusDepot();

    FileWriter* file_writer = new FileWriter();
    (file_writer)->Clear("PassData.csv"); 
    (file_writer)->Clear("BusData.csv"); 


    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);

        prototypeRoutes_[i]->UpdateRouteData();
        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
    }

}

bool VisualizationSimulator::Update() {
    // Code called to update simulator. Will first check if
    // we are in a state where we can update (e.g., not paused, not finished)
    // then call ExecuteUpdate() to actually call update if possible
    // return whether or not ExecuteUpdate() was called
    bool can_update = CanUpdate();
    if (can_update) {
        ExecuteUpdate();
    }
    return can_update;
}

bool VisualizationSimulator::CanUpdate() {
    // Check whether or not simulator can update
    // maybe unable to update because paused, terminated, etcetra
    // only cares about whether or not it is paused right now
    return !paused_;
}

void VisualizationSimulator::ExecuteUpdate() {
    // This function has the same text as what Update() used to have
    // I added a gating mechanism for pause functionality
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
            Route * outbound = prototypeRoutes_[2 * i];
            Route * inbound = prototypeRoutes_[2 * i + 1];

            busses_.push_back(bus_depot_->SendOutBus(std::to_string(busId),
                              outbound->Clone(), inbound->Clone(), 1));
            busId++;

            timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
            timeSinceLastBus_[i]--;
        }
    }

    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update busses
    std::ostringstream oss;
    std::vector<std::string> data;
    FileWriter* file_writer;
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();
        
        //newly added
        bool flag = busses_[i]->CheckRoute();
        if(!flag){
            busses_[i]= new MaroonBus(busses_[i]);
        }else{
            busses_[i]= new GoldBus(busses_[i]);
        }
        
        if (busses_[i]->IsTripComplete()) {
            //write the bus data here 
            busses_[i]->Report(oss);
            data = Util::processOutput(oss);
            file_writer = FileWriterManager::GetInstance();
            file_writer->Write(bus_file_name,data);
            oss.str("");

            webInterface_->UpdateBus(busses_[i]->GetBusData(), true);
            busses_.erase(busses_.begin() + i);
            continue;
        }

        webInterface_->UpdateBus(busses_[i]->GetBusData());

        busses_[i]->Report(std::cout);

        
        
    }

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;

    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();

        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());

        prototypeRoutes_[i]->Report(std::cout);
    }
}