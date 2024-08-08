
#ifndef PROXY_SERVER_H
#define PROXY_SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <memory>
#include <vector>
#include <thread>

#include "ServerSocket.h"
#include "ClientConnection.h"
#include "TargetConnection.h"
#include "Cache.h"

enum class HandlingType{
    BUFFERED,
    STREAMING
};

class Server{

public:
    Server(const std::string& port, const std::string& ip);
    ~Server();

    bool start();
    void stop();

private:
    ServerSocket server_socket;
    std::vector<std::thread> threads;
    Cache cache;

    void handle_clients(std::shared_ptr<ClientConnection> client_connection);
};

#endif //PROXY_SERVER_H
