#pragma once

#include <assert.h>
#include "bezier.h"
#include "utils.h"

int bezier_quad_roots(Bezier* b, float** roots);
int bezier_cubic_roots(Bezier* b, float** roots);
