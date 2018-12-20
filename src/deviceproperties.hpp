#ifndef RPICONTROL_DEVICEPROPERTIES_H
#define RPICONTROL_DEVICEPROPERTIES_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>

#include "../utils/utils.hpp"

using namespace std;

typedef struct {
    string data;
    bool success;
} FILE_READER;

class DeviceProperties {
private:
    const string MODEL_FNAME = "/proc/device-tree/model";
    const string OS_V_FNAME = "/etc/os-release";
    const string DIR_PATH = "/etc/rpicontrol";
    const string DEVICE_NAME_FNAME = "devicecredname.conf";
    const string DEVICE_PWD_FNAME = "devicecredpwd.conf";
    FILE_READER* read_data_from_file(string filename);

public:
    string get_device_model();
    string get_temperature();
    string get_os_version();
    string get_device_name();
    void set_device_name(string name);
    bool auth_user(string pwd);
    bool set_new_pwd(string oldPwd, string newPwd);
};


#endif //RPICONTROL_DEVICEPROPERTIES_H
