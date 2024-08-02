#include <string>

#include <thread>
#include <ws2tcpip.h>

std::string receive_request(SOCKET socket){
    char buffer[DEFAULT_BUFLEN];
    std::string request;
    int bytes_received;
    bool is_headers_over;

    while(!is_headers_over){
        bytes_received = recv(socket, buffer, DEFAULT_BUFLEN, 0);
        if(bytes_received > 0) {
            request.append(buffer, bytes_received);

            if (request.find("\r\n\r\n") != std::string::npos) {
                is_headers_over = true;
            }
        }

        else if(bytes_received == 0){
            break;
        }

        else if(bytes_received == SOCKET_ERROR){
            //logging
        }
    }
    return request;
}

SOCKET create_target_socket(const std::string& host, int port){
    SOCKET target_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(target_socket == INVALID_SOCKET){
        //logging & error handling
    }

    struct addrinfo* result = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::string port_str = std::to_string(port);
    int addr_result = getaddrinfo(host.c_str(), port_str.c_str(), &hints, &result);
    if (addr_result != 0) {
       //logging & error handling
    }

    int connection = connect(target_socket, result->ai_addr, (int)result->ai_addrlen);
    if(connection == SOCKET_ERROR){
        //logging
        WSACleanup();
    }

    freeaddrinfo(result);

    return target_socket;
}

void ClientHandler::handle_client(SOCKET client_socket) {
    HttpRequest request = HTTPHandler::parse_http_request((const std::string&)receive_request(client_socket));

    std::string target_host = request.headers.at("Host");

    SOCKET target_socket = create_target_socket(target_host, TARGET_PORT);

    forward_data(request, sizeof(request), target_socket);

}

std::string ClientHandler::forward_data( const std::string, request, int requestLength, SOCKET target_socket) {
    send(target_socket, )
}