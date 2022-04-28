#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
Ana Laura Fernandes de Oliveira
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho
Pedro Henrique Reis Rodrigues
Tárcila Fernanda Resende da Silva


Tarefa 22

Tempo do Programa Serial
real  1m50.604s
user  1m15.349s
sys   0m0.108s

Tempo do Programa Paralelo CPU
real  0m40.297s
user  1m11.810s
sys   0m0.315s

Tempo do Programa Paralelo GPU
real  0m16.489s
user  0m8.802s
sys   0m2.857s

Speedup Paralelo GPU em relação Paralelo CPU: 2,44

Métricas da Nvdia
Invocations                                Event Name         Min         Max         Avg       Total
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                            warps_launched      155832      155832      155832      155832

==11722== Metric result:
Invocations                               Metric Name                        Metric Description         Min         Max         Avg
Device "GeForce GT 1030 (0)"
    Kernel: mm$_omp_fn$0
          1                 warp_execution_efficiency                 Warp Execution Efficiency      86.81%      86.81%      86.81%



*/



void mm(double* a, double* b, double* c, int width) 
{
   #pragma omp target map(to: a[0:width*width], b[0:width*width]), map(tofrom: c[0:width*width])
   #pragma omp teams distribute parallel for simd
   for (int i = 0; i < width; i++) {
      for (int j = 0; j < width; j++) {
         double sum = 0;
         for (int k = 0; k < width; k++) {
	         double x = a[i * width + k];
	         double y = b[k * width + j];
	         sum += x * y;
         }
         c[i * width + j] = sum;
      }
   }
}

int main()
{
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

//    for(int i = 0; i < width; i++) {
//    for(int j = 0; j < width; j++) {
//      printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
//    }
//   }
}
