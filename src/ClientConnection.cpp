#include "../include/ClientConnection.h"

ClientConnection::ClientConnection(SOCKET socket) : client_socket(socket), request_h(std::make_shared<RequestHandler>()){}

ClientConnection::~ClientConnection(){
    if(client_socket != INVALID_SOCKET){
        closesocket(client_socket);
    }
}

std::string ClientConnection::receive_request(){
    std::string request;

    request;

    bytes_received = recv(client_socket, , DEFAULT_BUFLEN, 0);
        if(bytes_received > 0) {
            request.append(buffer, bytes_received);


        }
    return request;
}

void ClientConnection::send_response(const std::string& response) {
    send(client_socket, response.c_str(), response.size(), 0);
}
