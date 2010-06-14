#include "utils.h"

float min(float a, float b) { return (a < b) ? a : b; }
float max(float a, float b) { return (a < b) ? b : a; }
void swap(float* a, float* b)
{
  float tmp = *a;
  *a = *b;
  *b = tmp;
}

float gammln(const float xx)
{
  int j;
  float x,tmp,y,ser;
  static const float cof[14]={57.1562356658629235,-59.5979603554754912,
			      14.1360979747417471,-0.491913816097620199,.339946499848118887e-4,
			      .465236289270485756e-4,-.983744753048795646e-4,.158088703224912494e-3,
			      -.210264441724104883e-3,.217439618115212643e-3,-.164318106536763890e-3,
			      .844182239838527433e-4,-.261908384015814087e-4,.368991826595316234e-5};
  if (xx <= 0) return -1;
  y=x=xx;
  tmp = x+5.24218750000000000;
  tmp = (x+0.5)*log(tmp)-tmp;
  ser = 0.999999999999997092;
  for (j=0;j<14;j++) ser += cof[j]/++y;
  return tmp+log(2.5066282746310005*ser/x);
}


float factrl(const int n)
{
  static float a[171];
  static int init = 1;
  if (init)
  {
    init = 0;
    a[0] = 1.;
    for (int i=1;i<171;i++) a[i] = i*a[i-1];
  }
  if (n < 0 || n > 170) return -1;
  return a[n];
}

float factln(const int n)
{
  static float a[2000];
  static int init = 1;
  if (init)
  {
    init = 0;
    for (int i=0; i<2000; i++)
      a[i] = gammln(i+1.);
  }
  if (n < 0) return -1;
  if (n < 2000) return a[n];
  return gammln(n+1.);
}

float bico(const int n, const int k)
{
  if (n<0 || k<0 || k>n) return -1;
  if (n<171) return floor(0.5+factrl(n)/(factrl(k)*factrl(n-k)));
  return floor(0.5+exp(factln(n)-factln(k)-factln(n-k)));
}

int up_power(const int x, const int up)
{
  int t = 1;
  for(int i = x; i < x + up; ++i)
    t*=i;
  return t;
}

const float PI = 3.1415692f;
