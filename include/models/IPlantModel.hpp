#pragma once

namespace sim {
namespace models {

class IPlantModel {
public:
    virtual ~IPlantModel() = default;
    // Returns the new state (output) given control input and timestep
    virtual double update(double control_input, double dt, double disturbance) = 0;
    virtual void reset() = 0;
};

} // namespace models
} // namespace sim
