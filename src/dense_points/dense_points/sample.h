#ifndef sample_h
#define sample_h
#include <iostream>

using namespace std;
struct Sample {
    double prioridad;
    int pos[2] = {0};  // pos 0 <- x y pos 1 <- y
    string status;
    //no estoy seguro de usar id_grid_cell
    int id_grid_cell;   //face_id
};

#endif /* sample_h */
