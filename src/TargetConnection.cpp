#include "../include/TargetConnection.h"
#include "../include/ResponseHandler.h"

TargetConnection::TargetConnection(const std::string &host) : target_socket(create_target_socket(host)){}

TargetConnection::~TargetConnection() noexcept {
    if(target_socket != INVALID_SOCKET){
        closesocket(target_socket);
    }
}

SOCKET TargetConnection::create_target_socket(const std::string& host){
    struct addrinfo* result = nullptr,
                    *ptr = nullptr,
                    hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::string port_str = std::to_string(DEFAULT_TARGET_PORT);
    int addr_result = getaddrinfo(host.c_str(), port_str.c_str(), &hints, &result);
    if (addr_result != 0) {
        //logging & error handling
        //SOMEHOW HANDLE ERROR
    }

    for(ptr = result; ptr != nullptr; ptr->ai_next) {
        target_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(target_socket == INVALID_SOCKET){
            //logging
            //SOMEHOW HANDLE ERROR
            continue;
        }

        int connection = connect(target_socket, ptr->ai_addr, (int) ptr->ai_addrlen);
        if (connection == SOCKET_ERROR) {
            //logging
            closesocket(target_socket);
            target_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    return target_socket;
}

void TargetConnection::send_request(const std::string &request) {
    int sent_result = send(target_socket, request.c_str(), (int)request.length(), 0);
    if(sent_result == SOCKET_ERROR){
        //logging
        //SOMEHOW HANDLE ERROR
    }
}

std::string TargetConnection::receive_response() {
    char *recvbuf = new char[DEFAULT_RECVBUFLEN];

    int recv_result = recv(target_socket, recvbuf, DEFAULT_RECVBUFLEN, 0);
    if(recv_result > 0){
        //logging bytes received
    }
    else if(recv_result == 0){
        //logging connection closed
    }
    else{
        //loging that reciving is failed WSAGETLASTERROR()
    }

    std::string response(recvbuf);

    //logging response

    return response;
}