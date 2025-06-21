#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include "sensor_simulator.h"
#include "complementary.h"

// Opens the log file and writes the CSV header
int init_logger(const char *filename);

// Closes the log file
void close_logger();

// Prints the current simulation state to the console
void log_to_console(int cycle, const SensorData *sensors, const FusionData *fusion);

// Writes the current simulation state as a new row in the CSV file
void log_to_csv(int cycle, const SensorData *sensors, const FusionData *fusion);

#endif // LOGGER_H
