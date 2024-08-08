#include "../include/ServerSocket.h"
#include "../include/Utils.h"

//#include "../include/Logger.h"

#include <iostream>

ServerSocket::ServerSocket(int port) : port(port), socket_handle(INVALID_SOCKET){}

ServerSocket::~ServerSocket() noexcept {
    if(socket_handle != INVALID_SOCKET){
        closesocket(socket_handle);
    }
}

bool ServerSocket::initialize() {
    struct addrinfo *result = nullptr,
                    hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::string port_str = std::to_string(DEFAULT_PORT);
    int addr_result = getaddrinfo(nullptr, port_str.c_str(), &hints, &result);
    if(addr_result != 0){
        //logging
        this->~ServerSocket();
        // TO DO EXCEPTION LOGIC
    }

    socket_handle = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(socket_handle != INVALID_SOCKET){
        //logging
        freeaddrinfo(result);
    }

    return bind_() && listen_();
}

bool ServerSocket::bind_(){
    sockaddr_in server_addr {};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(socket_handle, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR){
        //logging
        return false;
    }
    return true;
}

bool ServerSocket::listen_(){
    if(listen(socket_handle, SOMAXCONN) == SOCKET_ERROR){
        //logging
        return false;
    }
    return true;
}

SOCKET ServerSocket::accept_client() { return accept(socket_handle, nullptr, nullptr);}