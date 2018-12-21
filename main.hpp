//
// Created by Admin on 2018-12-21.
//

#ifndef RPICONTROL_MAIN_HPP
#define RPICONTROL_MAIN_HPP

#include <thread>
#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "utils/utils.hpp"
#include "src/deviceproperties.hpp"

#define PORT 4822
#define BUFF_SIZE 8192

#define PKG_MASK "mikhnovich.oleg.rpicontrol"
#define H_SCANNER "scanner"

volatile sig_atomic_t sigint_flag = 0;

class RpiControlCore {
private:
    void exit_app(const char *message, int code);
    std::string process_package(std::string &header, std::string &message);

public:
    void start_server();
};

#endif //RPICONTROL_MAIN_HPP
