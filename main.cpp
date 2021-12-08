/*
 * Shree Murthy
 * 2374658
 * shmurthy@chapman.edu
 * CPSC 350-03
 * Assignment 6
 **/



#include "Simulation.h"

int main(int argc, char** argv){
   Simulation *s = new Simulation();
   s->run();
   delete s;
}