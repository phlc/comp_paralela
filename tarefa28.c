/*
Ana Laura Fernandes de Oliveira
Larissa Domingues Gomes
Pedro Henrique Lima Carvalho
Pedro Henrique Reis Rodrigues
*/



#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define PIPE_MSG 0  
#define END_MSG 1  

int size;  
int n;     
int rank;  

void removeMultipleOf3() {  
   int number, i;

   for (i = 1; i <= n/2; i++)  {
      number = 2 * i + 1;
      if (number > n) break;
      if (number % 3 > 0)
         MPI_Send(&number,1,MPI_INT,1,PIPE_MSG,MPI_COMM_WORLD);
   }
   MPI_Send(&number,1,MPI_INT,1,END_MSG,MPI_COMM_WORLD);
}

void removeMultipleOf5() {  	
   int number, i=0;
   MPI_Status Status; 
	
   while (1)  {
     MPI_Recv(&number,1,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&Status);
     if (Status.MPI_TAG == END_MSG) break;
     if (number % 5 > 0) {
      int proximo = (i % (size -2)+2);
      i++; 
       // enviar para o próximo estágio
      MPI_Send(&number,1,MPI_INT,proximo,PIPE_MSG,MPI_COMM_WORLD);
     }
   }
   // enviar mensagem de finalização
   for(i=2;i<size; i++){
      MPI_Send(&number,1,MPI_INT,i,END_MSG,MPI_COMM_WORLD);
   }
}

void countOnlyPrimes() {

   int number, primeCount, i, isComposite;
   MPI_Status Status; 

   primeCount = 0;  

   while (1)  {
      // receber mensagem do estágio anterior
      // sair do loop se fim
     MPI_Recv(&number,1,MPI_INT,1,MPI_ANY_TAG,MPI_COMM_WORLD,&Status);
     if (Status.MPI_TAG == END_MSG) break;
      
      isComposite = 0;
      for (i = 7; i*i <= number; i += 2)
        if (number % i == 0)  {
	      isComposite = 1;
	      break;
	    }
      
	  if (!isComposite) primeCount++;  
   }

    MPI_Send(&primeCount,1,MPI_INT,0,END_MSG,MPI_COMM_WORLD);
 
}

void reduce(){
   int i, subtotal = 0;
   int primeCount = 3;
   MPI_Status Status;
   for (int i=2; i<size; i++){
      MPI_Recv(&subtotal,1,MPI_INT,i,MPI_ANY_TAG,MPI_COMM_WORLD,&Status);
      primeCount += subtotal;

}
   printf("number of primes: %i\n", primeCount); 
}

void main(int argc, char **argv) {  

   n = atoi(argv[1]); 
   MPI_Init(&argc,&argv);	

   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank); 

   switch (rank)  {
      case 0:  removeMultipleOf3();
               reduce();
	  break;
      
	  case 1:  removeMultipleOf5();
      break;
      
      default: countOnlyPrimes();
      break;
   };

   MPI_Finalize();
}
