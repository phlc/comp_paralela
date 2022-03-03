/*
Pedro Henrique Lima Carvalho
Matricula: 651230
Computação Paralela

Tarefa 9

Tempo do Programa Serial
real  0m4.366s
user  0m4.359s
sys   0m0.004s

Tempo do Programa Paralelo - Com collapse - Escalonamento Default
real  0m2.643s
user  0m4.896s
sys   0m0.004s

Tempo do Programa Paralelo - Sem collapse - Escalonamento Default
real  0m3.455s
user  0m6.342s
sys   0m0.008s

Tempo do Programa Paralelo - Sem collapse - Escalonamento Dynamic
real  0m28.193s
user  0m56.339s
sys   0m0.024s

Tempo do Programa Paralelo - Sem collapse - Escalonamento Guided
real  0m3.474s
user  0m6.354s
sys   0m0.020s

Melhor Speedup: 1,65

A melhor versão utilizou a diretiva collapse com escalonamento estatico.
No entanto, quanto utilizado escalonamento dinamico associado a diretiva
collapse, o codigo apresentou resposta incorreta, o que nos leva a concluir 
que o collapse criou uma dependencia de variaveis que, por sorte, nao gerou 
uma resposta errada nos escalonamentos estatico e guided. Concluimos que o 
tamanho do chunk influencia na ocorrencia do erro em razao dessa dependencia
das variaveis.
Como as cargas de cada iteracao sao iguais, nao faz sentido a utilizacao
de escalonamentos dinamicos, vez que geram overhead.
 

*/

#include <stdio.h>
#include <stdlib.h>

int main() 
{
   int i, j, n = 30000; 

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
   #pragma omp parallel for num_threads(2)
   for(i=0; i < n; i++) 
      #pragma omp parallel for num_threads(2)
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

