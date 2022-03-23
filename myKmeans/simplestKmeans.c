#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <time.h>
//#include <omp.h>


//Estrutura para um ponto
typedef struct
{
    double* coords;
    int cluster;
}point;

//Variáveis Globais
char filename[] = "dataSet.in";
int nPoints = 10000;
int dimensions = 2;
int nClusters = 8;
point* allPoints;
point** clusters;


void print_point(point p){
    printf("Cluster %d - Coords: ", p.cluster);
    for(int i=0; i<dimensions; i++)
        printf("%lf ", p.coords[i]);
    printf("\n");
}

void print_allPoints(){
    for(int i=0; i<nPoints; i++)
        print_point(allPoints[i]);
}


int main() {
    //Declarações
    FILE *fp;
		
	//Alocar vetor para todos os pontos
    allPoints = (point*) malloc(sizeof(point) * nPoints);

	//Testar abertura arquivo
    if ((fp = fopen(filename, "r")) == NULL) exit(1);
		
	//Ler pontos do arquivo	
    for (int i = 0; i < nPoints; i++) {
        allPoints[i].coords = (double*) malloc(sizeof(double) * dimensions); 
        allPoints[i].cluster = -1;
		for (int j = 0; j < dimensions; j++){
			fscanf(fp, "%lf", &allPoints[i].coords[j]);
        }
    }
	
    //Fechar arquivo
    fclose(fp);

	print_allPoints();

	return 0;
}
