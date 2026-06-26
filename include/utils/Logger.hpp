#pragma once
#include <string>
#include <vector>
#include <fstream>

namespace sim {
namespace utils {

struct DataPoint { double t, setpoint, error, control_u, state_y; };

class Logger {
private:
    std::vector<DataPoint> data;
public:
    void log(double t, double r, double e, double u, double y);
    void saveToCSV(const std::string& filename) const;
    const std::vector<DataPoint>& getData() const;
};

}
}
