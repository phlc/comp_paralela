#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
//#include <omp.h>


//Definições
#define FILENAME "dataSet.in"
#define NPOINTS 100
#define DIMENSIONS 2
#define NCLUSTERS 8

//Estrutura para um ponto
typedef struct
{
    double coords[DIMENSIONS];
    int cluster;
}point;

typedef struct
{
    double centroide[DIMENSIONS];
    point* clusterPoints[NPOINTS];
    int nClusterPoints;
}cluster;


//Variáveis Globais
point allPoints[NPOINTS];
cluster allClusters[NCLUSTERS];


void print_point(point p){
    printf("Cluster: %d | Coords: (", p.cluster);
    for(int i=0; i<DIMENSIONS-1; i++)
        printf("%.2lf, ", p.coords[i]);
    printf("%.2lf)\n", p.coords[DIMENSIONS-1]);
}

void print_allPoints(){
    for(int i=0; i<NPOINTS; i++)
        print_point(allPoints[i]);
}

void print_clusters(){
    for(int i=0; i<NCLUSTERS; i++){
        printf("---------- Cluster %d ----------\nCentroid: (", i);
        for(int j=0; j<DIMENSIONS-1; j++){
            printf("%.2lf, ", allClusters[i].centroide[j]);
        }
        printf("%.2lf)\n", allClusters[i].centroide[DIMENSIONS-1]);
        for(int j=0; j<allClusters[i].nClusterPoints; j++){
            print_point(*allClusters[i].clusterPoints[j]);
        }
    }
}

void reset_clusters(){
    for(int i=0; i<DIMENSIONS; i++)
        allClusters[i].nClusterPoints=0;
}

double calcDistance(int p, int c){
    double distance  = 0.0;

    for(int i=0; i<DIMENSIONS; i++)
        distance += pow(allPoints[p].coords[i]-allClusters[c].centroide[i], 2);

    return sqrt(distance);
}

void assignCluster(int* change){
    //Resetar Clusters
    reset_clusters();

    //Verificar Cluster mais perto
    for(int i=0; i<NPOINTS; i++){
        int closestCluster = -1;
        double distance = DBL_MAX;

        //Calcular menor distância do cluster
        for(int j=0; j<NCLUSTERS; j++){
            double newDistance = calcDistance(i, j);
            if(newDistance < distance){
                distance = newDistance;
                if(allPoints[i].cluster != j)
                    *change = 1;
                allPoints[i].cluster = j;
                closestCluster = j;
            }
        }

        //Adicionar ponto no cluster
        allClusters[closestCluster].clusterPoints[allClusters[closestCluster].nClusterPoints] = &allPoints[i];
        allClusters[closestCluster].nClusterPoints++;
    }
}

void kmeans(){
    int hadChange = 1;

    //Repetir enquanto houver mudança
    while(hadChange){
        hadChange = 0;

        assignCluster(&hadChange);

        //if(hadChange)
            //recalcCentroide();
    }
}


int main() {
    //Declarações
    FILE *fp;

    //Abrir arquivo
    fp = fopen(FILENAME, "r");

	//Testar abertura arquivo
    if (fp == NULL) return 1;	
    
	//Ler pontos do arquivo	
    for (int i = 0; i < NPOINTS; i++) {
        allPoints[i].cluster = -1;
		for (int j = 0; j < DIMENSIONS; j++){
			fscanf(fp, "%lf", &allPoints[i].coords[j]);
        }
    }

    //Inicializar Clusters
    for(int i=0; i<NCLUSTERS; i++){
        for(int j=0; j<DIMENSIONS; j++)
            allClusters[i].centroide[j] = allPoints[i].coords[j];
        allClusters[i].nClusterPoints = 0;
    }

    //Obter Clusters
    kmeans();

    //Mostrar Clusters
    print_clusters();
	
    //Fechar arquivo
    fclose(fp);

	return 0;
}
