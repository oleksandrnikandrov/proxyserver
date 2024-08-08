
#ifndef PROXY_RESPONSEHANDLER_H
#define PROXY_RESPONSEHANDLER_H

#include <string>

const int DEFAULT_RECVBUFLEN = 4096;

class ResponseHandler{
public:
    std::string handle(const std::string& response);

};

#endif //PROXY_RESPONSEHANDLER_H
