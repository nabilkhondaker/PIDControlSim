#pragma once
#include "IPlantModel.hpp"

namespace sim {
namespace models {

class DCMotorModel : public IPlantModel {
private:
    double K;   // Motor gain
    double tau; // Time constant
    double state_omega; // Angular velocity

public:
    DCMotorModel(double gain, double time_const);
    double update(double control_input, double dt, double disturbance) override;
    void reset() override;
};

}
}
