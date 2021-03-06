#include "power.h"

Power* power_create(int deg)
{
  Power* p = malloc(sizeof(Power));
  p->n = deg;
  p->c = (float*)malloc(sizeof(float) * (p->n + 1));
  return p;
}

void power_destroy(Power* p)
{
  free(p);
}

int power_linear_roots(float A, float B, float** roots);
int power_quad_roots(float A, float B, float C, float** roots);
int power_cubic_roots(float A, float B, float C, float D, float** roots);

int power_analytic_roots(Power* p, float** roots)
{
  if(p->n == 1)
    return power_linear_roots(p->c[0], p->c[1], roots);
  else if(p->n == 2)
    return power_quad_roots(p->c[0], p->c[1], p->c[2], roots);
  else if(p->n == 3)
    return power_cubic_roots(p->c[0], p->c[1], p->c[2], p->c[3], roots);
  else
  {
    assert(0); // power basis root finder of polynomials of degree higher then 3 is not the point of this program
    return 0;
  }
}

int power_linear_roots(float A, float B, float** roots)
{
  if(A == 0)
  {
    // function is constant and we treat f(x) == 0 as no roots
    return 0;
  }
  else
  {
    float root = -B / A;
    *roots = malloc(sizeof(float));
    (*roots)[0] = root;
    return 1;
  }
}

int power_quad_roots(float A, float B, float C, float** roots)
{
  if(A == 0)
  {
    return power_linear_roots(B, C, roots);
  }
  else
  {
    float delta = B*B - 4*A*C;
  
    if(delta < 0)
    {
      *roots = 0;
      return 0;
    }
    else
    {
      // quadratic formula and scaling from [0,1] to [a,b]
      float lroot = (-B - sqrtf(delta)) / (2*A);
      float rroot = (-B + sqrtf(delta)) / (2*A);
      
      if(lroot > rroot)
      {
	swap(&lroot, &rroot);
      }
      
      assert(lroot <= rroot);
      
      if(lroot == rroot)
      {
	*roots = malloc(sizeof(float));
	(*roots)[0] = lroot;
	return 1;
      }
      else
      {
	*roots = malloc(2 * sizeof(float));
	(*roots)[0] = lroot;
	(*roots)[1] = rroot;
	return 2;
      }
    }
  }
}

int power_cubic_roots(float A, float B, float C, float D, float** roots)
{
  if(A == 0)
  {
    return power_quad_roots(B, C, D, roots);
  }
  else
  {
    *roots = malloc(sizeof(float) * 3);
    
    float w = B / (3 * A);
    float p = (C / (3 * A) - w*w)*(C / (3 * A) - w*w)*(C / (3 * A) - w*w);
    float q = -0.5 * (2 * w*w*w - (C * w - D) / A);
    float delta = q*q + p;
    
    if(delta < 0.0)
    {
      float h = q / sqrt(-p);
      float phi = acos(max(-1.0, min(1.0, h)));
      p = 2 * pow(-p, 1.0 / 6.0);

      int inserter = 0;
      for(; inserter < 3; inserter++)
	(*roots)[inserter] = p * cos((phi + 2 * inserter * PI) / 3.0) - w;
      
      if ((*roots)[1] < (*roots)[0]) swap(&(*roots)[0], &(*roots)[1]);
      if ((*roots)[2] < (*roots)[1]) swap(&(*roots)[1], &(*roots)[2]);
      if ((*roots)[1] < (*roots)[0]) swap(&(*roots)[0], &(*roots)[1]);

      assert((*roots)[0] < (*roots)[1] && (*roots)[1] < (*roots)[2]);
      
      return 3;
    }
    else
    {
      delta = sqrt(delta);
      *roots = malloc(sizeof(float));
      (*roots)[0] = CBRT(q + delta) + CBRT(q - delta) - w;
      return 1;
    }
  }
}

float power_eval(Power* p, float t)
{
  float res = p->c[0];
  for(int i = 1; i <= p->n; ++i)
    res = res * t + p->c[i];
  return res;
}

Power* power_derivative(Power* p)
{
  Power* d = power_create(p->n - 1);
  for(int i = 0; i <= d->n; ++i)
    d->c[i] = p->c[i] * (p->n - i);

  return d;
}

// in [0,1]
int power_above(Power* p, Interval*** intervals)
{
  float* roots = 0;
  int num_roots = power_analytic_roots(p, &roots);
  num_roots = interval_filter(interval_create(0,1), &roots, num_roots);

  int inserter = 0;

  if(num_roots == 0)
  {
    if(power_eval(p, 0.5f) < 0.0)
    {
      *intervals = malloc(sizeof(float));
      (*intervals)[0] = interval_create(0, 1);
      return 1;
    }
    else
      return 0;
  }
  else
  {
    *intervals = malloc(sizeof(float) * (num_roots - 1));
    float last_dec_deriv = 0.0f;
    Power* deriv = power_derivative(p);
    
    for(int i = 0; i < num_roots; ++i)
    {
      if(power_eval(deriv, roots[i]) < 0.0f)
      {
	if(i == num_roots - 1)
	  (*intervals)[inserter++] = interval_create(roots[i], 1.0f);
	else
	  last_dec_deriv = roots[i];
      }
      else
      {
	(*intervals)[inserter++] = interval_create(last_dec_deriv, roots[i]);
      }
    }
    power_destroy(deriv);
  }
  
  return inserter;
}
