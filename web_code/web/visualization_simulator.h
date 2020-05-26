/**
 * @file visualization_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_
#define WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_

#include <vector>
#include <list>
#include <string>

#include "web_code/web/web_interface.h"
#include "src/config_manager.h"
#include "src/iobserver.h"
#include "src/bus_depot.h"

class Route;
class Bus;
class Stop;

class VisualizationSimulator {
 public:
  VisualizationSimulator(WebInterface*, ConfigManager*);
  ~VisualizationSimulator();

  void Start(const std::vector<int>&, const int&);
  bool Update();
  bool CanUpdate();
  void TogglePause();
  void ClearListeners();
  void AddListener(std::string*, IObserver<BusData>*);
  /**
   * add observer to stop
   * @param id stop id
   * @param observer observer 
   * @return void
  */
  void AddListenerStop(std::string* id, IObserver<StopData>* observer);

 private:
  void ExecuteUpdate();
  WebInterface* webInterface_;
  ConfigManager* configManager_;

  std::vector<int> busStartTimings_;
  std::vector<int> timeSinceLastBus_;
  int numTimeSteps_;
  int simulationTimeElapsed_;

  std::vector<Route *> prototypeRoutes_;
  std::vector<Bus *> busses_;
  BusDepot* bus_depot_;

  int busId = 1000;
  bool paused_;;

  std::string bus_file_name = "BusData.csv";
};

#endif  // WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_