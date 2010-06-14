#pragma once

#include <assert.h>

#include "interval.h"

int power_linear_roots(Interval* b, float A, float B, float** roots);
int power_quad_roots(Interval* b, float A, float B, float C, float** roots);
int power_cubic_roots(Interval* b, float A, float B, float C, float D, float** roots);
