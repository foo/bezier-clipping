#pragma once

#include <assert.h>
#include <math.h>

#include "interval.h"
#include "utils.h"

int power_linear_roots(float A, float B, float** roots);
int power_quad_roots(float A, float B, float C, float** roots);
int power_cubic_roots(float A, float B, float C, float D, float** roots);
