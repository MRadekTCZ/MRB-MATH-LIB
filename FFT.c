#include <stdio.h>
#include <math.h>

// Define constants
#define PI 3.14159265358979323846
#define FFT_ACCURACY 1
#define MAX_SAMPLES 200*FFT_ACCURACY  // Maximum number of samples
#define MAX_FREQ_RANGE 8*FFT_ACCURACY // Reduced frequency range for DFT

// Function to generate a sine wave with additional frequencies
float generate_sine_wave(float f, float t) {
    float y;
    y = sin(2 * PI * f * t);
    y += 0.02 * sin(2.0 * PI * (2.0 * f) * t);
    y += 0.02 * sin(2.0 * PI * (5.0 * f) * t);
    y += 0.05 * sin(2.0 * PI * (7.0 * f) * t);
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
                real += input_buffer[n] * cos(angle);
                imag += input_buffer[n] * sin(angle);
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
    float T = 1.0 / f;  // Signal period
    int sampling_rate = 200 * f;  // Sampling rate in Hz

    // Define fixed-size arrays for time and signal data
    float t;
    float y;
    float P1[MAX_SAMPLES / 2 + 1];



    for (int i = 0; i < 202.5*MAX_SAMPLES; i++) {
        float t = i * 0.0001;
        float y = generate_sine_wave(f, t);

        // Compute DFT
        compute_dft(y, P1);
    }
    

    float main_frequency = 50.0;
    printf("Main Frequency: %f Hz\n", main_frequency);
    printf("Amplitude of Main Frequency: %f\n", P1[1]);
    // Print all values in P1
    printf("\nP1 values:\n");
    for (int i = 0; i < MAX_FREQ_RANGE; i++) {
        printf("Frequency bin %d: Amplitude = %f\n", i, P1[i]);
    }
    return 0;
}
