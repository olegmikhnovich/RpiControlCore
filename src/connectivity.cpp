#include "connectivity.hpp"

CONNECTION *Connectivity::get_ethernet_connection() {
    auto data = Utils::split(Utils::exec("ifconfig"), "\n");
    auto interfaces = get_interfaces_list(data);
    for (auto &i : interfaces) {
        if (i.length() > 3 && i.substr(0, 3) == "eth") {
            std::string cmd = "ifconfig ";
            cmd += i;
            auto eth_conf = Utils::split(Utils::exec(cmd.data()), "\n");
            auto conn = new CONNECTION;
            conn->name = i;
            conn->status = find_connect_status(eth_conf);
            conn->ip = find_ip_address(eth_conf);
            conn->mac = find_mac_address(eth_conf);
            return conn;
        }

    }
    return nullptr;
}

std::vector<std::string> Connectivity::get_interfaces_list(std::vector<std::string> data) {
    std::vector<std::string> interfaces;
    for (auto &i : data) {
        if (count_divs(i) == 1) {
            interfaces.push_back(Utils::trim_copy(Utils::split(i, ":")[0]));
        }
    }
    return interfaces;
}

bool Connectivity::find_connect_status(std::vector<std::string> data) {
    for (auto &i : data) {
        auto row = Utils::split(i, " ");
        for (auto &r : row) {
            std::string v = transform(r.begin(), r.end(), r.begin(), ::tolower).base();
            if (v == "running") return true;
        }
    }
    return false;
}

std::string Connectivity::find_ip_address(std::vector<std::string> data) {
    for (auto &row : data) {
        auto words = Utils::split(row, " ");
        for (auto &w : words) {
            try {
                std::regex re("([0-9A-Fa-f]{1,4}:){7}[0-9A-Fa-f]{1,4}|(\\d{1,3}\\.){3}\\d{1,3}");
                std::smatch match;
                if (regex_search(w, match, re) && match.size() > 1) {
                    return match.str();
                } else {
                }
            } catch (std::regex_error& e) {
                return std::string();
            }
        }
    }
    return std::string();
}

std::string Connectivity::find_mac_address(std::vector<std::string> data) {
    for (auto &row : data) {
        auto words = Utils::split(row, " ");
        for (auto &w : words) {
            try {
                std::regex re("^([0-9a-fA-F][0-9a-fA-F]:){5}([0-9a-fA-F][0-9a-fA-F])$");
                std::smatch match;
                if (regex_search(w, match, re) && match.size() > 1) {
                    return match.str();
                } else {
                }
            } catch (std::regex_error& e) {
                return std::string();
            }
        }
    }
    return std::string();
}

unsigned short Connectivity::count_divs(std::string row) {
    unsigned short count = 0;
    for (auto &c : row) {
        if (c == ':') count++;
    }
    return count;
}

