#pragma once

#include "bezier.h"

float bezier_de_casteljau(Bezier* b, float u);
void bezier_split(Bezier* b, float u, Bezier** left, Bezier** right);
Bezier* bezier_subrange(Bezier* b, float t1, float t2);
