#pragma once

#include <malloc.h>
#include <assert.h>
#include "utils.h"
#include "interval.h"

typedef struct
{
  float a, b;
} Interval;

Interval* interval_create(float a, float b);
Interval* interval_copy(Interval* i);
Interval* interval_intersection(Interval* i, Interval* j);
int interval_difference(Interval* i, Interval* j, Interval*** intervals);
int interval_empty(Interval* i);
int interval_subinterval(Interval* i, Interval* j);
int interval_overlapps(Interval* i, Interval* j);
int interval_inside(Interval* i, float t);
void interval_destroy(Interval* i);

int interval_equal(Interval* i, Interval* j);
int interval_filter(Interval* i, float** pts, int num_pts);
float interval_len(Interval* i);
float interval_middle(Interval* i);
float interval_linear_scale(Interval* from, Interval* to, float t);
int intervals_subtract(Interval** intervals_up, int num_intervals_up, Interval** intervals_down, int num_intervals_down, Interval *** interrvals);
