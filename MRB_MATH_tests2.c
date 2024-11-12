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
void compare_sin(double step) {
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
        float sin_mine = sin_t(x); // Result from sin_f
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
        float cos_mine = cos_t(x); // Result from cos_f
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
    for (int i = 0; i < number_of_tests; i++) {
        x = values[i]* 19500.397;

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
        array[i] = amplitude * cos(theta);
        // array[i] = 1; // This line seems incorrect as it overwrites the calculated sine value
    }
}

void compare_RMS(float* array, int number_of_samples) {
    float rms_normal, rms_fast, rms_rapid;
    float current[3], voltage[3];
    float ADC1[200], ADC2[200], ADC3[200], ADC4[200], ADC5[200], ADC6[200];

    printf("   RMS    |  fast_RMS  |  rapid_RMS  | Difference \n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < number_of_samples; i++) {
        ADC1[i] = array[i];
        ADC2[i] = array[i];
        ADC3[i] = array[i];
        ADC4[i] = array[i];
        ADC5[i] = array[i];
        ADC6[i] = array[i];
        #define current_A 0
        #define current_B 1
        #define current_C 2
        #define voltage_A 3
        #define voltage_B 4
        #define voltage_C 5
        current[0] = rapid_RMS(ADC1[i], current_A);
        current[1] = rapid_RMS(ADC2[i], current_B);
        current[2] = rapid_RMS(ADC3[i], current_C);
        voltage[0] = rapid_RMS(ADC4[i], voltage_A);
        voltage[1] = rapid_RMS(ADC5[i], voltage_B);
        voltage[2] = rapid_RMS(ADC6[i], voltage_C);

        // Printing results for each value
        printf("  %10.9f | %10.9f | %10.9f  | %10.9f\n", current[0], current[1], current[2], voltage[0]);
    }
}
float generate_sine_wave(float f, float t) {
    float y;
    y = cos_f(2 * PI * f * t);
    y += 0.05 * sinf(2.0 * PI * (1.1 * f) * t);
    y += 0.05 * sinf(2.0 * PI * (1.2 * f) * t);
    y += 0.015 * sinf(2.0 * PI * (1.5 * f) * t);
    y += 0.05 * sinf(2.0 * PI * (1.6 * f) * t);
    y += 0.05 * sinf(2.0 * PI * (1.8 * f) * t);
    y += 0.02 * sinf(2.0 * PI * (2.0 * f) * t);
    y += 0.03 * sinf(2.0 * PI * (3.0 * f) * t);
    y += 0.05 * sinf(2.0 * PI * (5.0 * f) * t);
    y += 0.07 * sinf(2.0 * PI * (7.0 * f) * t);
    return y;
}

int main() {

    double step = 0.00001; // Set the step for x variables

    int number_of_samples = 200;
    float amplitude = 330.0;          // Amplitude of the sine wave
    float sine_array[200];            // Array to hold sine values
    compare_sin(step);
    //compare_cos(step);
    //compare_sqrt();
    //generate_sine(sine_array, number_of_samples, amplitude);

    //printf("Array of sine wave values:\n");
    //for (int i = 0; i < number_of_samples; i++) {
    //    printf("sine_array[%d] = %8.6f\n", i, sine_array[i]);
    //}

    //compare_RMS(sine_array, number_of_samples);
    // Define signal parameters
    float f = 50.0;  // Main frequency in Hz
    /*

    // Define fixed-size arrays for time and signal data
    float t;
    float y;
    float P1[DFT_BUFFER_SIZE / 2 + 1];
    float P2[DFT_BUFFER_SIZE / 2 + 1];

    for (int i = 0; i < 2 * DFT_BUFFER_SIZE; i++) {
        float t = i * (1.0f/SAMPLING_FREQ);
        float y = generate_sine_wave(f, t);
        //printf("%f\n", y);
        //float y2 = generate_sine_wave(2*f, t);
        DFT(y, P1, 0);
        //DFT(y2, P2, 1);
    }


    float main_frequency = f;
    printf("Main Frequency: %f Hz\n", main_frequency);
    printf("Amplitude of Main Frequency: %f\n", P1[1 * DFT_RESULUTION]);
    // Print all values in P1
    printf("\nP1 values:\n");
    for (int i = 0; i < MAX_FREQ_RANGE; i++) {
        printf("Frequency bin %d: Amplitude = %f\n", i, P1[i]);
    }
    
    printf("\n");

    


    // Write P1 values to a CSV file using fopen_s
    FILE* file;
    errno_t err = fopen_s(&file, "P1_values.csv", "w");
    if (err != 0 || file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Write header
    fprintf(file, "Frequency Bin,Amplitude\n");

    // Write values
    for (int i = 0; i < MAX_FREQ_RANGE; i++) {
        fprintf(file, "%d,%f\n", i, P1[i]);
    }

    fclose(file);
    printf("P1 values written to P2_values.csv\n");
    */
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
