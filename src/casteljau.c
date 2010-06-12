#include "casteljau.h"

float bezier_de_casteljau(Bezier* b, float t)
{
  float u = (t - b->a) / (b->b - b->a);

  assert(0.0f <= u && u <= 1.0f);
  // same as:
  assert(b->a <= t && t <= b->b);

  float (*d)[b->n + 1] = calloc((b->n + 1) * (b->n + 1), sizeof(float));

  float result;
  
  {
    for(int i = 0; i <= b->n; ++i)
      d[0][i] = b->c[i];
    
    for(int j = 1; j <= b->n; ++j)
      for(int i = 0; i <= b->n - j; ++i)
	d[j][i] = (1.0f - u) * d[j-1][i] + u * d[j-1][i+1];

    result = d[b->n][0];
  }

  free(d);
  return result;
}

void bezier_split(Bezier* b, float t, Bezier** left, Bezier** right)
{
  float u = (t - b->a) / (b->b - b->a);

  assert(0.0f <= u && u <= 1.0f);
  // same as:
  assert(b->a <= t && t <= b->b);
  
  *left = bezier_create(b->n);
  *right = bezier_create(b->n);

  float (*d)[b->n + 1] = calloc((b->n + 1) * (b->n + 1), sizeof(float));

  for(int i = 0; i <= b->n; ++i)
    d[0][i] = b->c[i];

  for(int j = 1; j <= b->n; ++j)
    for(int i = 0; i <= b->n - j; ++i)
      d[j][i] = (1.0f - u) * d[j-1][i] + u * d[j-1][i+1];

  for(int i = 0; i <= b->n; ++i)
  {
    (*left)->c[i] = d[i][0];
    (*right)->c[i] = d[b->n - i][i];
  }

  (*left)->a = b->a;
  (*left)->b = (*right)->a = t;
  (*right)->b = b->b;

  free(d);
}

Bezier* bezier_subrange(Bezier* b, float t1, float t2)
{
  Bezier* left = 0;
  Bezier* middle_and_right = 0;
  Bezier* middle = 0;
  Bezier* right = 0;

  bezier_split(b, t1, &left, &middle_and_right);
  bezier_split(middle_and_right, t2, &middle, &right);

  bezier_destroy(left);
  bezier_destroy(middle_and_right);
  bezier_destroy(right);

  return middle;
}
