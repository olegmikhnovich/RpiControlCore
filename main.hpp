#ifndef RPICONTROL_MAIN_HPP
#define RPICONTROL_MAIN_HPP

#include <vector>
#include <thread>
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "utils/utils.hpp"
#include "src/deviceproperties.hpp"
#include "src/audiocontrol.hpp"
#include "src/filemanager.hpp"

#define PORT 4822
#define BUFF_SIZE 8192

#define PKG_MASK "mikhnovich.oleg.rpicontrol"
#define H_SCANNER "scanner"
#define H_AUTH "auth"
#define H_DEVICE_INFO "device-info"
#define H_GET_SOUND_VOLUME "get-sound-volume"
#define H_SET_SOUND_VOLUME "set-sound-volume"
#define H_SET_DEVICE_NAME "set-device-name"
#define H_SET_NEW_PASSWORD "set-new-password"
#define H_REBOOT_DEVICE "reboot-device"
#define H_SHUTDOWN_DEVICE "shutdown-device"
#define H_GET_DIR "get-dir"
#define H_GET_FILE "get-file"

volatile sig_atomic_t sigint_flag = 0;

class RpiControlCore {
private:
    void exit_app(const char *message, int code);
    std::string process_package(std::string &header, std::string &message);

public:
    void start_server();
};

#endif //RPICONTROL_MAIN_HPP
