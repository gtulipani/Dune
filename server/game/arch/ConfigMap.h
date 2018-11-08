#ifndef __CONFIG_MAP_H__
#define __CONFIG_MAP_H__

#include <map>
#include <string>

class ConfigMap {
    private:
    std::map<std::string, std::string> configMap;

    public:
    ConfigMap(const std::string& filePath);

    std::string at(const std::string& key) const;
};

#endif // __CONFIG_MAP_H__
