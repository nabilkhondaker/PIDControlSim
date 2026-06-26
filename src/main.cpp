#include <iostream>
#include <memory>
#include "models/DCMotorModel.hpp"
#include "models/MassSpringDamperModel.hpp"
#include "control/PIDController.hpp"
#include "utils/Logger.hpp"
#include "utils/MetricsCalculator.hpp"
#include "utils/ConfigParser.hpp"

using namespace sim;

int main() {
    std::cout << "Initializing Real-Time PID Simulation Engine...\n";
    
    try {
        // Initialize the new, decoupled ConfigParser
        utils::ConfigParser conf("config/sim_config.ini");

        // Simulation Params
        double dt = conf.getDouble("Simulation_dt");
        double duration = conf.getDouble("Simulation_duration");
        double setpoint = conf.getDouble("Simulation_setpoint");
        double dist_time = conf.getDouble("Simulation_disturbance_time");
        double dist_val = conf.getDouble("Simulation_disturbance_val");

        // PID Init
        control::PIDController pid(
            conf.getDouble("PID_kp"), conf.getDouble("PID_ki"), conf.getDouble("PID_kd"),
            conf.getDouble("PID_output_min"), conf.getDouble("PID_output_max"),
            conf.getDouble("PID_derivative_filter_time_const")
        );

        // Plant Polymorphism
        std::unique_ptr<models::IPlantModel> plant;
        std::string plant_type = conf.getString("Plant_type");
        
        if (plant_type == "DCMotor") {
            plant = std::make_unique<models::DCMotorModel>(
                conf.getDouble("Plant_dc_k"), conf.getDouble("Plant_dc_tau")
            );
        } else {
            plant = std::make_unique<models::MassSpringDamperModel>(
                conf.getDouble("Plant_msd_m"), conf.getDouble("Plant_msd_c"), conf.getDouble("Plant_msd_k")
            );
        }

        utils::Logger logger;
        double current_time = 0.0;
        double y = 0.0; // Initial state

        std::cout << "Running Simulation [Plant: " << plant_type << ", Duration: " << duration << "s]\n";

        // Fixed-timestep simulation loop
        while (current_time <= duration) {
            double error = setpoint - y;
            double u = pid.compute(setpoint, y, dt);
            
            // Inject Disturbance
            double current_dist = (current_time >= dist_time) ? dist_val : 0.0;
            
            // Update Plant
            y = plant->update(u, dt, current_dist);
            
            logger.log(current_time, setpoint, error, u, y);
            current_time += dt;
        }

        logger.saveToCSV("simulation_results.csv");
        std::cout << "Simulation complete. Data written to 'simulation_results.csv'.\n";

        utils::MetricsCalculator::report(logger.getData());

    } catch (const std::exception& e) {
        std::cerr << "\n[SIMULATION ABORTED] " << e.what() << "\n";
        return 1;
    }

    return 0;
}
