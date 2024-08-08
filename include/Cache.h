
#ifndef PROXY_CACHE_H
#define PROXY_CACHE_H

#include <unordered_map>
#include <string>
#include <mutex>

class Cache{
public:
    bool has(const std::string& key);
    std::string get(const std::string& key);
    void store(const std::string& key, const std::string& value);

private:
    std::unordered_map<std::string, std::string> cache_storage;
    std::mutex cache_mutex;
};

#endif //PROXY_CACHE_H