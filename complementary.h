#ifndef COMPLEMENTARY_H
#define COMPLEMENTARY_H

#include "sensor_simulator.h" // Include for SensorData type

// Holds the state and configuration of the complementary filter
typedef struct {
    float alpha;        // The filter's tuning constant
    float fused_angle;  // The latest stable angle output from the filter
} FusionData;

// Initializes the fusion data structure with a given alpha and starting angle
void init_fusion_data(FusionData *data, float alpha, float starting_angle);

// Processes new sensor data through the filter to compute the next fused angle
void run_complementary_filter(FusionData *fusion, const SensorData *sensors, float dt);

#endif // COMPLEMENTARY_H
