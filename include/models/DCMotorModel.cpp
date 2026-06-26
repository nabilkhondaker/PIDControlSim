#include "models/DCMotorModel.hpp"

namespace sim {
namespace models {

DCMotorModel::DCMotorModel(double gain, double time_const) 
    : K(gain), tau(time_const), state_omega(0.0) {}

double DCMotorModel::update(double control_input, double dt, double disturbance) {
    // First order system: tau * d(omega)/dt + omega = K * V
    // Euler integration: omega_{k+1} = omega_k + dt * (K * V - omega_k) / tau
    double d_omega = (K * (control_input + disturbance) - state_omega) / tau;
    state_omega += d_omega * dt;
    return state_omega;
}

void DCMotorModel::reset() { state_omega = 0.0; }

}
}
