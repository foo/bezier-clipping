#pragma once

#include <malloc.h>
#include "bezier.h"
#include "graph.h"
#include "reduction.h"
#include "quadclip.h"
#include "cubicclip.h"
#include "samples.h"
#include "interval.h"

void init();
void key_press(unsigned char);
void mouse_left_click();
void mouse_right_click();
void mouse_move();
void update();
void draw();
