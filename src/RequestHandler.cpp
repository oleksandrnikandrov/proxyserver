#include "../include/RequestHandler.h"

HttpRequest RequestHandler::parse_http_request(const std::string& raw_request) {
    HttpRequest request;
    std::istringstream request_stream(raw_request);
    std::string line;

    if (std::getline(request_stream, line)) {
        std::istringstream start_line(line);
        start_line >> request.method >> request.path >> request.version;
    }

    while (std::getline(request_stream, line) && line != "\r") {
        std::string key, value;
        std::size_t delimiter_pos = line.find(':');
        if (delimiter_pos != std::string::npos) {
            key = line.substr(0, delimiter_pos);
            value = line.substr(delimiter_pos + 2);
            request.headers[key] = value;
        }
    }

    if (std::getline(request_stream, line)) {
        request.body = line;
    }

    return request;
}

void RequestHandler::push_data(const std::string &data) { buffer.append(data); }

std::string build_request(const HttpRequest* http_req){
    std::string request;
    return request;
}



