// MRB_MATH_tests.c : This file contains the 'main' function. Program execution begins and ends there.
#include "MRB_MATH_LIB.h"
#include <stdio.h>
#include <stdint.h> // For uint64_t type
#include <stdlib.h>
#include <math.h>
#include <time.h>   // For clock
// Function to measure clock cycles
uint64_t get_clock_cycles() {
    return __rdtsc(); // This is for Intel/AMD CPUs on Windows or compatible environments
}
void compare_sines(double step) {
    printf("   x        |   sin(x)   |  sin_f(x)  | Difference \n");
    printf("-------------------------------------------------\n");

    // Open a CSV file for writing
    FILE* file = fopen("sine_comparison.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    // Write the CSV header
    fprintf(file, "x,sin_x,sin_f_x,Difference\n");

    for (double x = -PI; x <= 3 * PI; x += step) {
        float sin_math = sin(x);  // Result from math.h
        float sin_mine = sin_f(x); // Result from sin_f
        float difference = fabs(sin_math - sin_mine);

        // Print to console
        printf("%10.6f | %10.6f | %10.6f | %10.6f\n", x, sin_math, sin_mine, difference);

        // Write to CSV file
        fprintf(file, "%10.6f,%10.6f,%10.6f,%10.6f\n", x, sin_math, sin_mine, difference);
    }

    // Close the file
    fclose(file);
}

void compare_cos(double step) {
    printf("   x        |   cos(x)   |  cos_f(x)  | Difference \n");
    printf("-------------------------------------------------\n");

    // Open a CSV file for writing
    FILE* file = fopen("cosine_comparison.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    // Write the CSV header
    fprintf(file, "x,cos_x,cos_f_x,Difference\n");

    for (double x = -PI; x <= 3 * PI; x += step) {
        float cos_math = cos(x);  // Result from math.h
        float cos_mine = cos_f(x); // Result from cos_f
        float difference = fabs(cos_math - cos_mine);

        // Print to console
        printf("%10.6f | %10.6f | %10.6f | %10.6f\n", x, cos_math, cos_mine, difference);

        // Write to CSV file
        fprintf(file, "%10.6f,%10.6f,%10.6f,%10.6f\n", x, cos_math, cos_mine, difference);
    }

    // Close the file
    fclose(file);
}

void compare_sqrt() {
    float values[] = { 1.234, 23.456, 56.789, 123.456, 234.567, 345.678, 456.789, 567.890, 678.901, 789.012, 890.123, 
        1000.234, 1234.567, 1500.789, 1750.890, 2000.123, 2500.456, 3000.789, 3500.123, 4000.456, 4500.789, 5000.012, 
        5500.345, 6000.678, 6500.890, 7000.123, 7500.456, 8000.789, 8500.123, 9000.456, 9500.789, 10000.000, 10500.123, 
        11000.456, 11500.789, 12000.012, 12500.345, 13000.678, 13500.890, 14000.123, 14500.456, 15000.789, 15500.012, 
        16000.345, 16500.678, 17000.890, 17500.123, 18000.456, 18500.789, 19000.012, 19500.345 };

    int number_of_tests = sizeof(values) / sizeof(values[0]);

    float x, sqrt_math, sqrt_fast, difference;

    // Open a CSV file for writing
    FILE* file = fopen("sqrt_comparison.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }

    // Write the CSV header
    fprintf(file, "x,sqrt_x,fast_sqrt_x,Difference\n");

    printf("   x         |   sqrt(x)   |  fast_sqrt(x)  | Difference \n");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < number_of_tests; i++) {
        x = values[i];

        sqrt_math = sqrt(x);
        sqrt_fast = fast_sqrt(x);
        difference = fabs(sqrt_math - sqrt_fast);

        // Print to console
        printf("%10.6f | %10.6f | %14.6f | %10.6f\n", x, sqrt_math, sqrt_fast, difference);

        // Write to CSV file
        fprintf(file, "%10.6f,%10.6f,%14.6f,%10.6f\n", x, sqrt_math, sqrt_fast, difference);
    }

    // Close the file
    fclose(file);
}

void generate_sine(float* array, int number_of_samples, float amplitude) {
    for (int i = 0; i < number_of_samples; i++) {
        float theta = (2.0 * PI * i) / number_of_samples;  // Calculate theta
        array[i] = amplitude * sin(theta);
        // array[i] = 1; // This line seems incorrect as it overwrites the calculated sine value
    }
}

void compare_RMS(float* array, int number_of_samples) {
    float rms_normal, rms_fast, rms_rapid;

    printf("   RMS    |  fast_RMS  |  rapid_RMS  | Difference \n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < number_of_samples; i++) {
        rms_normal = RMS(array[i]);
        rms_fast = fast_RMS(array[i]);
        rms_rapid = rapid_RMS(array[i]);

        // Printing results for each value
        printf("  %8.6f | %8.6f | %8.6f  | %8.6f\n", rms_normal, rms_fast, rms_rapid, fabs(rms_normal - rms_fast));
    }
}

int main() {

    double step = 0.001572*0.01; // Set the step for x variables

    int number_of_samples = 200;
    float amplitude = 330.0;          // Amplitude of the sine wave
    float sine_array[200];            // Array to hold sine values
    compare_sines(step);
    //compare_sqrt();
    //generate_sine(sine_array, number_of_samples, amplitude);

    //printf("Array of sine wave values:\n");
    //for (int i = 0; i < number_of_samples; i++) {
    //    printf("sine_array[%d] = %8.6f\n", i, sine_array[i]);
    //}

    //compare_RMS(sine_array, number_of_samples);


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file 
