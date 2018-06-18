//
//  main.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017


//main function for tests

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "simulEngine/World.hpp"
#include "simulEngine/FitnessFunctions.hpp"
using namespace std;

int main(){
    
    srand ((unsigned int)time(NULL));
    
    cout << "Hello World!" << endl;
    /*
    // Run the simulation. No insight on what's happening in the back box for now
    World myWorld(1000, 10);
    for (int t = 0; t < 200; t++) {
        myWorld.runSimulationStep();
        std::cout << "Turn " << t << " with " << myWorld.getNbCreatures() << " creatures alive" << std::endl;
        if (myWorld.getNbCreatures() == 0) {
            std::cout << "Oh no! They're all dead :'(" << std::endl;
            break;
        }
    }*/
    //FitnessFunctions f = FitnessFunctions();
    World myWorld(2, 30);
    for (int i = 0; i < 100; i++) {
        myWorld.runSimulationStep();
    }
    cout << "Hello" << endl;
    
    return 0;
    
}
