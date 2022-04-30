#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
  int width = 40000000;


  int w2 = (int) pow(2, floor(log2((double) width))+1);

  double *a = (double*) malloc (sizeof(double)*width);

  for(int i = 0; i < width; i++)
     a[i] = i;  

  for(int i = w2/2; i > 0 ; i/=2){
     #pragma omp parallel for 
     for(int j=0; j<i; j++){
        if(j+i < width)
           a[j] += a[j+i];
     }
  }

  printf("\nSum = %f\n",a[0]);
  
  free(a);
}
