#include "reduction.h"

float** bezier_reduction_matrix(int n, int m)
{
  assert(n > m);

  float (*psi)[n+1] = malloc(sizeof(float) * (m + 1) * (n + 1));

  float C = factrl(n)*up_power(1-n, m)
    / (factrl(m)*up_power(m+2, n));

  // 0,0
  {
    psi[0][0] = 0;
    for(int h = 0; h <= m; ++h)
    {
      float t = bico(m,h) * up_power(m+2,h) / ((h-n)*factrl(h));
      if(h % 2 != 0)
	t *= -1;
      psi[0][0] += t;
    }
    psi[0][0] *= -n*C;
  }

  // 0,1
  {
    psi[0][1] = (m+1)*C;
    if(m%2 != 0)
      psi[0][1] *= -1;
  }

  // pierwszy wiersz
  {
    for(int j = 1; j <= n - 1; ++j)
    {
      float F = ((float)((j-1)*(n-j+1)))/((float) ((n-j)*(j+1)));
      float E = 1. + F - ((float)(m*(m+2)))/((float) ((n-j)*(j+1)));

      psi[0][j+1] = E*psi[0][j] - F*psi[0][j-1];
    }
  }

  // reszta tablicy
  {
    for(int i = 0; i <= m - 1; ++i)
    {
      for(int j = 0; j <= n; ++j)
      {
	float Anj = j*(j-n-1);
	float Ami = i*(i-m-1);
	float Bnj = (j-n)*(j+1);
	float Bmi = (i-m)*(i+1);
	float Cnj = Anj + Bnj;
	float Cmi = Ami + Bmi;

	float pp0m1 = ((j - 1) < 0) ? 0 : psi[i][j-1];
	float pp0p0 = psi[i][j];
	float pm1p0 = ((i - 1) < 0) ? 0 : psi[i-1][j];
	float pp0p1 = ((j + 1) > n) ? 0 : psi[i][j+1];

	psi[i+1][j] = (Anj*pp0m1 + (Cmi-Cnj)*pp0p0 +
	  Bnj*pp0p1 - Ami*pm1p0) / Bmi;
      }
    }
  }

  return (float**)psi;
}

Bezier* bezier_degree_reduction(Bezier* c, int m, float **reduction_matrix)
{
  int n = c->n;

  Bezier* low = bezier_create(m);
  low->a = c->a;
  low->b = c->b;
  
  float (*psi)[n+1] = (float(*)[])reduction_matrix;
  float (*e) = malloc(sizeof(float) * (n + 1));

  for(int i = 0; i <= m; ++i)
  {
    e[i] = 0;
    for(int j = 0; j <= n; ++j)
      e[i] += c->c[j]*psi[i][j];
  }

  for(int i = 0; i <= m; ++i)
  {
    low->c[i] = e[i];
  }

  free(e);
  
  return low;
}
