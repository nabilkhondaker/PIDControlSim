#include "utils/MetricsCalculator.hpp"
#include <iostream>
#include <cmath>

namespace sim {
namespace utils {

void MetricsCalculator::report(const std::vector<DataPoint>& data) {
    if (data.empty()) return;

    double max_y = 0.0;
    double steady_state_y = data.back().state_y;
    double setpoint = data.back().setpoint;
    
    double rise_time = -1.0;
    double settling_time = -1.0;
    
    bool crossed_10 = false;
    double t_10 = 0.0;

    for (const auto& d : data) {
        if (d.state_y > max_y) max_y = d.state_y;
        
        // Rise time (10% to 90%)
        if (!crossed_10 && d.state_y >= 0.1 * setpoint) { crossed_10 = true; t_10 = d.t; }
        if (rise_time < 0 && d.state_y >= 0.9 * setpoint) { rise_time = d.t - t_10; }
    }

    // Settling time (2% band) backwards search
    double band = 0.02 * setpoint;
    for (auto it = data.rbegin(); it != data.rend(); ++it) {
        if (std::abs(it->state_y - setpoint) > band) {
            settling_time = it->t;
            break;
        }
    }

    double overshoot = ((max_y - setpoint) / setpoint) * 100.0;
    double ss_error = std::abs(setpoint - steady_state_y);

    std::cout << "\n=== Controller Performance Metrics ===\n";
    std::cout << "Overshoot:      " << (overshoot > 0 ? overshoot : 0) << " %\n";
    std::cout << "Rise Time:      " << (rise_time > 0 ? rise_time : 0) << " s\n";
    std::cout << "Settling Time:  " << settling_time << " s\n";
    std::cout << "Steady State Err: " << ss_error << "\n======================================\n";
}

}
}
