# PIDControlSim

**Interactive PID controller simulator for robotic and motor control systems with real-time response visualization.**

---

<details>
<summary><b>Contents</b></summary>

- [🚀 Engineering Overview](#-engineering-overview)
- [✨ Key Features](#-key-features)
- [📁 Project Structure](#-project-structure)
- [🛠️ Tech Stack](#️-tech-stack)
- [⚙️ Quick Start](#️-quick-start)
  - [1. Prerequisites](#prerequisites)
  - [2. Build & Run](#build--run)
  - [3. Basic Usage Example](#basic-usage-example)
- [📊 Simulation Capabilities](#-simulation-capabilities)
- [🎯 Use Cases](#-use-cases)
- [📋 Roadmap](#-roadmap)
- [👤 Author](#-author)

</details>

## 🚀 Engineering Overview

**PIDControlSim** is a high-performance C++ simulation environment designed to model, tune, and visualize **Proportional-Integral-Derivative (PID)** controllers in real-time. Built for educational and prototyping purposes in mechatronics, robotics, and control systems engineering, it allows users to experiment with different plant models (DC motors, robotic joints, etc.), tune PID gains on the fly, and observe system responses including step responses, error tracking, and stability characteristics.

Whether you're learning classical control theory or prototyping real-world actuator behavior, PIDControlSim bridges theory and practice with interactive visualization and modular architecture.

---

## ✨ Key Features

* **Real-Time PID Tuning:** Adjust Kp, Ki, Kd gains interactively and see immediate effects on system behavior.
* **Multiple Plant Models:** Pre-built models including DC motors, second-order systems, and customizable transfer functions.
* **Response Visualization:** Live plotting of reference signals, system output, error, control effort, and phase portraits.
* **Simulation Modes:** Step response, ramp, sinusoidal tracking, and disturbance rejection testing.
* **Performance Metrics:** Automatic calculation of rise time, settling time, overshoot, steady-state error, and stability margins.
* **C++ Core with Scripting Support:** High-performance simulation engine with Python bindings for rapid experimentation.
* **Modular Architecture:** Easily extend with new controllers, plants, or visualization tools.

---

## 📁 Project Structure

```
PIDControlSim/
├── CMakeLists.txt
├── config/
│   └── sim_config.ini
├── include/
│   ├── control/
│   │   └── PIDController.hpp
│   ├── models/
│   │   ├── IPlantModel.hpp
│   │   ├── DCMotorModel.hpp
│   │   └── MassSpringDamperModel.hpp
│   └── utils/
│       ├── Logger.hpp
│       ├── MetricsCalculator.hpp
│       └── ConfigParser.hpp
├── src/
│   ├── main.cpp
│   ├── control/
│   │   └── PIDController.cpp
│   ├── models/
│   │   ├── DCMotorModel.cpp
│   │   └── MassSpringDamperModel.cpp
│   └── utils/
│       ├── Logger.cpp
│       ├── MetricsCalculator.cpp
│       └── ConfigParser.cpp
└── scripts/
    └── plot_results.py
```

---

## 🛠️ Tech Stack

* **Core Language:** C++ (modern C++20/23)
* **Build System:** CMake
* **Visualization:** Custom plotting (potentially integrated with matplotlib via Python or custom renderers)
* **Scripting:** Python bindings for analysis and automation
* **Mathematics:** Eigen-style linear algebra or custom vector/matrix utilities
* **Simulation:** Discrete-time integration with configurable time steps

---

## ⚙️ Quick Start

### 1. Prerequisites
- CMake (>= 3.10)
- C++ compiler with C++20 support (GCC/Clang/MSVC)
- (Optional) Python 3.x for scripting extensions

### 2. Build & Run

```bash
git clone https://github.com/nabilkhondaker/PIDControlSim.git
cd PIDControlSim

mkdir build && cd build
cmake ..
make

# Run the simulator
./PIDControlSim
```

### 3. Basic Usage Example

```cpp
// Example in main.cpp or your test script
PIDController pid(2.0, 0.5, 0.1);  // Kp, Ki, Kd
MotorModel motor(1.0, 0.5, 0.1);   // Example DC motor parameters

double dt = 0.01;
for (double t = 0; t < 10; t += dt) {
    double setpoint = (t < 2) ? 0 : 1.0;
    double output = motor.update(pid.compute(setpoint - motor.getPosition(), dt), dt);
    // Visualize or log results
}
```
---

## 📊 Simulation Capabilities

- **Controller Variants:** Standard PID, PI, PD, with anti-windup and derivative filtering.
- **Plant Dynamics:** First and second-order systems, with support for nonlinearities and noise.
- **Analysis Tools:** Bode plots, root locus (planned), Nyquist criteria insights.
- **Export Options:** CSV data logs, PNG/SVG response graphs.

---

## 🎯 Use Cases

- Learning PID tuning principles
- Prototyping robotic arm joint controllers
- Motor speed/position control simulation
- Control systems education and demonstrations
- Quick validation before hardware deployment

---

## 📋 Roadmap

- GUI interface (Dear ImGui or similar)
- More advanced plant models (inverted pendulum, quadrotor dynamics)
- System identification tools
- Hardware-in-the-loop (HIL) support
- WebAssembly export for browser-based demos

--- 

## 👤 Author
*Engineered by Nabil Khondaker*

