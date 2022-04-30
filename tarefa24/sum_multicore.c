#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
  int width = 40000000;

  double sum = 0.0;
  double *a = (double*) malloc (sizeof(double)*width);

  for(int i = 0; i < width; i++)
     a[i] = i;  

  #pragma omp parallel for reduction(+: sum)
  for(int i = 0; i < width ; i++){
     sum += a[i];
  }

  printf("\nSum = %f\n",sum);
  
  free(a);
}
