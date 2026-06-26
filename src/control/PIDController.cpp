#include "control/PIDController.hpp"

namespace sim {
namespace control {

PIDController::PIDController(double kp, double ki, double kd, double min_out, double max_out, double filter_tc)
    : Kp(kp), Ki(ki), Kd(kd), out_min(min_out), out_max(max_out), Tf(filter_tc),
      integral_error(0.0), prev_error(0.0), prev_derivative(0.0) {}

double PIDController::compute(double setpoint, double measured_value, double dt) {
    double error = setpoint - measured_value;

    // Proportional
    double P_out = Kp * error;

    // Derivative with low-pass filter
    // D_k = (Tf * D_{k-1} + Kd * (e_k - e_{k-1})) / (Tf + dt)
    double D_out = 0.0;
    if (dt > 0.0) {
        D_out = (Tf * prev_derivative + Kd * (error - prev_error)) / (Tf + dt);
    }
    
    // Preliminary Output (to check for saturation)
    double u_pre = P_out + (Ki * integral_error * dt) + D_out;

    // Anti-windup (Clamping approach)
    if (u_pre > out_max) {
        if (error < 0) integral_error += error * dt; 
    } else if (u_pre < out_min) {
        if (error > 0) integral_error += error * dt;
    } else {
        integral_error += error * dt;
    }

    // Integral
    double I_out = Ki * integral_error;

    // Final Output Output calculation
    double output = P_out + I_out + D_out;

    // Saturation
    output = std::clamp(output, out_min, out_max);

    // State update
    prev_error = error;
    prev_derivative = D_out;

    return output;
}

void PIDController::reset() {
    integral_error = 0.0;
    prev_error = 0.0;
    prev_derivative = 0.0;
}

}
}
