#include <libconfig.h++>
#include "Config.hpp"
#include <fstream>
#include <iostream> // For error handling

std::map<std::string, std::string> Config::_configMap;

void Config::load(const std::string& file) {
    libconfig::Config cfg;

    try {
        cfg.readFile(file.c_str());
    } catch (const libconfig::FileIOException& e) {
        std::cerr << "Error: Unable to read the configuration file: " << e.what() << std::endl;
        return;
    } catch (const libconfig::ParseException& e) {
        std::cerr << "Error: Failed to parse the configuration file at line " << e.getLine() << ": " << e.getError() << std::endl;
        return;
    }

    const libconfig::Setting& root = cfg.getRoot();

    // Load all the configuration key-value pairs from the file
    for (const auto& key : root) {
        const std::string& keyName = key.getName();
        std::string value;
        key.lookupValue(keyName.c_str(), value);

        _configMap[keyName] = value;
    }
}

bool Config::set(const std::string& key, const std::string& value) {
    // Find the key in the map
    auto it = _configMap.find(key);

    if (it != _configMap.end()) {
        // Update the value for the given key
        _configMap[key] = value;
        return true;
    }

    return false; // Key not found
}

void Config::save(const std::string& file) {
    libconfig::Config cfg;

    libconfig::Setting& root = cfg.getRoot();

    // Add all the key-value pairs to the configuration object
    for (const auto& keyValuePair : _configMap) {
        root.add(keyValuePair.first.c_str(), libconfig::Setting::TypeString) = keyValuePair.second;
    }

    // Write the configuration to the file
    try {
        cfg.writeFile(file.c_str());
    } catch (const libconfig::FileIOException& e) {
        std::cerr << "Error: Unable to write the configuration file: " << e.what() << std::endl;
    }
}

void Config::print() {
    for (const auto& keyValuePair : _configMap) {
        std::cout << keyValuePair.first << " = " << keyValuePair.second << std::endl;
    }
}