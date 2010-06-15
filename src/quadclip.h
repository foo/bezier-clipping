#pragma once

#include "bezier.h"
#include "interval.h"
#include "casteljau.h"
#include "reduction.h"

int bezier_roots(Bezier* b, float** roots, float eps, int reduce);
int bezier_intervals_between(Bezier* up, Bezier* down, Interval*** intervals);

