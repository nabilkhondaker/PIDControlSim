#pragma once
#include "Logger.hpp"

namespace sim {
namespace utils {

class MetricsCalculator {
public:
    static void report(const std::vector<DataPoint>& data);
};

}
}
