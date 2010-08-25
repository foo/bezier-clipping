#include <malloc.h>
#include "bezier.h"
#include "graph.h"
#include "reduction.h"
#include "quadclip.h"
#include "samples.h"
#include "interval.h"

void demo_cubic_roots1()
{
  Graph* g = graph_create("cubic_roots1");

  Bezier* b = sample_bezier_cosinus(3, 30);

  graph_add_bezier(g, b);

  g->num_roots = bezier_analytic_roots(b, &g->roots);

  graph_draw(g);
}

void demo_between2()
{
  Graph* g = graph_create("between2");
  
  Bezier* b = bezier_create(3);
  b->c[0] = 0.7;
  b->c[1] = -0.8;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  Bezier* b2 = bezier_copy(b);
  bezier_inc_coeffs(b2, 0.1);

  graph_add_bezier(g, b);
  graph_add_bezier(g, b2);
  
  g->num_intervals = bezier_intervals_between( b2, b, &g->intervals);
  
  graph_draw(g);
}

void demo_bounds2()
{
  Graph* g = graph_create("bounds2");

  g->draw_control_line = 0;
  g->draw_control_points = 0;

  int reduce = 3;
  int deg = 5;
  
  Bezier* b = sample_bezier_sinus(deg, 7);

  float** reduction_matrix = bezier_reduction_matrix(deg, reduce);
  Bezier* reduced = bezier_degree_reduction(b, reduce, reduction_matrix);
  Bezier* reduced_and_raised = bezier_copy(reduced);

  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(b, reduced_and_raised);
    
  Bezier* reduced_up = bezier_copy(reduced);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_copy(reduced);
  bezier_inc_coeffs(reduced_down, -difference);

  graph_add_bezier(g, b);
  graph_add_bezier(g, reduced);
  graph_add_bezier(g, reduced_up);
  graph_add_bezier(g, reduced_down);

  g->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &g->intervals);

  graph_draw(g);
}


int main(int argc, char** argv)
{
  demo_bounds2();
  
  return 0;
}
