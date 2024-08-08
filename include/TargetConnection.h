
#ifndef PROXY_TARGETCONNECTION_H
#define PROXY_TARGETCONNECTION_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

const int DEFAULT_TARGET_PORT = 80;


class TargetConnection{
public:
    TargetConnection(const std::string& host);
    ~TargetConnection();

    std::string receive_response();
    void send_request(const std::string& request);

private:
    SOCKET create_target_socket(const std::string& host);
    SOCKET target_socket;
};


#endif //PROXY_TARGETCONNECTION_H
