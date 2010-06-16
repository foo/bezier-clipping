#pragma once

#include <math.h>

#define CBRT(X)		(((X) < 0.0) ? -pow(-(X), 1.0/3.0) : pow((X), 1.0/3.0))  
#define SQ(X)		((X) * (X))	/* square */
#define CB(X)		((X) * (X) * (X)) /* cube */

float min(float a, float b);
float max(float a, float b);
void swap(float* a, float* b);

float gammln(const float xx);
float factrl(const int n);
float factln(const int n);
int bico(const int n, const int k);
int up_power(const int x, const int up);
  
const float PI;
