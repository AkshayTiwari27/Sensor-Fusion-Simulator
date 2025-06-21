#include "complementary.h"

// Initialize the filter's state
void init_fusion_data(FusionData *data, float alpha_val, float starting_angle) {
    data->alpha = alpha_val;         // Set the alpha value
    data->fused_angle = starting_angle; // Set the initial angle
}

// Applies the complementary filter algorithm
void run_complementary_filter(FusionData *fusion, const SensorData *sensors, float dt) {
    // Gyro part: Integrate the gyro rate to get the change in angle
    // This is trusted for short-term changes
    float gyro_angle = fusion->fused_angle + sensors->gyro_rate * dt;

    // Accel part: The raw, noisy angle from the accelerometer
    // This is trusted for long-term stability
    float accel_angle = sensors->accel_angle;

    // Complementary filter formula
    // A weighted average combining the stable but noisy accelerometer and the responsive but drifting gyroscope
    fusion->fused_angle = fusion->alpha * gyro_angle + (1.0f - fusion->alpha) * accel_angle;
}
