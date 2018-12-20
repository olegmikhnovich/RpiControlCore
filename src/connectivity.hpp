#ifndef RPICONTROL_CONNECTIVITY_H
#define RPICONTROL_CONNECTIVITY_H

#include "../utils/utils.hpp"

#include <string>
#include <vector>
#include <regex>

using namespace std;

typedef struct {
    string name;
    bool status;
    string ip;
    string mac;
} CONNECTION;

class Connectivity {
public:
    CONNECTION* get_ethernet_connection();

private:
    vector<string> get_interfaces_list(vector<string> data);
    bool find_connect_status(vector<string> data);
    string find_ip_address(vector<string> data);
    string find_mac_address(vector<string> data);
    unsigned short count_divs(string row);
};


#endif //RPICONTROL_CONNECTIVITY_H
