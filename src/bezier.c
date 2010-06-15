#include "bezier.h"

Bezier* bezier_create(int N)
{
  Bezier* b = malloc(sizeof(Bezier));
  b->n = N;
  b->c = (float*)malloc(sizeof(float) * (b->n + 1));

  b->dom = interval_create(0.0f, 1.0f);

  return b;
}

Bezier* bezier_create_with_coeffs(int N, float* coeffs)
{
  Bezier* b = malloc(sizeof(Bezier));
  b->n = N;
  b->c = coeffs;

  b->dom = interval_create(0.0f, 1.0f);

  return b;
}

Bezier* bezier_copy(Bezier* b)
{
  Bezier* b2 = bezier_create(b->n);
  memcpy(b2->c, b->c, sizeof(float) * (b->n + 1));
  
  b2->dom = interval_copy(b->dom);
  return b2;
}

void bezier_destroy(Bezier* b)
{
  free(b->c);
  free(b->dom);
  free(b);
}

/*
 * It's not the most effective version, as it raises the polynomial one degree (M - b->n) times
 */
void bezier_degree_raise(Bezier* b, int M)
{
  b->c = realloc(b->c, sizeof(float) * (M + 1));
  
  for(int m = b->n + 1; m <= M; ++m, ++b->n)
  {
    b->c[m] = b->c[b->n];
    for(int i = b->n; i >= 1; --i)
      b->c[i] = (i*b->c[i-1]+(m-i)*b->c[i])/((float)m);
  }
}

float bezier_max_coeff_diff(Bezier* b1, Bezier* b2)
{
  // equal degrees are required in opposition to automatically raising degree in order to preserve b1 and b2
  assert(b1->n == b2->n);

  assert(interval_equal(b1->dom, b2->dom));

  float result = fabs(b1->c[0] - b2->c[0]);
  for(int i = 1; i <= b1->n; ++i)
    if(result < fabs(b1->c[i] - b2->c[i]))
      result = fabs(b1->c[i] - b2->c[i]);
  return result;
}

void bezier_inc_coeffs(Bezier* b, float ratio)
{
  for(int i = 0; i <= b->n; ++i)
    b->c[i] += ratio;
}

int bezier_analytic_roots(Bezier* b, float** roots)
{
  Power* p = bezier_to_power(b);

  Interval* zero_one = interval_create(0.0f, 1.0f);

  int num_roots = power_analytic_roots(p, roots);
  for(int i = 0; i < num_roots; ++i)
    (*roots)[i] = interval_linear_scale(zero_one, b->dom, (*roots)[i]);

  interval_destroy(zero_one);
  
  return interval_filter(b->dom, roots, num_roots);
}

Power* bezier_to_power(Bezier* b)
{
  assert(b);

  if(b->n == 2)
  {
    float A = b->c[0] - 2*b->c[1] + b->c[2];
    float B = -2*b->c[0] + 2*b->c[1];
    float C = b->c[0];

    Power* p = power_create(3);
    p->c[0] = A;
    p->c[1] = B;
    p->c[2] = C;
    p->dom = interval_copy(b->dom);
    p->n = b->n;
    return p;
  }
  else if(b->n == 3)
  {
    float A = -b->c[0] + 3*b->c[1] - 3*b->c[2] + b->c[3];
    float B = 3*b->c[0] - 6*b->c[1] + 3*b->c[2];
    float C = -3*b->c[0] + 3*b->c[1];
    float D = b->c[0];
    
    Power* p = power_create(4);
    p->c[0] = A;
    p->c[1] = B;
    p->c[2] = C;
    p->c[3] = D;
    p->dom = interval_copy(b->dom);
    p->n = b->n;
    return p;
  }
  else
  {
    assert(0); // unimplemented, out of scope of this program
  }
}
