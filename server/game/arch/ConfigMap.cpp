#include "ConfigMap.h"

#include <fstream>
#include <SOException.h>

#define KEY_VALUE_SEPARATOR '='

ConfigMap::ConfigMap(const std::string& file_path) {
    std::ifstream configFile(file_path);
    if (!configFile.is_open()) {
        throw SOException();
    }

    std::string line;
    size_t pos;
    while (!configFile.eof()) {
        std::getline(configFile, line);
        pos = line.find(KEY_VALUE_SEPARATOR);
        configMap[line.substr(0, pos)] = line.substr(pos + 1);
    }

    configFile.close();
}

std::string ConfigMap::at(const std::string& key) const {
    return configMap.at(key);
}
