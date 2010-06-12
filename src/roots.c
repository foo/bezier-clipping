#include "roots.h"

// wzory viete'a

int bezier_quad_roots(Bezier* b, float** roots)
{
  assert(b);
  assert(b->n == 2);

  // quadratic polynomial coefficients in power basis
  float A = b->c[0] - 2*b->c[1] + b->c[2];
  float B = -2*b->c[0] + 2*b->c[1];
  float C = b->c[0];

  if(A == 0)
  {
    if(B == 0)
      return 0;
    else
    {
      float root = -C / B;
      if(b->a <= root && root <= b->b)
      {
	*roots = malloc(sizeof(float));
	(*roots)[0] = root;
	return 1;
      }
      else
	return 0;
    }
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
      float lroot = (-B - sqrtf(delta)) / (2*A) * (b->b - b->a) + b->a;
      float rroot = (-B + sqrtf(delta)) / (2*A) * (b->b - b->a) + b->a;
      
      if(lroot > rroot)
      {
	swap(&lroot, &rroot);
      }
      
      assert(lroot <= rroot);
      
      if(lroot == rroot)
      {
	if(lroot < b->a || lroot > b->b)
	  return 0;
	else
	{
	  *roots = malloc(sizeof(float));
	  (*roots)[0] = lroot;
	  return 1;
	}
      }
      else
      {
	if(lroot < b->a || lroot > b->b)
	{
	  if(rroot < b->a || rroot > b->b)
	  {
	    return 0;
	  }
	  else
	  {
	    *roots = malloc(sizeof(float));
	    (*roots)[0] = rroot;
	    return 1;
	  }
	}
	else
	{
	  if(rroot < b->a || rroot > b->b)
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
  }
}

int bezier_cubic_roots(Bezier* b, float** roots)
{
  
  return 0;
}

