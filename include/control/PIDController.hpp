#pragma once
#include <algorithm>

namespace sim {
namespace control {

class PIDController {
private:
    double Kp, Ki, Kd;
    double out_min, out_max;
    double Tf; // Derivative filter time constant

    double integral_error;
    double prev_error;
    double prev_derivative;

public:
    PIDController(double kp, double ki, double kd, double min_out, double max_out, double filter_time_const);
    double compute(double setpoint, double measured_value, double dt);
    void reset();
};

}
}
