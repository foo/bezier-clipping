#include "graph.h"

Graph* graph_create(char* dir)
{
  Graph* g = malloc(sizeof(Graph));

  g->dirname = dir;
  
  g->draw_control_line = 0;
  g->draw_control_points = 1;
  g->draw_axis = 1;
  g->color_r = 0.0f;
  g->color_g = 0.0f;
  g->color_b = 0.0f;
  g->width = 400.0f;
  g->height = 400.0f;
  g->offset_x = 100.0f;
  g->offset_y = 200.0f;
  g->precision = 0.001f;

  g->bezier = 0;
  g->num_bezier = 0;
  
  g->roots = 0;
  g->num_roots = 0;

  g->intervals = 0;
  g->num_intervals = 0;
  
  return g;
}

void bezier_to_file(Bezier* b, FILE* f)
{
  fprintf(f, "bezier\n");
}

void bezier_control_to_file(Bezier* b, FILE* f)
{
  fprintf(f, "ctrl\n");
}

/*
 * kazdy graph musi wyprodukowac:
 ** katalog danego wykresu, nalezy go nazwac w konstruktorze graph
 ** plik gnuplota

 * nalezy umozliwic wrzucanie wielu wielomianow do jednego wykresu, dlatego graph powinien miec kolekcje wielomianow a nie jeden wielomian (lub nalezy to podzielic na zbiory graph)

 * mozna pominac rysowanie osi
 * punkty kontrolne powinny byc osobnym wykresem (with circles)
 * lamana kontrolna powinna byc osobnym wykresem (with lines)

 * nalezy jakos zaznaczac intervals i roots
 */

void graph_draw(Graph* g)
{
  assert(g->num_bezier != 0);

  FILE* gnuplot = fopen("../tests/default/gnuplot.pg", "w");
  fprintf(gnuplot, "set term postscript eps enhanced\nset output \"graph.eps\"\n");

  for(int i = 0; i < g->num_bezier; ++i)
  {
    char control_path[256];
    sprintf(control_path, "../tests/default/control%d.xy", i);
    FILE* control = fopen(control_path, "w");
    bezier_control_to_file(g->bezier[i], control);
    
    char bezier_path[256];
    sprintf(bezier_path, "../tests/default/bezier%d.xy", i);
    FILE* bezier = fopen(bezier_path, "w");
    bezier_to_file(g->bezier[i], bezier);
    
    fprintf(gnuplot, "plot %s with ????\n", control_path);
    fprintf(gnuplot, "plot %s with ????\n", bezier_path);
  }

  // for num_intervals
  // for num_roots
  
  // utworz num_bezier plikow z parami dziedzina->wartosc
  // utworz num_bezier plikow z parami i/n->punkt kontrolny
  // utworz num_interval plikow z bound rect
  // utworz num_roots plikow z parami root->0 (circles)
  
  /*
  glColor3f(g->color_r, g->color_g, g->color_b);
  
  if(g->draw_control_line)
  {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= g->bezier->n; i++)
    {
      const float x_01 = (float)i / (float)g->bezier->n;
      const float x_ab = x_01 * (g->bezier->dom->b - g->bezier->dom->a) + g->bezier->dom->a;
      
      glVertex2f(
	g->offset_x + g->width * x_ab,
	g->offset_y + g->height * g->bezier->c[i]
		 );
    }
    glEnd();
  }

  glLineWidth(1.0f);
  if(g->draw_control_points)
  {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= g->bezier->n; i++)
    {
      const float x_01 = (float)i / (float)g->bezier->n;
      const float x_ab = x_01 * (g->bezier->dom->b - g->bezier->dom->a) + g->bezier->dom->a;
      
      glVertex2f(
	g->offset_x + g->width * x_ab,
	g->offset_y + g->height * g->bezier->c[i]
		 );

    }
    glEnd();
  }

  glLineWidth(1.0f);
  if(g->draw_axis)
  {
    glBegin(GL_LINES);
    glVertex2f(g->offset_x, g->offset_y);
    glVertex2f(g->offset_x, g->offset_y + g->height);

    glVertex2f(g->offset_x, g->offset_y);
    glVertex2f(g->offset_x + g->width, g->offset_y);
    glEnd();
  }

  glLineWidth(1.0f);
  glBegin(GL_LINE_STRIP);
  for(float t = g->bezier->dom->a; t <= g->bezier->dom->b; t += g->precision)
  {
    const float ft = bezier_de_casteljau(g->bezier, t);

    glVertex2f(
      g->offset_x + g->width * t,
      g->offset_y + g->height * ft
	       );
  }
  glEnd();

  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  
  for(int i = 0; i < g->num_intervals; ++i)
  {
    assert(g->intervals);
    assert(g->intervals[i]);
    assert(!interval_empty(g->intervals[i]));
    glVertex2f(g->offset_x + g->width * g->intervals[i]->a, g->offset_y);
    glVertex2f(g->offset_x + g->width * g->intervals[i]->b, g->offset_y);
  }
  glEnd();

  glBegin(GL_POINTS);
  
  for(int i = 0; i < g->num_intervals; ++i)
  {
    assert(g->intervals);
    assert(g->intervals[i]);
    assert(!interval_empty(g->intervals[i]));
    glVertex2f(g->offset_x + g->width * g->intervals[i]->a, g->offset_y);
    glVertex2f(g->offset_x + g->width * g->intervals[i]->b, g->offset_y);
  }
  glEnd();

  glBegin(GL_POINTS);
  
  for(int i = 0; i < g->num_roots; ++i)
  {
    assert(g->roots);
    glVertex2f(g->offset_x + g->width * g->roots[i], g->offset_y);
  }
  glEnd();
  
  glLineWidth(1.0f);
  */
}
