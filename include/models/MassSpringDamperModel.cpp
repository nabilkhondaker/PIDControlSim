#include "models/MassSpringDamperModel.hpp"

namespace sim {
namespace models {

MassSpringDamperModel::MassSpringDamperModel(double mass, double damping, double stiffness)
    : m(mass), c(damping), k(stiffness), pos(0.0), vel(0.0) {}

double MassSpringDamperModel::update(double control_input, double dt, double disturbance) {
    // Second order system: m*a + c*v + k*x = F
    double accel = ((control_input + disturbance) - c * vel - k * pos) / m;
    vel += accel * dt;
    pos += vel * dt;
    return pos;
}

void MassSpringDamperModel::reset() { pos = 0.0; vel = 0.0; }

}
}
