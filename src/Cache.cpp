#include "../include/Cache.h"


bool Cache::has(const std::string &key) {
    return (cache_storage.at(key))? true : false;
}