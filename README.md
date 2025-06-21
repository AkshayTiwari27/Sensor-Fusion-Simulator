# 🛰️ Embedded Sensor Fusion Simulator in C

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language">
  <img src="https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg" alt="Platform">
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License">
</p>

<p align="center">
  <i>A hardware-free C simulation demonstrating real-time sensor fusion of noisy accelerometer and gyroscope data using a Complementary Filter to achieve stable orientation estimation.</i>
</p>

---

## 🧠 Project Concept

In embedded systems like drones, robots, and smartphones, estimating orientation (e.g., tilt angle) is critical. However, real sensors have flaws:

- 📉 **Accelerometers** give stable long-term tilt but are highly noisy due to vibration.
- 🌀 **Gyroscopes** offer smooth short-term angle rate but suffer from drift over time.

This project simulates both, then applies a **Complementary Filter** to fuse them. The result? A **clean, smooth, and stable orientation angle**, as seen in real-world IMUs.

---

## ✨ Key Features

- 🔁 **Realistic Sensor Emulation**  
  - Accelerometer with random noise  
  - Gyroscope with bias and drift

- 🎛️ **Complementary Filter Logic**  
  - Tunable `alpha` parameter  
  - Combines long-term & short-term reliability

- ⏱️ **Real-Time Simulation**  
  - Discrete-time loop mimicking embedded systems

- 🖥️ **Color-Coded Console Output**  
  - Raw & fused angles printed in live terminal

- 📊 **CSV Logging**  
  - `log.csv` output for external analysis

- 🧩 **Modular C Codebase**  
  - Clean separation of logic, sensors, and logging

- 💻 **Hardware-Free Execution**  
  - No sensors, no MCU needed — runs on any PC

---
## 🧱 Architecture & Data Flow

This project implements a **complementary filter** to derive a stable and accurate angle estimation from simulated, imperfect sensor data. The data flows through the system in the following sequence:

<p align="center">
  <img src="images/Sensor Fusion System Flow Diagram.png" alt="Sensor Fusion Architecture Diagram" width="800"/>
  <br/>
  <em>Sensor Fusion System – Accelerometer and Gyroscope Fusion with Complementary Filter</em>
</p>

---
### 1. Sensor Simulation

The process begins with a simulated **Inertial Measurement Unit (IMU)** that generates two distinct sensor readings:

* **`accel_angle` (Noisy):**
  Angle derived from an accelerometer simulation. It reflects long-term orientation but is affected by short-term vibration and noise.

* **`gyro_rate` (Drifty):**
  Angular velocity from a simulated gyroscope. It captures short-term changes accurately but accumulates drift over time.

### 2. Complementary Filter

The **complementary filter** is the core logic that fuses both sensor inputs:

* 🌀 Uses **gyroscope** for short-term precision (ignores noise)
* 📉 Uses **accelerometer** for long-term correction (ignores drift)

It computes a **`fused_angle`**, balancing the reliability of both sensors using a tunable alpha coefficient.

### 3. Console Output & Logging

The final filtered angle is sent to two output destinations:

* **🖥️ Console Output:**
  Displays real-time sensor readings and fused angle, cycle by cycle.

* **📁 CSV Logging (`log.csv`):**
  Stores a structured log of every sensor cycle for later analysis or graph plotting in tools like Excel or Python.
---

### 📦 Modules

| File                  | Purpose                                           |
|-----------------------|---------------------------------------------------|
| `main.c`              | Main loop, time steps, integration                |
| `sensor_simulator.c/h`| Simulates accelerometer and gyroscope readings    |
| `complementary.c/h`   | Applies fusion formula with alpha tuning          |
| `logger.c/h`          | Terminal and CSV logging                          |
| `utils.h`             | Helper functions (delay, clamp, noise, etc.)      |
| `log.csv`             | Output file for graphing and analysis             |
| `Makefile`            | Automates compilation                            |

---

## 🚀 Getting Started

### 🔧 Prerequisites

- ✅ C Compiler (GCC/Clang/MinGW)
- ✅ `make` utility (optional, recommended)
- ✅ No external libraries required

### 📥 Installation & Execution

```bash
# Clone the repository
git clone https://github.com/AkshayTiwari27/Sensor-Fusion-Simulator.git
cd c-sensor-fusion-simulator

# Compile the project
make   # or use gcc manually

# Run the simulation
./sensor_fusion_sim
````

### 🧹 Cleanup

```bash
make clean
```

---

## 🧮 Complementary Filter Formula

```c
fused_angle = α * (previous_angle + gyro_rate * dt) + (1 - α) * accel_angle;
```

* `α` = Trust factor for gyroscope (e.g., 0.98)
* `dt` = Time interval between readings
* High `α` = smooth but may drift
* Low `α` = stable but reacts slowly

---

## 📈 Visualizing Results

The simulation generates a `log.csv` like this:

```csv
cycle,accel_angle,gyro_angle,fused_angle
1,2.4,0.0,2.3
2,1.9,0.5,2.0
...
```

### 📊 Plot with Python

```python
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("log.csv")

plt.plot(df['cycle'], df['accel_angle'], label='Accel (noisy)', color='gold')
plt.plot(df['cycle'], df['gyro_angle'], label='Gyro (drifty)', color='red')
plt.plot(df['cycle'], df['fused_angle'], label='Fused Angle', color='green', linewidth=2)

plt.title("Sensor Fusion: Complementary Filter")
plt.xlabel("Cycle")
plt.ylabel("Angle (degrees)")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
```

---

## 🧪 Skills Demonstrated

| Skill                    | Application                                   |
| ------------------------ | --------------------------------------------- |
| Embedded C Programming   | Modular `.c/.h` design, simulation loop       |
| Sensor Fusion Algorithms | Complementary filter implementation           |
| Signal Processing        | Handling noise, drift, and real-time feedback |
| Data Logging & Analysis  | CSV output and plot-based validation          |
| System Design Thinking   | Architecture mimicking embedded IMU logic     |
| Build System Proficiency | Clean use of `Makefile`, directory management |

---

## 💡 Optional Enhancements

| Enhancement          | Description                                             |
| -------------------- | ------------------------------------------------------- |
| ✅ Kalman Filter      | Add a Kalman filter as advanced comparison              |
| ✅ Terminal Graphing  | Use ASCII or ncurses to live plot angle in terminal     |
| ✅ Runtime Parameters | Allow CLI flags for `alpha`, noise levels, sim duration |
| ✅ Adaptive Alpha     | Adjust `alpha` based on motion intensity (variance)     |

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## Credits

👨‍💻 **Author**: Akshay Tiwari  
📧 **Email**: [tiwariakshay590@gmail.com](mailto:tiwariakshay590@gmail.com)  
🌐 **GitHub**: [https://github.com/AkshayTiwari27](https://github.com/AkshayTiwari27)  
🔗 **LinkedIn**: [https://www.linkedin.com/in/akshay-tiwari2709/](https://www.linkedin.com/in/akshay-tiwari2709/)  
