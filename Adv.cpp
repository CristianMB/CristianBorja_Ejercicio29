#include <stdio.h>
#include <omp.h>
#include <array>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
using namespace std;

void Output(double *x, double *u, string file)
{
  ofstream myfile;
  myfile.open(file + ".dat");

  for (int i = 0; i < N; i++)
  {
    myfile << x[i] << " ";
  }

  myfile << endl;

  for (int i = 0; i < N; i++)
  {
    myfile << u[i] << " ";
  }

  myfile << endl;

  myfile.close();
}


double flux(double u)
{
  return 0.5*u*u;
}

float dx = 0.05;
double L = 4.0;
int N = (int)(L+dx)/dx;

void Lax(double *u, double t_max, double dt)
{
  int N_T = (int)(t_max/dt);
  double F[N];
  double u_copy[N];
  copy(u, u + N, u_copy);

  cout << N_T << " " << t_max << " " << dt<< " "<< endl;
  for (int m = 0; m < N_T; m++)
  {
    for (int k = 0; k < N; k++)
    {
      F[k] = flux(u[k]);
    }
    for (int j = 1; j < N - 1; j++)
    {
      u_copy[j] = 0.5*(u[j+1]+u[j-1]);
      u_copy[j] -= (0.5*dt/dx)*(F[j+1]-F[j-1]);
    }
      copy(u_copy, u_copy + N, u);
  }
}

void CIN(double *x, double *u)
{
  for (int i = 0; i < N; i++)
  {
    double x_t = (L/(N-1))*i;
    x[i] = x_t;
    if (x_t < 2.0)
    {
      u[i] = 1.0;
    }
    else
    {
      u[i] = 0.0;
    }
  }
}


main(int argc, char const *argv[])
{
  cout<<N<<endl;
  double x[N];
  double u[N];

  double t_max_values[4] = {0.0, 0.5, 1.0, 2.0};
  for (int i = 0; i < 4; i++)
  {
    CIN(x, u);
    Lax(u, t_max_values[i], 0.5 * dx);
    Output(x, u, to_string(i));
  }
  return 0;
}
