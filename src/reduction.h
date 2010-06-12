#pragma once

#include "bezier.h"
#include "utils.h"

Bezier* bezier_degree_reduction(Bezier* c, int reduced_degree, float **reduction_matrix);
float** bezier_reduction_matrix(int n, int m);
