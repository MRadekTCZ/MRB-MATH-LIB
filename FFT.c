#include <stdio.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
// Define constants
#define PI 3.14159265358979323846
#define FFT_ACCURACY 10
#define MAX_SAMPLES (200*FFT_ACCURACY)// Maximum number of samples
#define MAX_FREQ_RANGE (8*FFT_ACCURACY) // Reduced frequency range for DFT

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
void compute_dft(float y, float* P1) {
    float real, imag;
    static float input_buffer[MAX_SAMPLES];
    static unsigned short int buffer_overflow;
    static int buffr_pointr;
    input_buffer[buffr_pointr] = y;
    buffr_pointr++;

    if (buffr_pointr == MAX_SAMPLES)
    {
        buffr_pointr = 0;
        for (int k = 0; k < MAX_FREQ_RANGE; k++) {
            real = 0;
            imag = 0;
            for (int n = 0; n < MAX_SAMPLES; n++) {
                float angle = -2.0 * PI * k * n / MAX_SAMPLES;
                real += input_buffer[n] * cosf(angle);
                imag += input_buffer[n] * sinf(angle);
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
        compute_dft(y, P1);
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

    return 0;
}
