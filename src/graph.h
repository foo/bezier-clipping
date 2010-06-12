#pragma once

#include <malloc.h>
#include "bezier.h"
#include "casteljau.h"
#include "roots.h"

typedef struct
{
  Bezier* bezier;
  int draw_control_line;
  int draw_control_points;
  int draw_axis;
  int draw_roots;
  float color_r;
  float color_g;
  float color_b;
  float width;
  float height;
  float offset_x;
  float offset_y;
  float precision;
} Graph;

Graph* graph_create(Bezier* b);
void graph_draw(Graph* g);
