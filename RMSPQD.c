/*
 * RMSPQD.c
 *
 *  Created on: 21 okt. 2024
 *      Author: brzycki
 */

/*
 * MRB_PLL.c
 *
 *  Created on: 23 lut 2024
 *      Author: Maciek
 */

#include <stdio.h>
#include "RMSPQD.h"
#include "MRB_TRIGONOMETRIC_LIB.h"
/******************************************
THREE PHASE FUNCTIONS
*******************************************/

struct Axis AlfaBeta(float signal_a, float signal_b, float signal_c)
{
    struct Axis AB;
    AB.x = 0.33333*(2*signal_a - signal_b - signal_c);
    AB.y = one_by_sqrt3*(signal_b - signal_c);
    return AB;
}

struct Axis DQ(float signal_alfa, float signal_beta, float angle)
{
    struct Axis DQ;
    DQ.x = 0;
    DQ.y = 0;
    //if(angle >= 0 && angle <= 2*PI)
    //{
    DQ.x = signal_alfa*cos_f(angle) + signal_beta*sin_f(angle);
    DQ.y = -signal_alfa*sin_f(angle) + signal_beta*cos_f(angle);
    //}
    return DQ;
}

float PID_Regulator(float error, PID_handler* pid)
{
    float deficiency;
    float pid_derivative;

    pid->pid_integral = pid->pid_integral + pid->KI*SAMPLE_PRERIOD*error;
    pid_derivative = (error - pid->last_error )*pid->KD*SAMPLE_FREQ;

    deficiency = error*pid->KP + pid->pid_integral + pid_derivative;
    pid->last_error = error;
    return deficiency;
}

float Integrator(float input_signal, float THRESHOLD_LOW, float THRESHOLD_HIGH, unsigned int handler)
{
    static float integrated_s[16];
    if( (integrated_s[handler] < THRESHOLD_HIGH) && (integrated_s[handler] > THRESHOLD_LOW) )
    {
    integrated_s[handler] = integrated_s[handler] + input_signal*SAMPLE_PRERIOD;
    }
    else integrated_s[handler] = 0;

    return integrated_s[handler];
}

struct ThreePhaseSystem PLL_3phase(float theta_main)
{
    struct ThreePhaseSystem PLL_three_phase;
    PLL_three_phase.phase_A = theta_main;
    PLL_three_phase.phase_B = theta_main + 4*PI_BY_3;
    PLL_three_phase.phase_C = theta_main + 2*PI_BY_3;
    if(PLL_three_phase.phase_B > 2*PI) PLL_three_phase.phase_B = PLL_three_phase.phase_B - 2*PI;
    if(PLL_three_phase.phase_C > 2*PI) PLL_three_phase.phase_C = PLL_three_phase.phase_C - 2*PI;

    return PLL_three_phase;
}
/******************************************
ONE PHASE FUNCTIONS
*******************************************/
float RMS_PLL(float signal_actual, PLL_1phase_Handler* PLL_1phase )
{
    float rms;
    float signal_x2;
    float signal_integral;
    float one_by_rms;

    signal_x2 = signal_actual*signal_actual;
    signal_x2 = signal_x2*DT_RMS;
    signal_integral = 0;
    int i =0;
    for(i=0; i<BUFFER_SIZE-1;i++)
    {
    PLL_1phase->signal_integral_RMS_buffer[i] = PLL_1phase->signal_integral_RMS_buffer[i+1];
    signal_integral = signal_integral + PLL_1phase->signal_integral_RMS_buffer[i];
    }
    PLL_1phase->signal_integral_RMS_buffer[BUFFER_SIZE-1] = signal_x2;
    signal_integral = signal_integral + signal_x2;
    rms = sqrt(BASE_FREQ*signal_integral);
    //1 by rms is counted here, because RMS is counted less frequently than PLL.
    //That makes dividing occur 10 times less frequently, what drastically increase efficiency
    if(rms != 0) one_by_rms = 1/rms;
    else one_by_rms = 0;
    //return rms;
    return one_by_rms;
}

float RMS(float signal_actual)
{
    float rms;
    float signal_x2;
    float signal_integral;
    static float rms_buffer[BUFFER_SIZE];
    signal_x2 = signal_actual*signal_actual;
    signal_integral = 0;
    int i =0;
    for(i=0; i<BUFFER_SIZE-1;i++)
    {
    rms_buffer[i] = rms_buffer[i+1];
    signal_integral = signal_integral + rms_buffer[i];
    }
    rms_buffer[BUFFER_SIZE-1] = signal_x2;
    signal_integral = signal_integral + signal_x2;
    rms = fast_sqrt(ONE_BY_BUFFERSIZE*signal_integral);
    //return rms;
    return rms;
}

float fast_RMS(float signal_actual)
{
    float rms;
    float signal_fabs;
    float signal_integral;
    static float rms_buffer[BUFFER_SIZE];
    if(signal_actual >= 0) signal_fabs = signal_actual*ONE_BY_BUFFERSIZE;
    else signal_fabs = -signal_actual*ONE_BY_BUFFERSIZE;
    signal_integral = 0;
    int i =0;
    for(i=0; i<BUFFER_SIZE-1;i++)
    {
    rms_buffer[i] = rms_buffer[i+1];
    signal_integral = signal_integral + rms_buffer[i];
    }
    rms_buffer[BUFFER_SIZE-1] = signal_fabs;
    signal_integral = signal_integral + signal_fabs;

    //return rms;
    return signal_integral*FAST_RMS_COEF;
}

