#pragma once
/*
 * MRB_MATH_LIB.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Maciek
 */

#ifndef INC_MRB_MATH_LIB_H_
#define INC_MRB_MATH_LIB_H_

#include <stdlib.h>
#include <stdio.h>

//***********ADJUSTABLE PARAMETERS**************************//

// ***********RMS*******************************************//
//For proper RMS calculation, you have to adjust these parameters
#define RMS_HANDLERS 6
#define MEASURING_FREQUENCY 10000
#define BASE_FREQ 50
#define BUFFER_SIZE 200 // (MEASURING_FREQUENCY / BASE_FREQ)
//Buffer size has be counted manually before compilation, so there will be no need of using malloc()

// ***********SQRT******************************************//
// fast qrt accuracy is directly connected with number of cycles needed to count it
// increasing sqrt_accuracy by one effects linearly increasing execution time of fast_sqrt
#define SQRT_ACCURACY 3

// ***********SIN and COS***********************************//
//You can define lenght of look up table (in kB). The bigger the look up table, the more accurate sin_f and cos_f function are
#define LUTSIZE 0 //4*kB

// ***********DISCRETE FOURIER TRANSFORM********************//
//For proper DFT calculation, you have to adjust these parameters
#define DFT_HANDLERS 1
#define SAMPLING_FREQ 10000
#define DFT_BASE_FREQ 50
#define MAX_HARMONIC 8
#define DFT_RESULUTION 10
//#define NO_FPU
//*******don't change anything from here*************************//
//*******don't change anything from here*************************//
//*******don't change anything from here*************************//
// 
// 
// 
// 
// Mathematical constants with improved accuracy
#define ONE_BY_SQRT3 0.5773502691896257f // 1 / sqrt(3)
#define ONE_BY_SQRT2 0.7071067811865476f // 1 / sqrt(2)
#define SQRT2 1.4142135623730951f         // sqrt(2)
#define PI 3.14159265358979323846f        // Pi
#define PI_BY_2 1.57079632679489661923f   // Pi / 2
#define PI_BY_3 1.04719755119659774615f   // Pi / 3
#define ONE_BY_2PI 0.15915494309189533576f // 1 / (2 * Pi)

#define FAST_RMS_COEF 1.1098901f

#define DFT_BUFFER_SIZE ((unsigned int)((SAMPLING_FREQ*DFT_RESULUTION)/DFT_BASE_FREQ))// Maximum number of samples
#define MAX_FREQ_RANGE ((unsigned int)(MAX_HARMONIC*DFT_RESULUTION)) // Reduced frequency range for DFT


//*************************************************************************
#if LUTSIZE == 1
#define LUT_LENGTH 1000 
#elif LUTSIZE == 2
#define LUT_LENGTH 2000   
#elif LUTSIZE == 4
#define LUT_LENGTH 4000 
#else  
#define LUT_LENGTH 2 
#define NO_LUT
#endif

#define F3 0.166666666
#define F5 0.05
#define F7 0.023809523
#define F9 0.013888888

float sin_f(float arg);
float cos_f(float arg);

float sin_t(float arg);
float cos_t(float arg);

float fast_invsqrt(float number);
float fast_sqrt(float number);

float RMS(float signal_actual, unsigned int RMS_handler);
float fast_RMS(float signal_actual, unsigned int RMS_handler);
float rapid_RMS(float signal_actual, unsigned int RMS_handler);

void DFT(float y, float* P1, unsigned int DFT_Handler);

#endif /* INC_MRB_TRIGONOMETRIC_LIB_H_ */
