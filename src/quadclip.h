#pragma once

#include "bezier.h"
#include "interval.h"
#include "casteljau.h"
#include "reduction.h"

int bezier_quadclip(Bezier* b, float** roots, float eps);
int bezier_quad_intervals_between(Bezier* up, Bezier* down, Interval*** intervals);
int bezier_quad_above(Bezier* b, Interval*** intervals);

