#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){

    FILE* f = fopen("dataSet.in", "w");

    for(int i=0; i<atoi(argv[1]); i++){
        fprintf(f, "%.2lf %.2lf \n", ((double)(rand()%100000)/100), ((double)(rand()%100000)/100));
    }

}
