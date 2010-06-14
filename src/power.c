#include "power.h"

int power_linear_roots(Interval* b, float A, float B, float** roots)
{
  float root = -B / A;
  if(b->a <= root && root <= b->b)
  {
    *roots = malloc(sizeof(float));
    (*roots)[0] = root;
    return 1;
  }
  else
    return 0;

  return 0;
}

int power_quad_roots(Interval* b, float A, float B, float C, float** roots)
{
  if(A == 0)
  {
    // function is linear
    if(B == 0)
    {
      // function is constant
      return 0;
    }
    else
    {
      return power_linear_roots(b, B, C, roots);
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

int power_cubic_roots(Interval* b, float A, float B, float C, float D, float** roots)
{
  if(A == 0)
  {
    // function is quadratic
    if(B == 0)
    {
      // function is linear
      if(C == 0)
      {
	// function is constant
	return 0;
      }
      else
      {
	assert(0);
      }
    }
    else
    {
      assert(0);
    }
  }
  else
  {
    // function is not quadratic
    
  }
  return 0;
}

