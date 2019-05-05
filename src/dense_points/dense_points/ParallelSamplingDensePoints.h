#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "sample.h"

#define N_THREADS 2
#define WIDTH 500
#define HEIGHT 500

#include <vector>

using namespace std;

vector<Sample*> cloud; //dense points cloud
vector<int> pointIndex;
vector<Sample*> actives;
vector<Sample*> idles;
vector<vector<Sample*>> grid; //inicializar el grid !!!

int numberPoints;
double r = 5;
double size = r/sqrt(2);
int cols = WIDTH/size;
int fils = HEIGHT/size;

struct parallel_data {
    int ini;
    int fin;
};
void* parallel_generateDP(void* arg) {
    
    parallel_data* data1 = (parallel_data*) arg;
    
    for (int i = data1->ini; i < data1->fin; ++i) {
        Sample* sample = new Sample();
        sample->pos[0] = rand()%WIDTH;  //numeros aleatorios entre 0 y 500
        sample->pos[1] = rand()%HEIGHT;
        sample->status = "IDLE";
        cloud.push_back(sample);
        //agregar al grid cell correspondiente
        int i = sample->pos[0]/size;
        int j = sample->pos[1]/size;
        int id_grid_cell = i + j * cols;
        grid[id_grid_cell].push_back(sample);
        
    }
    
    return NULL;
};

class ParallelSamplingDensePoints {
    
    pthread_t hilos[N_THREADS];
    
    srand(time(NULL));
    
    void generateDensePoints() {
        for (int i = 0; i < N_THREADS; ++i) {
            int ini = i * 250;
            int fin = (i+1) * 250;
            parallel_data* args = new parallel_data();
            args->ini = fin;
            args->fin = fin;
            pthread_create(&hilos[i], NULL, parallel_generateDP, (void*) args);
        }
    }
    
    void checkStatus(Sample* sample){
        
    }
};
