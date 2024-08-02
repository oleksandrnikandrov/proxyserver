#include "../include/ServerSocket.h"
#include "../include/Utils.h"

//#include "../include/Logger.h"

#include <iostream>

ServerSocket::ServerSocket(int port) : port(port), socket_handle(INVALID_SOCKET){}

ServerSocket::~ServerSocket(){
    if(socket_handle != INVALID_SOCKET){
        closesocket(socket_handle);
    }

}

bool ServerSocket::initialize() {
    socket_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_handle == INVALID_SOCKET){
        //logging
        return false;
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

SOCKET ServerSocket::accept_client() { return accept(socket_handle, nullptr, nullptr)}