#include "audiocontrol.hpp"

int AudioControl::set_volume(unsigned short value) {
    std::string cmd;
    cmd.clear();
    cmd += "amixer set PCM -- ";
    cmd += std::to_string(coefficients[value]);
    return system(cmd.data());
}

unsigned short AudioControl::get_volume() {
    std::string data = Utils::exec("amixer get PCM");
    std::string row = Utils::split(data, "\n")[4];
    short v = (short) strtoul(Utils::split(row, " ")[4].data(), nullptr, 0);
    for (unsigned short i = 0; i < 101; ++i) {
        if (abs(coefficients[i] - v) <= 10) return i;
    }
    return 0;
}


