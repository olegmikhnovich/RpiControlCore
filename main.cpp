#include "main.hpp"

constexpr unsigned int sw_str(const char* str, int h = 0) {
    return !str[h] ? 5381 : (sw_str(str, h+1) * 33) ^ str[h];
}

string RpiControlCore::process_package(std::string &header, std::string &message) {
    string response;

    switch (sw_str(header.data())) {
        case sw_str(H_SCANNER):
            if (message == PKG_MASK) {
                auto d = new DeviceProperties;
                auto answer = d->get_device_name() + "|" + d->get_device_model() + "|" + d->get_os_version();
                delete d;
                response = answer;
            } else {
                response = "ACCESS_DENY";
            }
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
        line[0] = '\0';
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

void app_terminate_handler(int) {
    sigint_flag = 1;
}

void app_server_thread_run() {
    std::cout << "Starting RpiControl server ..." << std::endl;
    auto handler = new RpiControlCore;
    handler->start_server();
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
