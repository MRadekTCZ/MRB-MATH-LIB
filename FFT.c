#include <stdio.h>
#include <math.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS
// Define constants
#define PI 3.14159265358979323846
#define FFT_ACCURACY 1
#define MAX_SAMPLES ((unsigned int)(200*FFT_ACCURACY))// Maximum number of samples
#define MAX_FREQ_RANGE ((unsigned int)(8*FFT_ACCURACY)) // Reduced frequency range for DFT
#define FFT_HANDLERS 3

// Function to generate a sine wave with additional frequencies
float generate_sine_wave(float f, float t) {
    float y;
    y = sinf(2 * PI * f * t);
    y += 0.02 * sinf(2.0 * PI * (2.0 * f) * t);
    y += 0.03 * sinf(2.0 * PI * (3.0 * f) * t);
    y += 0.05 * sinf(2.0 * PI * (5.0 * f) * t);
    y += 0.07 * sinf(2.0 * PI * (7.0 * f) * t);
    return y;
}

// Function to compute the Discrete Fourier Transform (DFT)
void compute_dft(float y, float* P1, unsigned int FFT_Handler) {
    float real, imag;
    static float input_buffer[FFT_HANDLERS][MAX_SAMPLES];
    static unsigned short int buffer_overflow[FFT_HANDLERS];
    static int buffr_pointr[FFT_HANDLERS];
    input_buffer[FFT_Handler][buffr_pointr[FFT_Handler]] = y;
    buffr_pointr[FFT_Handler]++;

    if (buffr_pointr[FFT_Handler] == MAX_SAMPLES)
    {
        buffr_pointr[FFT_Handler] = 0;
        for (int k = 0; k < MAX_FREQ_RANGE; k++) {
            real = 0;
            imag = 0;
            for (int n = 0; n < MAX_SAMPLES; n++) {
                float angle = -2.0 * PI * k * n / MAX_SAMPLES;
                real += input_buffer[FFT_Handler][n] * cosf(angle);
                imag += input_buffer[FFT_Handler][n] * sinf(angle);
            }
            // Compute the magnitude of the DFT result
            P1[k] = 2.0 * sqrtf(real * real + imag * imag) / MAX_SAMPLES;
        }
    }
}

// Main function
int main() {
    // Define signal parameters
    float f = 50.0;  // Main frequency in Hz


    // Define fixed-size arrays for time and signal data
    float t;
    float y;
    float P1[MAX_SAMPLES / 2 + 1];



    for (int i = 0; i < 2*MAX_SAMPLES; i++) {
        float t = i * 0.0001;
        float y = generate_sine_wave(f, t);
        //printf("     %f     ", y);
        // Compute DFT
        compute_dft(y, P1, 1);
    }
    

    float main_frequency = 50.0;
    printf("Main Frequency: %f Hz\n", main_frequency);
    printf("Amplitude of Main Frequency: %f\n", P1[1*FFT_ACCURACY]);
    // Print all values in P1
    printf("\nP1 values:\n");
    for (int i = 0; i < MAX_FREQ_RANGE; i++) {
        printf("Frequency bin %d: Amplitude = %f\n", i, P1[i]);
    }
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
    printf("P1 values written to P1_values.csv\n");


    LARGE_INTEGER frequency;
    LARGE_INTEGER start, end;
    float times[2 * MAX_SAMPLES];  // Array to store cycle times in milliseconds
    // Get the high-resolution performance frequency
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 2 * MAX_SAMPLES; i++) {
        QueryPerformanceCounter(&start);  // Start time

        float t = i * 0.0001f;
        float y = generate_sine_wave(f, t);

        // Compute DFT
        compute_dft(y, P1, 1);

        QueryPerformanceCounter(&end);  // End time

        // Calculate the time taken in milliseconds
        times[i] = (float)(end.QuadPart - start.QuadPart) * 1000.0f / frequency.QuadPart;
    }

    // Print all cycle times
    for (int i = 0; i < 2 * MAX_SAMPLES; i++) {
        printf("Cycle %d: %f ms\n", i, times[i]);
    }

    return 0;
}
