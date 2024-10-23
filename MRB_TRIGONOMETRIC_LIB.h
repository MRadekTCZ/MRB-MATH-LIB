/*
 * MRB_TRIG_LIB.h
 *
 *  Created on: Feb 17, 2024
 *      Author: Maciek
 */

#ifndef INC_MRB_TRIGONOMETRIC_LIB_H_
#define INC_MRB_TRIGONOMETRIC_LIB_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MRB_TL_PI 3.14159f
#define MRB_TL_PI_BY_2 1.57079f
#define MRB_TL_1_BY_2PI 0.15915f
#define MRB_TL_PI_BY_3 1.04719755f
#define MRB_TL_LUT_LENGTH 1000



float sin_f(float arg);
float cos_f(float arg);
float asin_f(float arg);

float fast_invsqrt(float number);
float fast_sqrt(float number);
#endif /* INC_MRB_TRIGONOMETRIC_LIB_H_ */
