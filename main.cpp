#include "main.hpp"

/*
 * Utils block
 *
 * */

void app_terminate_handler(int) {
    sigint_flag = 1;
}

void app_server_thread_run() {
    std::cout << "Starting RpiControl server ..." << std::endl;
    auto handler = new RpiControlCore;
    handler->start_server();
}

constexpr unsigned int sw_str(const char* str, int h = 0) {
    return !str[h] ? 5381 : (sw_str(str, h+1) * 33) ^ str[h];
}

std::string init_response(std::string header) {
    std::string value = std::move(header);
    value += "\n";
    return value;
}

/*
 * Process package helpers
 *
 * */

bool auth_user(const std::string &package) {
    auto v = Utils::split(package, "\n");
    if (v.size() < 2) return false;
    auto dp = new DeviceProperties;
    auto name = dp->get_device_name();
    auto auth_state = dp->auth_user(v[1]);
    delete dp;
    return ((v[0] == name) && auth_state);
}

std::string get_device_info() {
    auto dp = new DeviceProperties;
    std::string res = dp->get_device_name() + "|" +
            dp->get_device_model() + "|" +
            dp->get_os_version() + "|" +
            dp->get_temperature();
    delete dp;
    return res;
}

unsigned short get_sound_volume() {
    auto audio = new AudioControl;
    auto result = audio->get_volume();
    delete audio;
    return result;
}

void set_sound_volume(unsigned short value) {
    auto audio = new AudioControl;
    audio->set_volume(value);
    delete audio;
}

std::string set_device_name(const std::string &name) {
    auto dp = new DeviceProperties;
    dp->set_device_name(name);
    auto result = dp->get_device_name();
    delete dp;
    return result;
}

bool change_password(const std::string &package) {
    auto v = Utils::split(package, "\\|");
    if (v.size() < 2) return false;
    auto dp = new DeviceProperties;
    auto result = dp->set_new_pwd(v[0], v[1]);
    delete dp;
    return result;
}

std::string RpiControlCore::process_package(std::string &header, std::string &message) {
    std::string response;

    switch (sw_str(header.data())) {
        case sw_str(H_SCANNER):
            response = init_response(H_SCANNER);
            if (message == PKG_MASK) {
                auto d = new DeviceProperties;
                auto answer = d->get_device_name() + "|" + d->get_device_model() + "|" + d->get_os_version();
                delete d;
                response += answer;
            } else {
                response += "ACCESS_DENY";
            }
            break;

        case sw_str(H_AUTH):
            response = init_response(H_AUTH);
            response += (auth_user(message)) ? "true" : "false";
            break;

        case sw_str(H_DEVICE_INFO):
            response = init_response(H_DEVICE_INFO);
            response += get_device_info();
            break;

        case sw_str(H_GET_SOUND_VOLUME):
            response = init_response(H_GET_SOUND_VOLUME);
            response += std::to_string(get_sound_volume());
            break;

        case sw_str(H_SET_SOUND_VOLUME):
            response = init_response(H_SET_SOUND_VOLUME);
            set_sound_volume(static_cast<unsigned short>( std::strtoul(message.c_str(), nullptr, 0)));
            response += std::to_string(get_sound_volume());
            break;

        case sw_str(H_SET_DEVICE_NAME):
            response = init_response(H_SET_DEVICE_NAME);
            response += set_device_name(message);
            break;

        case sw_str(H_SET_NEW_PASSWORD):
            response = init_response(H_SET_NEW_PASSWORD);
            response += (change_password(message)) ? "true" : "false";
            break;

        default:
            break;
    }
    return response;
}

void RpiControlCore::start_server() {
    int sock, listener;
    struct sockaddr_in addr{};
    char line[BUFF_SIZE];

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0) exit_app("socket", 1);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) exit_app("bind", 2);

    listen(listener, 10);
    std::cout << "-> RpiControl server started! Listen on port #" << PORT << std::endl;

    while(true)
    {
        sock = accept(listener, nullptr, nullptr);
        std::cout << "-> Accept new client connection." << std::endl;
        if(sock < 0) exit_app("accept", 3);

        recv(sock, line, BUFF_SIZE, 0);
        auto raw_msg = Utils::trim_copy(line);
        std::fill(&line[0], &line[0] + sizeof(line), 0);
        auto data = Utils::split(raw_msg, "\\^");
        if (data.size() < 2) continue;
        string header = data[0];
        string message;
        for(int i = 1; i < data.size(); i++) {
            message += data[i];
        }
        std::cout << std::endl << "-> Recived a package:" << std::endl;
        std::cout << "   Header: " << header << std::endl;
        std::cout << "   Message: " << message << std::endl;
        string answer = process_package(header, message);
        send(sock, answer.data(), answer.size(), 0);
        close(sock);
    }
}

void RpiControlCore::exit_app(const char *message, int code) {
    perror(message);
    delete this;
    exit(code);
}

int main() {
    signal(SIGINT, app_terminate_handler);
    std::thread t(app_server_thread_run);

    while(true)
    {
        if (sigint_flag) {
            std::cout << std::endl << "-> Get SIGINT!\nExiting an application..." << std::endl;
            return 0;
        }
    }
}
