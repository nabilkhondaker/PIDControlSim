#include "utils/Logger.hpp"

namespace sim {
namespace utils {

void Logger::log(double t, double r, double e, double u, double y) {
    data.push_back({t, r, e, u, y});
}

void Logger::saveToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    file << "Time,Setpoint,Error,Control,Output\n";
    for (const auto& d : data) {
        file << d.t << "," << d.setpoint << "," << d.error << "," << d.control_u << "," << d.state_y << "\n";
    }
}

const std::vector<DataPoint>& Logger::getData() const { return data; }

}
}
