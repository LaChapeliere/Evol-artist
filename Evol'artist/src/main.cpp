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
#include <ctime>
#include "simulEngine/World.hpp"
#include "simulEngine/FitnessFunctions.hpp"
using namespace std;

int main(){
    
    srand ((unsigned int)time(NULL));
    
    cout << "Hello World!" << endl;
    
    std::string testGenome =  "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";
    
    std::map<std::string, std::pair<int, int>> globalEnv;
    globalEnv.insert(std::make_pair("test", std::make_pair(50, 10)));
    globalEnv.insert(std::make_pair("test2", std::make_pair(45, 0)));
    
    std::clock_t start;
    double now;
    
    World myWorld(4, 100, testGenome, globalEnv);
    start = std::clock();
    
    for (int i = 0; i < 20; i++) {
        myWorld.runSimulationStep();
        now = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        std::cout << "STEPP//" << (i+1) 
				  //<< "//NBCREATURES//"  << myWorld.getNbCreatures() 
				  << "//TIME//" << now 
				  //<< "//%GENE//"<< myWorld.getPercentageGene("CC") 
				  << "//" << std::endl;
		int lol = myWorld.getNbCreatures();
		std::cout << "//NB CREATUR TOTALL//" << lol << "//" << std::endl << std::endl;
        //std::cout << "PERCENTAGEGENE/" << myWorld.getPercentageGene("CC") << std::endl;
    }
    
    cout << "Goodbye World!" << endl;
    
    return 0;
    
}
