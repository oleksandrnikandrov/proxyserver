
#ifndef PROXY_CONNECTION_H
#define PROXY_CONNECTION_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>


#include "../include/HttpErrors.h"
//#include "../include/"

class Connection{
public:
    Connection();
    ~Connection();

    std::string receive_request();
    std::string receive_response();

    void send_response(const std::string& response);
    void send_request(const std::string& request);

private:
    SOCKET create_target_socket(const std::string& host);

    std::string request, response;
    SOCKET client_socket, target_socket;
};


#endif //PROXY_CONNECTION_H
