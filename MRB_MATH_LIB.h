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
//For proper RMS calculation, you have to adjust 
#define MEASURING_FREQUENCY 10000
#define BASE_FREQ 50
#define BUFFER_SIZE 200 // (MEASURING_FREQUENCY / BASE_FREQ)
#define RMS_HANDLERS 6
//Buffer size has be counted manually before compilation, so there will be no need of using malloc()

// ***********SQRT******************************************//
// fast qrt accuracy is directly connected with number of cycles needed to count it
// increasing sqrt_accuracy by one effects linearly increasing execution time of fast_sqrt
#define SQRT_ACCURACY 2

// ***********SIN and COS***********************************//
//You can define lenght of look up table (in kB). The bigger the look up table, the more accurate sin_f and cos_f function are
#define LUTSIZE 1 //4*kB





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




//*************************************************************************
#if LUTSIZE == 2
#define LUT_LENGTH 2000   
#elif LUTSIZE == 4
#define LUT_LENGTH 4000 
#else  
#define LUT_LENGTH 1000
#endif



float sin_f(float arg);
float cos_f(float arg);


float fast_invsqrt(float number);
float fast_sqrt(float number);


float RMS(float signal_actual, unsigned int RMS_handler);
float fast_RMS(float signal_actual, unsigned int RMS_handler);
float rapid_RMS(float signal_actual, unsigned int RMS_handler);


#endif /* INC_MRB_TRIGONOMETRIC_LIB_H_ */
