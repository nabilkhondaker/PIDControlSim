#pragma once
#include "IPlantModel.hpp"

namespace sim {
namespace models {

class MassSpringDamperModel : public IPlantModel {
private:
    double m, c, k;
    double pos, vel;

public:
    MassSpringDamperModel(double mass, double damping, double stiffness);
    double update(double control_input, double dt, double disturbance) override;
    void reset() override;
};

}
}
