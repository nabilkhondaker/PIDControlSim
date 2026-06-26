#pragma once
#include <string>
#include <map>

namespace sim {
namespace utils {

class ConfigParser {
private:
    std::map<std::string, std::string> configData;

public:
    explicit ConfigParser(const std::string& filename);
    
    double getDouble(const std::string& key) const;
    std::string getString(const std::string& key) const;
    bool hasKey(const std::string& key) const;
};

} // namespace utils
} // namespace sim
