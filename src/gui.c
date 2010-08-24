#include "init.h"

const float mouse_size = 20;

float* move_mod_x = 0;
float* move_mod_y = 0;

Graph** graphs = 0;
int num_graphs = 0;

void demo_cubic_roots1()
{
  Graph* g = graph_create("cubic_roots1");

  Bezier* b = sample_bezier_cosinus(3, 30);

  g->num_bezier = 1;
  g->bezier = malloc(sizeof(Bezier*));
  g->bezier[0] = b;

  g->num_roots = bezier_analytic_roots(b, &g->roots);

  graph_draw(g);
}
/*
void demo_cubic_roots2()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.5;
  b->c[1] = -1.0f;
  b->c[2] = 1.0;
  b->c[3] = -0.5;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_cubic_roots3()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.5;
  b->c[1] = 0.4f;
  b->c[2] = -0.4f;
  b->c[3] = -0.5;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}


void demo_cubic_roots4()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.5;
  b->c[1] = 0.4f;
  b->c[2] = -0.4f;
  b->c[3] = 0.5;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_above1()
{
  Bezier* b = bezier_create(2);
  b->c[0] = 0.5;
  b->c[1] = 0.6f;
  b->c[2] = -0.6f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
}

void demo_above2()
{
  Bezier* b = bezier_create(2);
  b->c[0] = -0.5;
  b->c[1] = 0.6f;
  b->c[2] = -0.6f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_above3()
{
  Bezier* b = bezier_create(3);
  b->c[0] = -0.5;
  b->c[1] = 0.6f;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_above4()
{
  Bezier* b = bezier_create(3);
  b->c[0] = -0.5;
  b->c[1] = 0.8f;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_intervals = power_above(bezier_to_power(b), &graphs[0]->intervals);
  graphs[0]->num_roots = bezier_analytic_roots(b, &graphs[0]->roots);
}

void demo_between1()
{
  Bezier* b = bezier_create(3);
  b->c[0] = -0.5;
  b->c[1] = 0.8f;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  Bezier* b2 = bezier_copy(b);
  bezier_inc_coeffs(b2, 0.1);
  graphs[1] = graph_create(b2);

  graphs[0]->num_intervals = bezier_intervals_between( b2, b, &graphs[0]->intervals);
}

void demo_between2()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.7;
  b->c[1] = -0.8;
  b->c[2] = -0.6f;
  b->c[3] = 0.1f;
  
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  Bezier* b2 = bezier_copy(b);
  bezier_inc_coeffs(b2, 0.1);
  graphs[1] = graph_create(b2);

  graphs[0]->num_intervals = bezier_intervals_between( b2, b, &graphs[0]->intervals);
}

void demo_between3()
{
  Bezier* b = bezier_create(3);
  b->c[0] = 0.1;
  b->c[1] = -0.2;
  b->c[2] = 0.2f;
  b->c[3] = 0.1f;
  
  num_graphs = 2;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  Bezier* b2 = bezier_copy(b);
  bezier_inc_coeffs(b2, 0.1);
  graphs[1] = graph_create(b2);

  graphs[0]->num_intervals = bezier_intervals_between( b2, b, &graphs[0]->intervals);
}

void demo_bounds1(int reduce)
{
  int deg = 7;
  Bezier* b = sample_bezier_sinus(deg, 7);
  b->c[0] = 0.1;
  
  num_graphs = 3;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  float** reduction_matrix = bezier_reduction_matrix(deg, reduce);
  Bezier* reduced = bezier_degree_reduction(b, reduce, reduction_matrix);
  Bezier* reduced_and_raised = bezier_copy(reduced);

  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(b, reduced_and_raised);
    
  Bezier* reduced_up = bezier_copy(reduced);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_copy(reduced);
  bezier_inc_coeffs(reduced_down, -difference);
    
  graphs[1] = graph_create(reduced_up);
  graphs[2] = graph_create(reduced_down);

  graphs[0]->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &graphs[0]->intervals);
}

void demo_bounds2(int reduce)
{
  int deg = 5;
  Bezier* b = bezier_create(deg);
  b->c[0] = 0.5;
  b->c[1] = -0.5;
  b->c[2] = 0.3;
  b->c[3] = 0.5;
  b->c[4] = -0.1;
  b->c[5] = -0.5;
  
  num_graphs = 3;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  float** reduction_matrix = bezier_reduction_matrix(deg, reduce);
  Bezier* reduced = bezier_degree_reduction(b, reduce, reduction_matrix);
  Bezier* reduced_and_raised = bezier_copy(reduced);

  bezier_degree_raise(reduced_and_raised, deg);

  float difference = bezier_max_coeff_diff(b, reduced_and_raised);
    
  Bezier* reduced_up = bezier_copy(reduced);
  bezier_inc_coeffs(reduced_up, difference);
  Bezier* reduced_down = bezier_copy(reduced);
  bezier_inc_coeffs(reduced_down, -difference);
    
  graphs[1] = graph_create(reduced_up);
  graphs[2] = graph_create(reduced_down);

  graphs[0]->num_intervals = bezier_intervals_between(reduced_up, reduced_down, &graphs[0]->intervals);
}

void demo_cubic_clip1()
{
  Bezier* b = sample_bezier_sinus(7, 10);
  b->c[0] = 0.1;
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_roots(b, &graphs[0]->roots, 0.001f, 3);
}

void demo_cubic_clip2()
{
  Bezier* b = sample_bezier_cosinus(7, 10);
  
  num_graphs = 1;
  graphs = malloc(sizeof(Graph*) * num_graphs);
  graphs[0] = graph_create(b);

  graphs[0]->num_roots = bezier_roots(b, &graphs[0]->roots, 0.001f, 3);
}
*/

void demo()
{
  demo_cubic_roots1();
  //demo_cubic_roots2();
  //demo_cubic_roots3();
  //demo_cubic_roots4();

  //demo_above1();
  //demo_above2();
  //demo_above3();
  //demo_above4();

  //demo_between1();
  //demo_between2();
  //demo_between3();

  //demo_bounds1(3);
  //demo_bounds1(2);

  //demo_bounds2(3);
  //demo_bounds2(2);
  
  //demo_cubic_clip1();
  //demo_cubic_clip2();
}
