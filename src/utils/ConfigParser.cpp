#include "utils/ConfigParser.hpp"
#include <fstream>
#include <stdexcept>

namespace sim {
namespace utils {

ConfigParser::ConfigParser(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("FATAL: Could not open config file: " + filename);
    }
    
    std::string line, section;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#' || line[0] == ';') continue;
        
        // Parse sections
        if (line[0] == '[') { 
            section = line.substr(1, line.find(']') - 1) + "_"; 
            continue; 
        }
        
        // Parse key-value pairs
        auto delim = line.find('=');
        if (delim != std::string::npos) {
            std::string key = section + line.substr(0, delim);
            std::string value = line.substr(delim + 1);
            configData[key] = value;
        }
    }
}

double ConfigParser::getDouble(const std::string& key) const {
    try {
        return std::stod(configData.at(key));
    } catch (const std::out_of_range&) {
        throw std::runtime_error("Config Error: Missing numeric key -> " + key);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Config Error: Invalid number format for key -> " + key);
    }
}

std::string ConfigParser::getString(const std::string& key) const {
    try {
        return configData.at(key);
    } catch (const std::out_of_range&) {
        throw std::runtime_error("Config Error: Missing string key -> " + key);
    }
}

bool ConfigParser::hasKey(const std::string& key) const {
    return configData.find(key) != configData.end();
}

} // namespace utils
} // namespace sim
