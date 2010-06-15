#include "interval.h"

Interval* interval_create(float a, float b)
{
  Interval* i = malloc(sizeof(Interval));
  i->a = a;
  i->b = b;
  return i;
}

Interval* interval_intersection(Interval* i, Interval* j)
{
  return interval_create(max(i->a, j->a), min(i->b, j->b));
}

Interval* interval_copy(Interval* i)
{
  return interval_create(i->a, i->b);
}

int interval_difference(Interval* i, Interval* j, Interval*** intervals)
{
  if(!interval_overlapps(i, j))
  {
    *intervals = malloc(sizeof(Interval*));
    (*intervals)[0] = interval_copy(i);
    return 1;
  }
  else if(!interval_subinterval(i, j))
  {
    if(i->a < j->a)
    {
      *intervals = malloc(sizeof(Interval*));
      (*intervals)[0] = interval_create(j->b, i->b);
      return 1;
    }
    else
    {
      *intervals = malloc(sizeof(Interval*));
      (*intervals)[0] = interval_create(i->a, j->a);
      return 1;
    }
  }
  else
  {
    *intervals = malloc(2 * sizeof(Interval*));
    (*intervals)[0] = interval_create(i->a, j->a);
    (*intervals)[1] = interval_create(j->b, i->b);
    return 2;
  }
}

int interval_subinterval(Interval* i, Interval* j)
{
  return interval_empty(j) || (interval_inside(i, j->a) && interval_inside(i, j->b));
}

int interval_inside(Interval* i, float t)
{
  return i->a <= t && t <= i->b;
}

int interval_overlapps(Interval* i, Interval* j)
{
  return
    !interval_empty(i) &&
    !interval_empty(j) &&
    (interval_inside(i, j->a) || interval_inside(i, j->b)
    || interval_inside(j, i->a) || interval_inside(j, i->b));
}

int interval_empty(Interval* i)
{
  return i->a >= i->b;
}

void interval_destroy(Interval* i)
{
  free(i);
}

int interval_filter(Interval* i, float** pts, int num_pts)
{
  int inserter = 0;
  for(int k = 0; k < num_pts; ++k)
    if(interval_inside(i, (*pts)[k]))
    {
      if(inserter == k)
      {
	inserter++;
      }
      else
      {
	(*pts)[inserter++] = (*pts)[k];
      }
    }

  *pts = realloc(*pts, sizeof(float) * inserter);
  return inserter;
}

int interval_equal(Interval* i, Interval* j)
{
  assert(i);
  assert(j);

  return (interval_empty(i) && interval_empty(j)) || (i->a == j->a && i->b == j->b);
}

float interval_len(Interval* i)
{
  assert(i);
  return (interval_empty(i)) ? 0.0f : i->b - i->a;
}

float interval_middle(Interval* i)
{
  assert(i);
  assert(!interval_empty(i));
  
  return (i->a + i->b) / 2.0f;
}

float interval_linear_scale(Interval* from, Interval* to, float t)
{
  return ((t - from->a) / interval_len(from)) * interval_len(to) + to->a;
}
