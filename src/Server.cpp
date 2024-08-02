#include "../include/Server.h"
#include "../include/Utils.h"

//include "../include/Logger.h"

Server::Server(const std::string& port, const std::string& ip)
    : server_port(DEFAULT_PORT), server_socket(DEFAULT_PORT), running_(false){}

Server::~Server() {
    stop();
}

bool Server::start(){
    if(!Utils::init_winsock()){
        //logging
        return false;
    }

    if(!server_socket.initialize()){
        //logging
        return false;
    }

    //logging

    while(true){
        SOCKET client_socket = server_socket.accept_client();
        if(client_socket == INVALID_SOCKET){
            //logging
            continue;
        }

        auto client_connection = std::make_shared<ClientConnection>(client_socket);
        threads.emplace_back(&Server::handle_clients, this, client_connection);
    }
}

void Server::stop() {
    server_socket.~ServerSocket();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    Utils::cleanup_winsock();
}

//to handle request from client and response them
void Server::handle_clients(std::shared_ptr<ClientConnection> client_connection) {
    std::string request = client_connection->receive_request();

    if(Cache.has_(request)){
        std::string cached_response = Cache.get_(request);
        client_connection->send_response(cached_response);
    }
    else{
        RequestHandler request_handler;
        ResponseHandler response_handler;

        std::string response = request_handler.handle_(request);
        response = response_handler.handle_(response);

        cache.store(request, response);
        client_connection->send_response(response);
    }
}