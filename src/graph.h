#pragma once

#include <malloc.h>
#include <stdio.h>
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
  
  Interval** intervals;
  int num_intervals;

  float* roots;
  int num_roots;
} Graph;

Graph* graph_create(char* dir);
void graph_draw(Graph* g);
void graph_add_bezier(Graph* g, Bezier* b);
