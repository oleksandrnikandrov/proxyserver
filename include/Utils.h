
#ifndef PROXY_UTILS_H
#define PROXY_UTILS_H

#include <string>
#include <winsock2.h>

class Utils{

public:
    static bool init_winsock();
    static bool cleanup_winsock();
    static std::string socket_error_to_string(int error_code);
};

#endif //PROXY_UTILS_H
