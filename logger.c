#include "logger.h"

// --- ANSI Color Codes for Beautified Terminal Output ---
#define COLOR_RESET   "\x1b[0m"
#define COLOR_GRAY    "\x1b[90m"
#define COLOR_YELLOW  "\x1b[33m" // For the noisy accelerometer
#define COLOR_CYAN    "\x1b[36m" // For the drifting gyroscope
#define COLOR_GREEN   "\x1b[32m" // For the stable, fused angle

// --- Global Variables ---
static FILE *log_file = NULL; // File pointer for the CSV log, static to this file

// Initialize the logger by opening the file and writing the header
int init_logger(const char *filename) {
    log_file = fopen(filename, "w"); // Open file in write mode
    if (log_file == NULL) {
        return -1; // Return error if file couldn't be opened
    }
    // Write the header row for the CSV file
    fprintf(log_file, "cycle,gyro_rate,accel_angle,fused_angle\n");
    return 0; // Success
}

// Close the file handle when done
void close_logger() {
    if (log_file != NULL) {
        fclose(log_file); // Close the file
    }
}

// Log data to the standard terminal output with colors and clean formatting
void log_to_console(int cycle, const SensorData *sensors, const FusionData *fusion) {
    // Print with color codes for better readability and use "deg" instead of the ° symbol
    printf(COLOR_GRAY "[Cycle %03d] " COLOR_RESET
           "Accel: " COLOR_YELLOW "%6.2f deg" COLOR_RESET " | "
           "Gyro: "  COLOR_CYAN   "%6.2f deg/s" COLOR_RESET " | "
           "Fused: " COLOR_GREEN  "%6.2f deg" COLOR_RESET "\n",
           cycle,
           sensors->accel_angle,
           sensors->gyro_rate,
           fusion->fused_angle);
}

// Log data to the CSV file
void log_to_csv(int cycle, const SensorData *sensors, const FusionData *fusion) {
    if (log_file != NULL) {
        fprintf(log_file, "%d,%.4f,%.4f,%.4f\n",
                cycle,
                sensors->gyro_rate,
                sensors->accel_angle,
                fusion->fused_angle);
    }
}
