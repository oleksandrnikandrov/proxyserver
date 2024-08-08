#include "../include/Utils.h"

bool Utils::init_winsock() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(iResult != 0){
        //logging
        return false;
    }
    return true;
}

bool cleanup_winsock(){
    WSACleanup();
}
