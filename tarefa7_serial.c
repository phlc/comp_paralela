/*
Pedro Henrique Lima Carvalho
Matricula: 651230
Computação Paralela

Tarefa 7

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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int sieveOfEratosthenes(int n)
{
   // Create a boolean array "prime[0..n]" and initialize
   // all entries it as true. A value in prime[i] will
   // finally be false if i is Not a prime, else true.
   int primes = 0; 
   bool *prime = (bool*) malloc((n+1)*sizeof(bool));
   int sqrt_n = sqrt(n);

   memset(prime, true,(n+1)*sizeof(bool));

   for (int p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       if (prime[p] == true)
       {
           // Update all multiples of p
           for (int i=p*2; i<=n; i += p)
           prime[i] = false;
        }
    }

    // count prime numbers
    for (int p=2; p<=n; p++)
       if (prime[p])
         primes++;

    return(primes);
}

int main()
{
   int n = 100000000;
   printf("%d\n",sieveOfEratosthenes(n));
   return 0;
} 
