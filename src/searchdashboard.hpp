#ifndef RPICONTROL_SEARCHDASHBOARD_H
#define RPICONTROL_SEARCHDASHBOARD_H

#include "../utils/utils.hpp"
#include "../src/deviceproperties.hpp"

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

using namespace std;

class SearchDashboard {
private:
    const string PKG_MASK = "mikhnovich.oleg.rpicontrol";
    const short PORT = 4822;
    const size_t BUFF_SIZE = 2048;
    void start_server();
public:
    SearchDashboard();
};

#endif //RPICONTROL_SEARCHDASHBOARD_H
