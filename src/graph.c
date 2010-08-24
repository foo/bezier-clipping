#include "graph.h"

Graph* graph_create(char* dir)
{
  Graph* g = malloc(sizeof(Graph));

  g->dirname = dir;
  
  g->draw_control_line = 1;
  g->draw_control_points = 1;

  g->bezier = 0;
  g->num_bezier = 0;
  
  g->roots = 0;
  g->num_roots = 0;

  g->intervals = 0;
  g->num_intervals = 0;
  
  return g;
}

void graph_add_bezier(Graph* g, Bezier* b)
{
  g->num_bezier++;
  g->bezier = realloc(g->bezier, sizeof(Bezier*) * g->num_bezier);
  g->bezier[g->num_bezier-1] = b;
}


void bezier_to_file(Bezier* b, FILE* f)
{
  fprintf(f, "bezier\n");
  for(float t = b->dom->a; t <= b->dom->b; t += 0.001f)
  {
    const float ft = bezier_de_casteljau(b, t);

    fprintf(f, "%f %f\n", t, ft);
  }
}

void bezier_control_to_file(Bezier* b, FILE* f)
{
  for(int i = 0; i <= b->n; i++)
  {
    const float x_01 = (float)i / (float)b->n;
    const float x_ab = x_01 * (b->dom->b - b->dom->a) + b->dom->a;

    fprintf(f, "%f %f\n", x_ab, b->c[i]);
  }
}

void graph_draw(Graph* g)
{
  assert(g->num_bezier != 0);

  char gnuplot_path[256];
  sprintf(gnuplot_path, "../tests/%s/gnuplot.pg", g->dirname);

  FILE* gnuplot = fopen(gnuplot_path, "w");
  fprintf(gnuplot, "set term postscript eps enhanced\n");
  fprintf(gnuplot, "set output \"graph.eps\"\n");
  fprintf(gnuplot, "set xzeroaxis lt -1\n");
  fprintf(gnuplot, "set yzeroaxis lt -1\n");

  fprintf(gnuplot, "plot ");

  int first_plot = 1;
  
  for(int i = 0; i < g->num_bezier; ++i)
  {
    if(g->draw_control_line || g->draw_control_points)
    {
      char control_path[256];
      char control_full_path[256];
      sprintf(control_path, "control%d.xy", i);
      sprintf(control_full_path, "../tests/%s/%s", g->dirname, control_path);
      FILE* control = fopen(control_full_path, "w");
      bezier_control_to_file(g->bezier[i], control);

      if(g->draw_control_line)
      {
	if(!first_plot)
	  fprintf(gnuplot, ",");
	else
	  first_plot = 0;
	fprintf(gnuplot, "\"%s\" using 1:2 title \"lamana kontrolna\" with lines", control_path);
      }
      
      if(g->draw_control_points)
      {
	if(!first_plot)
	  fprintf(gnuplot, ",");
	else
	  first_plot = 0;

	fprintf(gnuplot, "\"%s\" using 1:2 title \"lamana kontrolna\" with points", control_path);
      }
    }
    
    char bezier_path[256];
    char bezier_full_path[256];
    sprintf(bezier_path, "bezier%d.xy", i);
    sprintf(bezier_full_path, "../tests/%s/%s", g->dirname, bezier_path);
    FILE* bezier = fopen(bezier_full_path, "w");
    bezier_to_file(g->bezier[i], bezier);

    if(!first_plot)
      fprintf(gnuplot, ",");
    else
      first_plot = 0;

    fprintf(gnuplot, "\"%s\" using 1:2 title \"wielomian Beziera\" with lines", bezier_path);
  }

  if(g->num_roots != 0)
  {
    char roots_path[256];
    char roots_full_path[256];
    sprintf(roots_path, "roots.xy");
    sprintf(roots_full_path, "../tests/%s/%s", g->dirname, roots_path);
    
    FILE* roots = fopen(roots_full_path, "w");
    
    for(int i = 0; i < g->num_roots; ++i)
    {
      fprintf(roots, "%f 0.0\n", g->roots[i]);
    }
    
    if(!first_plot)
      fprintf(gnuplot, ",");
    else
      first_plot = 0;
    
    fprintf(gnuplot, "\"%s\" using 1:2:(0.005) title \"miejsca zerowe\" with circles", roots_path);
  }
  
  if(g->num_intervals != 0)
  {
    char intervals_path[256];
    char intervals_full_path[256];
    sprintf(intervals_path, "intervals.xy");
    sprintf(intervals_full_path, "../tests/%s/%s", g->dirname, intervals_path);
    
    FILE* roots = fopen(intervals_full_path, "w");
    
    for(int i = 0; i < g->num_intervals; ++i)
    {
      fprintf(roots, "%f %f\n", g->intervals[i]->a, g->intervals[i]->b - g->intervals[i]->a);
    }
    
    if(!first_plot)
      fprintf(gnuplot, ",");
    else
      first_plot = 0;
    
    fprintf(gnuplot, "\"%s\" using 1:(-0.01):2 title \"przedzialy\" with xerrorbars", intervals_path);
  }
}
