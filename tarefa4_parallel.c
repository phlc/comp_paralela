#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
Pedro Henrique Lima Carvalho
Matricula: 651230
Computação Paralela

Tarefa 4

Tempo do Programa Serial
real  2m19.579s
user  2m18.938s
sys   0m0.480s

Tempo do Programa Paralelo com 'collapse(2)'
real  0m37.176s  Speedup 3,75
user  2m28.241s
sys   0m0.140s

Tempo do Programa Paralelo com dois 'parallel for'
real  0m43.765s  Speedup 3,18
user  2m53.656s
sys   0m0.132s

O programa abaixo utiliza a diretiva 'omp parallel for collaps(2), de forma que 
o compilador realiza uma 'junção' (collapse) dos dois for e divide as iterações 
entre as threads. Isso é possível vez que a contagem de um for não depende do
outro. A partir do collapse, a divisão atua como um 'omp parallel for' em um 
único for.

Também foi realizado um teste com dois 'omp parallel for' obtendo considerável 
speedup em relação ao cógido serial, mas com menor desempenho que utilizando 
'collapse';

A parelização é bastante eficiente vez que as operaçõe realizadas a partir do 
terceiro for (variável k) são independentes uma das outras em relação aos 'for'
de variáveis 'i' e  'j'. Cada multiplicação e soma dos elementos das linhas 'i'
e colunas 'j' das matrizes são completamente independentes das operações das 
outras linhas e colunas.

*/



void mm(double* a, double* b, double* c, int width) 
{
   //#pragma omp parallel for
   #pragma omp parallel for collapse(2)
   for (int i = 0; i < width; i++) {
      //pragma omp parallel for
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

    for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
    }
   }
}
