/**
 * @file my_web_server_command.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef WEB_CODE_WEB_MY_WEB_SERVER_COMMAND_H_
#define WEB_CODE_WEB_MY_WEB_SERVER_COMMAND_H_

#include <vector>

#include "src/config_manager.h"
#include "src/data_structs.h"
#include "web_code/web/visualization_simulator.h"
#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_session_state.h"
#include "web_code/web/my_web_server.h"

class MyWebServerSession;
class MyWebServerSessionState;

class MyWebServerCommand {
 public:
  virtual ~MyWebServerCommand() {}
  virtual void execute(MyWebServerSession* session, picojson::value& command,
                        MyWebServerSessionState* state) = 0;
};


///***** * * * * * COMMANDS * * * * * ******///

class GetRoutesCommand : public MyWebServerCommand {
 public:
  GetRoutesCommand(MyWebServer* ws);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  MyWebServer* myWS;
};

class GetBussesCommand : public MyWebServerCommand {
 public:
  GetBussesCommand(MyWebServer* ws);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  MyWebServer* myWS;
};

class StartCommand : public MyWebServerCommand {
 public:
  StartCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
  std::vector<int> timeBetweenBusses;
  int numTimeSteps;
};

class UpdateCommand : public MyWebServerCommand {
 public:
  UpdateCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

class PauseCommand : public MyWebServerCommand {
 public:
  PauseCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

class AddListenerCommand: public MyWebServerCommand {
 public:
  AddListenerCommand(VisualizationSimulator* sim);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

/**
 * @brief class for listening stop observed command
*/
class AddListenerStopCommand: public MyWebServerCommand {
 public:
  AddListenerStopCommand(VisualizationSimulator* sim);
  /**
   * listening stop observed command
   * @param session web session
   * @param command command 
   * @param state state of web session
   * @return void
  */
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  VisualizationSimulator* mySim;
};

class InitRoutesCommand : public MyWebServerCommand {
 public:
  InitRoutesCommand(ConfigManager* cm);
  void execute(MyWebServerSession* session, picojson::value& command,
                MyWebServerSessionState* state) override;
 private:
  ConfigManager* cm;
};

#endif  // WEB_CODE_WEB_MY_WEB_SERVER_COMMAND_H_