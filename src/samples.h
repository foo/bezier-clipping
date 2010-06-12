#pragma once

#include "bezier.h"
#include <math.h>

Bezier* sample_bezier_sinus(int degree, float freq);
Bezier* sample_bezier_cosinus(int degree, float freq);
Bezier* sample_bezier_parabola();

