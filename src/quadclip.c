#include "quadclip.h"

void bezier_roots_aux(Bezier* original, float** intervals, int* num_intervals, float eps, float** reduction_matrix, int reduce);

int bezier_roots(Bezier* original, float** roots, float eps, int reduce)
{
  int num_roots = 0;

  *roots = malloc(sizeof(float) * original->n);

  float** reduction_matrix = bezier_reduction_matrix(original->n, reduce);

  bezier_roots_aux(original, roots, &num_roots, eps, reduction_matrix, reduce);

  return num_roots;
}

void bezier_roots_aux(Bezier* original, float** roots, int* num_roots, float eps, float** reduction_matrix, int reduce)
{
  if(interval_len(original->dom) <= 2.0f*eps)
  {
    (*roots)[(*num_roots)++] = interval_middle(original->dom);
  }
  else
  {
    const int deg = original->n;
    Bezier* reduced = bezier_degree_reduction(original, reduce, reduction_matrix);
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
    
    ox_num_intervals = bezier_intervals_between(reduced_up, reduced_down, &ox_intervals);
    printf("ox = %d\n", ox_num_intervals);
    
    for(int i = 0; i < ox_num_intervals; ++i)
    {
      if(!interval_subinterval(original->dom, ox_intervals[i]))
      {
	printf("o: %f %f\n", original->dom->a, original->dom->b);
	printf("i: %f %f\n", ox_intervals[i]->a, ox_intervals[i]->b);
      }
      assert(interval_subinterval(original->dom, ox_intervals[i]));

      if(interval_len(ox_intervals[i]) < interval_len(original->dom) / 2.0f)
      {
	Bezier* clipped = bezier_subrange(original, ox_intervals[i]->a, ox_intervals[i]->b);
	bezier_roots_aux(clipped, roots, num_roots, eps, reduction_matrix, reduce);
	bezier_destroy(clipped);
      }
      else
      {
	const float middle = interval_middle(ox_intervals[i]);
	Bezier* clipped_left = bezier_subrange(original, ox_intervals[i]->a, middle);
	Bezier* clipped_right = bezier_subrange(original, middle, ox_intervals[i]->b);
	bezier_roots_aux(clipped_left, roots, num_roots, eps, reduction_matrix, reduce);
	bezier_roots_aux(clipped_right, roots, num_roots, eps, reduction_matrix, reduce);

	bezier_destroy(clipped_left);
	bezier_destroy(clipped_right);
      }
    }
  }
}

int bezier_intervals_between(Bezier* up, Bezier* down, Interval*** intervals)
{
  assert(up->n == down->n);
  assert(interval_equal(up->dom, down->dom));

  Interval* zero_one = interval_create(0.0f, 1.0f);
  Interval** intervals_up = 0;
  int num_intervals_up = power_above(bezier_to_power(up), &intervals_up);
  for(int i = 0; i < num_intervals_up; ++i)
  {
    intervals_up[i]->a = interval_linear_scale(zero_one, up->dom, intervals_up[i]->a);
    intervals_up[i]->b = interval_linear_scale(zero_one, up->dom, intervals_up[i]->b);
  }

  Interval** intervals_down = 0;
  int num_intervals_down = power_above(bezier_to_power(down), &intervals_down);
  for(int i = 0; i < num_intervals_down; ++i)
  {
    intervals_down[i]->a = interval_linear_scale(zero_one, down->dom, intervals_down[i]->a);
    intervals_down[i]->b = interval_linear_scale(zero_one, down->dom, intervals_down[i]->b);
  }

  return intervals_subtract(intervals_down, num_intervals_down, intervals_up, num_intervals_up, intervals);
}
