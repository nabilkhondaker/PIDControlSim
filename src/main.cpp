#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <memory>
#include "models/DCMotorModel.hpp"
#include "models/MassSpringDamperModel.hpp"
#include "control/PIDController.hpp"
#include "utils/Logger.hpp"
#include "utils/MetricsCalculator.hpp"

using namespace sim;

// Ultra-lightweight INI parser for the simulation
std::map<std::string, std::string> parseConfig(const std::string& filename) {
    std::map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line, section;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#' || line[0] == ';') continue;
        if (line[0] == '[') { section = line.substr(1, line.find(']') - 1) + "_"; continue; }
        auto delim = line.find('=');
        if (delim != std::string::npos) {
            config[section + line.substr(0, delim)] = line.substr(delim + 1);
        }
    }
    return config;
}

int main() {
    std::cout << "Initializing Real-Time PID Simulation Engine...\n";
    auto conf = parseConfig("config/sim_config.ini");

    // Simulation Params
    double dt = std::stod(conf["Simulation_dt"]);
    double duration = std::stod(conf["Simulation_duration"]);
    double setpoint = std::stod(conf["Simulation_setpoint"]);
    double dist_time = std::stod(conf["Simulation_disturbance_time"]);
    double dist_val = std::stod(conf["Simulation_disturbance_val"]);

    // PID Init
    control::PIDController pid(
        std::stod(conf["PID_kp"]), std::stod(conf["PID_ki"]), std::stod(conf["PID_kd"]),
        std::stod(conf["PID_output_min"]), std::stod(conf["PID_output_max"]),
        std::stod(conf["PID_derivative_filter_time_const"])
    );

    // Plant Polymorphism
    std::unique_ptr<models::IPlantModel> plant;
    if (conf["Plant_type"] == "DCMotor") {
        plant = std::make_unique<models::DCMotorModel>(
            std::stod(conf["Plant_dc_k"]), std::stod(conf["Plant_dc_tau"]));
    } else {
        plant = std::make_unique<models::MassSpringDamperModel>(
            std::stod(conf["Plant_msd_m"]), std::stod(conf["Plant_msd_c"]), std::stod(conf["Plant_msd_k"]));
    }

    utils::Logger logger;
    double current_time = 0.0;
    double y = 0.0; // Initial state

    std::cout << "Running Simulation [Plant: " << conf["Plant_type"] << ", Duration: " << duration << "s]\n";

    // Fixed-timestep simulation loop
    while (current_time <= duration) {
        // 1. Calculate Error
        double error = setpoint - y;

        // 2. Compute PID Control
        double u = pid.compute(setpoint, y, dt);

        // 3. Inject Disturbance (Load change simulation)
        double current_dist = (current_time >= dist_time) ? dist_val : 0.0;

        // 4. Update Plant Model
        y = plant->update(u, dt, current_dist);

        // 5. Log state
        logger.log(current_time, setpoint, error, u, y);

        // 6. Advance Time
        current_time += dt;
    }

    logger.saveToCSV("simulation_results.csv");
    std::cout << "Simulation complete. Data written to 'simulation_results.csv'.\n";

    utils::MetricsCalculator::report(logger.getData());

    return 0;
}
