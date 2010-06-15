#pragma once

#include <GL/glut.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "power.h"
#include "interval.h"

typedef struct
{
  int n; // degree
  float* c; // coefficients; size is n + 1
  Interval* dom;
} Bezier;

Bezier* bezier_create(int N);
Bezier* bezier_create_with_coeffs(int N, float* coeffs);
Bezier* bezier_copy(Bezier* b);
void bezier_destroy(Bezier* b);
void bezier_degree_raise(Bezier* b, int n);
float bezier_max_coeff_diff(Bezier* b1, Bezier* b2);
int bezier_analytic_roots(Bezier* b, float** roots);
void bezier_inc_coeffs(Bezier* b, float ratio);
Power* bezier_to_power(Bezier* b);
