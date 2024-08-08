
#ifndef PROXY_CLIENTCONNECTION_H
#define PROXY_CLIENTCONNECTION_H

#include <winsock2.h>
#include <string>
#include <thread>
#include <ws2tcpip.h>
#include <memory>

#include "RequestHandler.h"

//const int DEFAULT_BUFLEN = 6144;

class ClientConnection{
public:
    ClientConnection(SOCKET socket);
    ~ClientConnection();

private:
     SOCKET client_socket;
     std::shared_ptr<RequestHandler> request_h;
};

#endif //PROXY_CLIENTCONNECTION_H
