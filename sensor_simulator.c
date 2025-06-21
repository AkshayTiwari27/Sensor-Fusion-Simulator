#include "sensor_simulator.h"
#include "utils.h"
#include <math.h> // For sin function

// --- Sensor Noise Parameters ---
#define ACCEL_NOISE_AMPLITUDE 2.0f // Max noise in degrees for the accelerometer
#define GYRO_NOISE_AMPLITUDE  0.5f // Max noise in degrees/sec for the gyroscope
#define GYRO_BIAS             0.1f // Constant drift (bias) for the gyroscope in degrees/sec

// Simulates accelerometer and gyroscope readings with realistic noise and drift
void simulate_sensors(SensorData *data, float true_angle, float dt) {
    // A simple, slow-changing "true" angle for the simulation (e.g., a sine wave)
    // This represents the actual physical orientation of the device
    float actual_angle = 30.0f * sin(get_current_time_s() * 0.5f);

    // 1. Simulate Accelerometer
    // The accelerometer gives a noisy but stable reading of the actual angle
    data->accel_angle = actual_angle + generate_noise(ACCEL_NOISE_AMPLITUDE);

    // 2. Simulate Gyroscope
    // The gyroscope measures the rate of change of the angle (angular velocity)
    // We get this by finding the change in angle since the last reading
    float gyro_true_rate = (actual_angle - true_angle) / dt;
    data->gyro_rate = gyro_true_rate + generate_noise(GYRO_NOISE_AMPLITUDE) + GYRO_BIAS;
}
