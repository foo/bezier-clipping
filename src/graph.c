#include "graph.h"

Graph* graph_create(Bezier* b)
{
  Graph* g = malloc(sizeof(Graph));

  g->bezier = b;
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

  g->roots = 0;
  g->num_roots = 0;

  g->intervals = 0;
  g->num_intervals = 0;
  
  return g;
}

void graph_draw(Graph* g)
{
  glColor3f(g->color_r, g->color_g, g->color_b);
  
  glLineWidth(1.0f);
  if(g->draw_control_line)
  {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= g->bezier->n; i++)
    {
      const float x_01 = (float)i / (float)g->bezier->n;
      const float x_ab = x_01 * (g->bezier->b - g->bezier->a) + g->bezier->a;
      
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
      const float x_ab = x_01 * (g->bezier->b - g->bezier->a) + g->bezier->a;
      
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
  for(float t = g->bezier->a; t <= g->bezier->b; t += g->precision)
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
}
