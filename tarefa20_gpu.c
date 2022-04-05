/*
Pedro Henrique Lima Carvalho
Matricula: 651230
Computação Paralela

Tarefa 20

Tempo com tamanho origial de n=30000

Tempo do Programa Serial
real  0m1.513s
user  0m1.511s
sys   0m0.000s

Tempo do Programa Paralelo
real  0m0.531s
user  0m1.560s
sys   0m0.004s

Tempo do Programa GPU
real  0m1.060s
user  0m0.160s
sys   0m0.811s

Obs: O overhead de mandar para a GPU não compensa com o tamanho do arranjo

---------------------

Tempo com tamanho aumentado para n=90000

Tempo Programa Serial
real  0m13.554s
user  0m13.548s
sys   0m0.000s

Tempo Programa Paralelo CPU
real  0m9.914s
user  0m26.889s
sys   0m0.004s

Tempo Programa GPU
real  0m2.148s
user  0m0.973s
sys   0m1.092s

Speedup em relação ao Serial: 6.31
Speedup em relação ao Paralelo CPU: 4,61 



*/

#include <stdio.h>
#include <stdlib.h>

int main() 
{
   int i, j, n = 90000; 


   // Allocate input, output and position arrays
   int *in = (int*) calloc(n, sizeof(int));
   int *pos = (int*) calloc(n, sizeof(int));   
   int *out = (int*) calloc(n, sizeof(int));   

   // Initialize input array in the reverse order
   for(i=0; i < n; i++)
      in[i] = n-i;  

   // Print input array
   //   for(i=0; i < n; i++) 
   //      printf("%d ",in[i]);
    
   // Silly sort (you have to make this code parallel)
   #pragma omp target map(tofrom: pos[0:n]) map(to: in[0:n])
   #pragma omp teams distribute parallel for simd
   for(i=0; i < n; i++) 
      for(j=0; j < n; j++)
        if(in[i] > in[j]) 
            pos[i]++;   

   // Move elements to final position
   for(i=0; i < n; i++) 
      out[pos[i]] = in[i];
   
   // print output array
   //   for(i=0; i < n; i++) 
   //      printf("%d ",out[i]);

   // Check if answer is correct
   for(i=0; i < n; i++)
      if(i+1 != out[i]) 
      {
         printf("test failed\n");
         exit(0);
      }

   printf("test passed\n"); 
}  

