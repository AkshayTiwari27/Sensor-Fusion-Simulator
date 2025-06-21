#include <stdio.h>
#include <unistd.h> // For usleep
#include "sensor_simulator.h"
#include "complementary.h"
#include "logger.h"
#include "utils.h"

// --- Simulation Parameters ---
#define SIMULATION_DURATION_S 10 // Duration of the simulation in seconds
#define LOOP_DELAY_MS 100        // Delay in each loop iteration in milliseconds
#define ALPHA 0.98               // Complementary filter tuning constant

int main() {
    // --- Initialization ---
    SensorData sensors; // Struct to hold sensor readings
    FusionData fusion;  // Struct to hold fusion algorithm data
    
    float dt = LOOP_DELAY_MS / 1000.0f; // Calculate time delta in seconds
    int total_cycles = (SIMULATION_DURATION_S * 1000) / LOOP_DELAY_MS; // Total simulation cycles

    // Initialize the fusion data structure
    init_fusion_data(&fusion, ALPHA, 0.0f); 

    // Initialize the logger and write the CSV header
    if (init_logger("log.csv") != 0) {
        fprintf(stderr, "Error: Could not open log file.\n");
        return 1; // Exit if the log file cannot be created
    }

    printf("Starting Sensor Fusion Simulation...\n");
    printf("Alpha: %.2f | Loop Delay: %dms | Duration: %ds\n\n", ALPHA, LOOP_DELAY_MS, SIMULATION_DURATION_S);

    // --- Main Simulation Loop ---
    for (int i = 0; i < total_cycles; i++) {
        // 1. Simulate new sensor readings
        simulate_sensors(&sensors, fusion.fused_angle, dt);

        // 2. Apply the complementary filter to get the fused angle
        run_complementary_filter(&fusion, &sensors, dt);

        // 3. Log the current state to the console and the CSV file
        log_to_console(i + 1, &sensors, &fusion);
        log_to_csv(i + 1, &sensors, &fusion);

        // 4. Wait for the next cycle
        delay_ms(LOOP_DELAY_MS);
    }

    // --- Cleanup ---
    close_logger(); // Close the CSV file handle
    printf("\nSimulation finished. Data logged to log.csv\n");

    return 0; // Successful execution
}
