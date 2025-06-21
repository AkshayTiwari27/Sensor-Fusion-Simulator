#ifndef SENSOR_SIMULATOR_H
#define SENSOR_SIMULATOR_H

// Holds the raw data from our simulated sensors
typedef struct {
    float accel_angle; // Angle calculated from the accelerometer
    float gyro_rate;   // Angular velocity from the gyroscope
} SensorData;

// Function to simulate new readings from the accelerometer and gyroscope
void simulate_sensors(SensorData *data, float true_angle, float dt);

#endif // SENSOR_SIMULATOR_H
