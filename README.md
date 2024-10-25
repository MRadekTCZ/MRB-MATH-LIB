This library is intended for use in lower-cost, slower microcontrollers not dedicated for mathematical calculations (e.g. ATmega/Arduino, ARM Cortex M0 and M4, ESP, Raspberry Pi pico) to speed up floating point operations. 
It can also be used in DSP to reduce cycle time, wherever cycle time is very critical, but the accuracy of calculations is not so critical. 
The MRB_MATH library will also significantly speed up the execution time of math calculations on microcontrollers without FPU or without hardware support for the default math.h library. 
An additional function not included in the math.h library is the function for calculating the RMS of a signal. This function is available in three variants: normal, fast and rapid. 
In summary, this library allows faster calculations at the expense of lower precision and higher memory usage.

The documentation describes the functions contained in the MRB_MATH library and compares them with their counterparts from the math.h library. 
Execution times and precision are compared. The results are summarized in graphs or tables. 
The possibility to parameterize each function is also described - the MRB_MATH library makes it possible to increase the precision of a function at the cost of additional cycles or FLASH/RAM memory usage.

Functions included in the library
•	sin_f(float x) 	sinus from argument  x
•	cos_f(float x)	cosinus from argument  x
•	fast_invsqrt(float x)       fast inverse root square from argument  x
•	fast_sqrt(float x)	        fast root square from argument  x
•	RMS(float x)	root mean square function (with normal sqrt function)
•	fast_RMS(float x)    fast root mean square function (with fast sqrt function)
•	rapid_RMS(float x)   rapid root mean square function (approach without sqrt)

Execution speed overview
Table 1 Comparison of function execution time in terms of cycles on STM32 microcontroller with Cortex M-7 core
Function	  <math.h>	  “MRB_MATH_LIB.h”
sinus	      762 cycles	    90 cycles
cosinus	    762 cycles	    92 cycles
sqrt	      674 cycles	    28 cycles
RMS	            -	          694 cycles
fast RMS	      -	          46 cycles
rapid RMS	      -	          13 cycles
FFT	-	

Library created by Maciej Brzycki ------ February 2024
