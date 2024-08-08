#include "../include/Server.h"
#include "../include/Utils.h"
#include "../include/RequestHandler.h"
#include "../include/ResponseHandler.h"

//include "../include/Logger.h"


Server::Server(const std::string& port, const std::string& ip)
    : server_socket(DEFAULT_SERVER_PORT){}

Server::~Server() noexcept { stop(); }

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
            //logginga
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
    std::string request_ready_to_send = client_connection->receive_request();

    //TO DO: CACHING

    std::string host = ;
    TargetConnection target_connection = TargetConnection(host);

    //std::string response = handle_target(target_connection, request_ready_to_send);
    //client_connection->send_response(response);

}

std::string Server::handle_target(TargetConnection target_connection, const std::string& request){
    target_connection.send_request(request);
    return target_connection.receive_response();
}