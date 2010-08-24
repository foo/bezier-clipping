#pragma once

#include <malloc.h>
#include "bezier.h"
#include "casteljau.h"
#include "interval.h"

typedef struct
{
  char* dirname;
  
  Bezier** bezier;
  int num_bezier;
  
  int draw_control_line;
  int draw_control_points;
  int draw_axis;
  float color_r;
  float color_g;
  float color_b;
  float width;
  float height;
  float offset_x;
  float offset_y;
  float precision;
  
  Interval** intervals;
  int num_intervals;

  float* roots;
  int num_roots;
} Graph;

Graph* graph_create(char* dir);
void graph_draw(Graph* g);
