/**
 * @file my_web_server_session.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef WEB_CODE_WEB_MY_WEB_SERVER_SESSION_H_
#define WEB_CODE_WEB_MY_WEB_SERVER_SESSION_H_

#include "WebServer.h"
#include "web_code/web/my_web_server_session_state.h"

class MyWebServerSession : public JSONSession {
 public:
  MyWebServerSession(MyWebServerSessionState s) : state(s) {}
  ~MyWebServerSession() {}

  void receiveJSON(picojson::value& val) override;
  void update() override {}

 private:
  MyWebServerSessionState state;
};


#endif  // WEB_CODE_WEB_MY_WEB_SERVER_SESSION_H_