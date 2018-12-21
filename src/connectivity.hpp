#ifndef RPICONTROL_CONNECTIVITY_H
#define RPICONTROL_CONNECTIVITY_H

#include "../utils/utils.hpp"

#include <string>
#include <vector>
#include <regex>

typedef struct {
    std::string name;
    bool status;
    std::string ip;
    std::string mac;
} CONNECTION;

class Connectivity {
public:
    CONNECTION* get_ethernet_connection();

private:
    std::vector<std::string> get_interfaces_list(std::vector<std::string> data);
    bool find_connect_status(std::vector<std::string> data);
    std::string find_ip_address(std::vector<std::string> data);
    std::string find_mac_address(std::vector<std::string> data);
    unsigned short count_divs(std::string row);
};


#endif //RPICONTROL_CONNECTIVITY_H
