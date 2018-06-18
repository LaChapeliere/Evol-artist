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
    
    std::string testGenome =  "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";
    
    World myWorld(4, 250, testGenome);
    for (int i = 0; i < 100; i++) {
        myWorld.runSimulationStep();
        std::cout << myWorld.getPercentageGene("CC") << std::endl;
    }
    
    cout << "Goodbye World!" << endl;
    
    return 0;
    
}
