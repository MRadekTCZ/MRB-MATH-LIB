/*
 * RMSPQD.h
 *
 *  Created on: 21 okt. 2024
 *      Author: brzycki
 */

#ifndef DEVICE_RMSPQD_H_
#define DEVICE_RMSPQD_H_


#include <math.h>
#define one_by_sqrt3 0.5773502f
#define SQRT2 1.4142f
#define PI 3.1415926f
#define PI_BY_2 1.570796f
#define PI_BY_3 1.047197f
#define ONE_BY_SQRT2 0.70711f
#define PID_1_KP 50
#define PID_1_KI 500
#define PID_1_KD 0.0
#define SAMPLE_FREQ 10000
#define SAMPLE_PRERIOD 0.0001f
#define DIDT_SCALING_CONSTANT 0.00303030303f
#define BASE_FREQ 50
#define BASE_PERIOD 0.02 //RMS counted for 50Hz frequency with 1kHz measure rate
#define BUFFER_SIZE 200
#define DT 0.0001f
#define DT_RMS 0.0001f
#define ONE_BY_BUFFERSIZE 0.005f
#define FAST_RMS_COEF 1.1098901f
/******************************************
THREE PHASE FUNCTIONS
*******************************************/
struct Axis
{
float x;
float y;
};


struct ThreePhaseSystem
{
float phase_A;
float phase_B;
float phase_C;
};
typedef struct ThreePhaseSystem Three_phase_handler;
struct PID_unit
{
float KP;
float KI;
float KD;
float pid_integral;
float last_error;
};
typedef struct PID_unit PID_handler;


struct Axis AlfaBeta(float signal_a, float signal_b, float signal_c);
struct Axis DQ(float signal_alfa, float signal_beta, float angle);
float PID_Regulator(float error, PID_handler* pid);
float Integrator(float input_signal, float THRESHOLD_LOW, float THRESHOLD_HIGH, unsigned int handler);
struct ThreePhaseSystem PLL_3phase(float theta_main);
/******************************************
ONE PHASE FUNCTIONS
*******************************************/


struct PLL_1_PHASE_INTEGRAL
{
float moving_average_buffer[20];
float signal_integral_RMS_buffer[BUFFER_SIZE];
float signal_input_last;
float PLL_asin_last;
};
typedef struct PLL_1_PHASE_INTEGRAL PLL_1phase_Handler;


float RMS_PLL(float signal_actual, PLL_1phase_Handler* PLL_1phase );
float RMS(float signal_actual);
float PLL_1phase(float input_signal, float rms, PLL_1phase_Handler* PLL_1phase );
float fast_RMS(float signal_actual);

#endif /* DEVICE_RMSPQD_H_ */
