#pragma once

#include <assert.h>
#include <math.h>

#include "interval.h"
#include "utils.h"

typedef struct
{
  int n; // degree
  float* c; // coefficients; size is n + 1
} Power;

Power* power_create(int deg);
void power_destroy(Power* p);
int power_analytic_roots(Power* p, float** roots);
