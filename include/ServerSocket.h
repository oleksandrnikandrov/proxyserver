#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <winsock2.h>

const int DEFAULT_PORT = 8080;

class ServerSocket {
public:
    ServerSocket(const int port);
    ~ServerSocket();

    bool initialize();
    SOCKET accept_client();

private:
    int port;
    SOCKET socket_handle;

    bool bind_();
    bool listen_();
};

#endif // SERVER_SOCKET_H