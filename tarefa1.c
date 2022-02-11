/*
*  Computacao Paralela
*  Pedro Henrique Lima Carvalho
*  651230
*/


#include <stdio.h>
#include <omp.h>


/*
   Na linha 39 duas threads são abertas, compartilhando a
   variável 'i'. Como a variável 'tid' é criada dentro das
   threads, cada uma tem a sua.
   
   O 'for' tem a diretiva 'omp for ordered' de forma que as 
   instruções vinculadas a diretiva 'omp ordered' (linha 46) 
   serão executadas em ordem. Assim, eventuais tarefas 
   realizadas em paralelo pelas threads dentro do 'for' antes
   da diretiva 'omp ordered;, somente prosseguirão em ordem. 
   
   Não é o cado do código, mas eventuais tarefas já finalizadas
   pelas threads aguardam sua ordem para prosseguimento.
   
   Apesar de ambas as threads poderem ler o mesmo valor de 'i',
   'omp ordered' se assegura que o mesmo bloco não seja executado
   mais de uma vez na mesma iteração.

   No caso, não há, realmente, qualquer trabalho a ser executado 
   em paralelo, de forma que não há speedup possível.
   
*/

int main()
{
    int i;

   #pragma omp parallel num_threads(2) // seta o número de threads em 2 
   {
      int tid = omp_get_thread_num(); // lê o identificador da thread  
    
      #pragma omp for ordered
      for(i = 1; i <= 3; i++) 
      {
         #pragma omp ordered
         {
            printf("[PRINT1] T%d = %d \n",tid,i);
            printf("[PRINT2] T%d = %d \n",tid,i); 
         }
       }
   }
}
