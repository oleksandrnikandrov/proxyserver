
#ifndef PROXY_REQUESTHANDLER_H
#define PROXY_REQUESTHANDLER_H

#include <string>
#include <map>
#include <sstream>

//const int DEFAULT_BUFFER_SIZE = 6144;

struct HttpRequest {
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

class RequestHandler{

public:

    RequestHandler();
    ~RequestHandler();

    void read_from_socket(SOCKET client_socket);
    void push_data(const std::string& data);
    std::string build_request(const HttpRequest& http_req);
    HttpRequest parse_http_request(const std::string& raw_request);

private:
    std::string buffer;
};

#endif //PROXY_REQUESTHANDLER_H
