
#ifndef PROXY_CLIENTCONNECTION_H
#define PROXY_CLIENTCONNECTION_H


#include <winsock2.h>
#include <string>

const int DEFAULT_BUFLEN = 4096;
const int TARGET_PORT = 80;//default http port

class ClientConnection{
public:
    ClientConnection(SOCKET socket);
    ~ClientConnection();

    std::string receive_request();
    void send_response(const std::string& response);

private:
    SOCKET client_socket;
};

#endif //PROXY_CLIENTCONNECTION_H
