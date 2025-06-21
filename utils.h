#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h> // For rand()

// --- Platform-specific includes and functions for timing ---

// Check if the compiler is on a Windows system
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h> // Use the Windows API for timing

// Provides a high-resolution time in seconds using the Windows API
static inline float get_current_time_s() {
    static LARGE_INTEGER freq;
    // Get the frequency of the performance counter, only needs to be done once
    if (freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
    }
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now); // Get the current counter value
    return (float)now.QuadPart / (float)freq.QuadPart; // Return time in seconds
}

// A simple delay function using the Windows Sleep function
static inline void delay_ms(unsigned int milliseconds) {
    Sleep(milliseconds); // Sleep takes milliseconds
}

#else // Otherwise, assume a POSIX-compliant system (Linux, macOS)
#define _POSIX_C_SOURCE 199309L // Enable POSIX features
#include <time.h>   // For clock_gettime
#include <unistd.h> // For usleep

// Provides a high-resolution time in seconds using the POSIX API
static inline float get_current_time_s() {
    struct timespec ts;
    // Use CLOCK_MONOTONIC for a steadily increasing time
    clock_gettime(CLOCK_MONOTONIC, &ts); 
    return (float)ts.tv_sec + (float)ts.tv_nsec / 1e9f;
}

// A simple delay function using usleep
static inline void delay_ms(unsigned int milliseconds) {
    usleep(milliseconds * 1000); // usleep takes microseconds
}

#endif

// --- Generic Utility Functions ---

// Generates a random float value between -amplitude and +amplitude
static inline float generate_noise(float amplitude) {
    // `rand() / (RAND_MAX / 2.0f)` gives a float between 0.0 and 2.0
    // Subtracting 1.0 makes it range from -1.0 to 1.0
    return amplitude * ((rand() / (RAND_MAX / 2.0f)) - 1.0f);
}

#endif // UTILS_H
