#include "searchdashboard.hpp"

SearchDashboard::SearchDashboard() {
    start_server();
}

void SearchDashboard::start_server() {
    int sock, listener;
    struct sockaddr_in addr{};
    char line[BUFF_SIZE];

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 10);

    while(true)
    {
        sock = accept(listener, nullptr, nullptr);
        cout << "Accept new client connection." << endl;
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

        recv(sock, line, BUFF_SIZE, 0);
        string msg = Utils::trim_copy(line);
        cout << "Message: " << msg << endl;
        line[0] = '\0';
        if (msg == PKG_MASK) {
            auto d = new DeviceProperties;
            string answer = d->get_device_name() + "|" + d->get_device_model() + "|" +  d->get_os_version();
            delete d;
            send(sock, answer.data(), answer.size(), 0);
        } else {
            string err = "ACCESS_DENY";
            send(sock, err.data(), err.size(), 0);
        }
        close(sock);
    }
}
