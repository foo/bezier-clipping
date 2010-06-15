#include "quadclip.h"

void bezier_quadclip_aux(Bezier* original, float** intervals, int* num_intervals, float eps, float** reduction_matrix);


int bezier_quadclip(Bezier* original, float** roots, float eps)
{
  int num_roots = 0;

  *roots = malloc(sizeof(float) * original->n);

  float** reduction_matrix = bezier_reduction_matrix(original->n, 2);

  bezier_quadclip_aux(original, roots, &num_roots, eps, reduction_matrix);

  return num_roots;
}

void bezier_quadclip_aux(Bezier* original, float** roots, int* num_roots, float eps, float** reduction_matrix)
{
  if(interval_len(original->dom) <= 2.0f*eps)
  {
    (*roots)[(*num_roots)++] = interval_middle(original->dom);
  }
  else
  {
    const int deg = original->n;
    Bezier* reduced = bezier_degree_reduction(original, 2, reduction_matrix);
    Bezier* reduced_and_raised = bezier_copy(reduced);

    bezier_degree_raise(reduced_and_raised, deg);
    
    float difference = bezier_max_coeff_diff(original, reduced_and_raised);
    Bezier* reduced_up = bezier_copy(reduced);
    bezier_inc_coeffs(reduced_up, difference);
    Bezier* reduced_down = bezier_copy(reduced);
    bezier_inc_coeffs(reduced_down, -difference);
    
    bezier_destroy(reduced);
    
    Interval** ox_intervals = 0;
    int ox_num_intervals = 0;
    
    ox_num_intervals = bezier_quad_intervals_between(reduced_up, reduced_down, &ox_intervals);
    
    for(int i = 0; i < ox_num_intervals; ++i)
    {
      if(interval_len(ox_intervals[i]) < interval_len(original->dom) / 2.0f)
      {
	Bezier* clipped = bezier_subrange(original, ox_intervals[i]->a, ox_intervals[i]->b);
	bezier_quadclip_aux(clipped, roots, num_roots, eps, reduction_matrix);
	bezier_destroy(clipped);
      }
      else
      {
	const float middle = interval_middle(ox_intervals[i]);
	Bezier* clipped_left = bezier_subrange(original, ox_intervals[i]->a, middle);
	Bezier* clipped_right = bezier_subrange(original, middle, ox_intervals[i]->b);
	bezier_quadclip_aux(clipped_left, roots, num_roots, eps, reduction_matrix);
	bezier_quadclip_aux(clipped_right, roots, num_roots, eps, reduction_matrix);

	bezier_destroy(clipped_left);
	bezier_destroy(clipped_right);
      }
    }
  }
}

int bezier_quad_above(Bezier* b, Interval*** intervals)
{
  assert(b->n == 2);

  float A = b->c[0] - 2*b->c[1] + b->c[2];
  float B = -2*b->c[0] + 2*b->c[1];

  float* roots = 0;
  int num_roots = bezier_analytic_roots(b, &roots);
  
  if(A == 0)
  {
    if(num_roots == 0)
      return 0;
    else
    {
      if(B > 0)
      {
	*intervals = malloc(sizeof(Interval*));
	(*intervals)[0] = interval_create(b->dom->a, roots[0]);
	return 1;
      }
      else
      {
	*intervals = malloc(sizeof(Interval*));
	(*intervals)[0] = interval_create(roots[0], b->dom->b);
	return 1;
      }
    }
  }
  else
  {
    float C = b->c[0];
    float delta = B*B - 4*A*C;

    if(delta == 0)
      return 0;
    else
    {
      if(A > 0)
      {
	if(num_roots == 2)
	{
	  *intervals = malloc(sizeof(Interval*));
	  (*intervals)[0] = interval_create(roots[0], roots[1]);
	  return 1;
	}
	else if(num_roots == 1)
	{
	  float Wx = -B / (2 * A);
	  if(Wx < roots[0])
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(b->dom->a, roots[0]);
	    return 1;
	  }
	  else
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(roots[0], b->dom->b);
	    return 1;
	  }
	}
	else
	{
	  assert(num_roots == 0);

	  const float half = interval_middle(b->dom);
	  if(bezier_de_casteljau(b, half) < 0)
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_copy(b->dom);
	    return 1;
	  }
	  else
	    return 0;
	}
      }
      else
      {
	if(num_roots == 2)
	{
	  *intervals = malloc(sizeof(Interval*) * 2);
	  (*intervals)[0] = interval_create(b->dom->a, roots[0]);
	  (*intervals)[1] = interval_create(roots[1], b->dom->b);
	  return 2;
	}
	else if(num_roots == 1)
	{
	  float Wx = -B / (2 * A);
	  if(Wx < roots[0])
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(roots[0], b->dom->b);
	    return 1;
	  }
	  else
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(b->dom->a, roots[0]);
	    return 1;
	  }
	}
	else
	{
	  assert(num_roots == 0);

	  const float half = interval_middle(b->dom);
	  if(bezier_de_casteljau(b, half) < 0)
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_copy(b->dom);
	    return 1;
	  }
	  else
	    return 0;
	}
      }
    }
  }
}

int bezier_quad_intervals_between(Bezier* up, Bezier* down, Interval*** intervals)
{
  assert(up->n == 2);
  assert(down->n == 2);

  Interval** intervals_up = 0;
  int num_intervals_up = bezier_quad_above(up, &intervals_up);

  Interval** intervals_down = 0;
  int num_intervals_down = bezier_quad_above(down, &intervals_down);

  // keep intervals above "down" and subtract intervals above "up"

  int inserter = 0;
  *intervals = malloc(sizeof(Interval*) * 4);
  for(int i = 0; i < num_intervals_down; ++i)
  {
    if(!interval_empty(intervals_down[i]))
    {
      Interval* actual = (*intervals)[inserter++] = interval_copy(intervals_down[i]);
    
      for(int j = 0; j < num_intervals_up; ++j)
      {
	if(interval_overlapps(actual, intervals_up[j]))
	{
	  --inserter;
	  Interval** diff = 0;
	  int num_diff = interval_difference(actual, intervals_up[j], &diff);
	  
	  for(int k = 0; k < num_diff; ++k)
	  {
	    if(!interval_empty(diff[k]))
	    {
	      (*intervals)[inserter++] = interval_copy(diff[k]);
	    }
	  }
	}
      }
    }
  }

  return inserter;
}
