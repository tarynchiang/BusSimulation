/**
 * @file my_web_server_session.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include <string>
#include <map>

#include "web_code/web/my_web_server_session.h"
#include "web_code/web/my_web_server_command.h"

void MyWebServerSession::receiveJSON(picojson::value& val) {
    std::string cmd = val.get<picojson::object>()["command"].get<std::string>();
    // std::cout << val.get<picojson::object>()["command"].get<std::string>()
    // << std::endl;
    std::map<std::string, MyWebServerCommand*>::iterator it
                = state.commands.find(cmd);
    if (it != state.commands.end()) {
        it->second->execute(this, val, &state);
    }
}
