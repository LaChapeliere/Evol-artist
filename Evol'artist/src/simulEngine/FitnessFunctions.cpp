//
//  FitnessFunctions.cpp
//  Evol'artist
//
//  Created by Emma Barme on 22/04/2018.
//  Copyright © 2018 LaChapeliere. All rights reserved.
//

#include "FitnessFunctions.hpp"


FitnessFunctions::FitnessFunctions() {
    
    m_fitnessFunctions.insert(std::make_pair("BB", [] (std::map<std::string, int> env) { return 10; }));
    m_fitnessFunctions.insert(std::make_pair("BC", [] (std::map<std::string, int> env) { return 11; }));
    m_fitnessFunctions.insert(std::make_pair("BD", [] (std::map<std::string, int> env) { return 12; }));
    m_fitnessFunctions.insert(std::make_pair("CB", [] (std::map<std::string, int> env) { return 13; }));
    m_fitnessFunctions.insert(std::make_pair("CC", [] (std::map<std::string, int> env) { return 89; }));
    m_fitnessFunctions.insert(std::make_pair("CD", [] (std::map<std::string, int> env) { return 70; }));
    m_fitnessFunctions.insert(std::make_pair("DB", [] (std::map<std::string, int> env) { return 16; }));
    m_fitnessFunctions.insert(std::make_pair("DC", [] (std::map<std::string, int> env) { return 17; }));
    m_fitnessFunctions.insert(std::make_pair("DD", [] (std::map<std::string, int> env) { return 18; }));
    m_fitnessFunctions.insert(std::make_pair("BBB", [] (std::map<std::string, int> env) { return 20; }));
    m_fitnessFunctions.insert(std::make_pair("BBC", [] (std::map<std::string, int> env) { return 21; }));
    m_fitnessFunctions.insert(std::make_pair("BBD", [] (std::map<std::string, int> env) { return 22; }));
    m_fitnessFunctions.insert(std::make_pair("BCB", [] (std::map<std::string, int> env) { return 23; }));
    m_fitnessFunctions.insert(std::make_pair("BCC", [] (std::map<std::string, int> env) { return 64; }));
    m_fitnessFunctions.insert(std::make_pair("BCD", [] (std::map<std::string, int> env) { return 25; }));
    m_fitnessFunctions.insert(std::make_pair("BDB", [] (std::map<std::string, int> env) { return 26; }));
    m_fitnessFunctions.insert(std::make_pair("BDC", [] (std::map<std::string, int> env) { return 27; }));
    m_fitnessFunctions.insert(std::make_pair("BDD", [] (std::map<std::string, int> env) { return 28; }));
    m_fitnessFunctions.insert(std::make_pair("CBB", [] (std::map<std::string, int> env) { return 30; }));
    m_fitnessFunctions.insert(std::make_pair("CBC", [] (std::map<std::string, int> env) { return 31; }));
    m_fitnessFunctions.insert(std::make_pair("CBD", [] (std::map<std::string, int> env) { return 32; }));
    m_fitnessFunctions.insert(std::make_pair("CCB", [] (std::map<std::string, int> env) { return 33; }));
    m_fitnessFunctions.insert(std::make_pair("CCC", [] (std::map<std::string, int> env) { return 34; }));
    m_fitnessFunctions.insert(std::make_pair("CCD", [] (std::map<std::string, int> env) { return 35; }));
    m_fitnessFunctions.insert(std::make_pair("CDB", [] (std::map<std::string, int> env) { return 36; }));
    m_fitnessFunctions.insert(std::make_pair("CDC", [] (std::map<std::string, int> env) { return 37; }));
    m_fitnessFunctions.insert(std::make_pair("CDD", [] (std::map<std::string, int> env) { return 38; }));
    m_fitnessFunctions.insert(std::make_pair("DBB", [] (std::map<std::string, int> env) { return 40; }));
    m_fitnessFunctions.insert(std::make_pair("DBC", [] (std::map<std::string, int> env) { return 41; }));
    m_fitnessFunctions.insert(std::make_pair("DBD", [] (std::map<std::string, int> env) { return 42; }));
    m_fitnessFunctions.insert(std::make_pair("DCB", [] (std::map<std::string, int> env) { return 43; }));
    m_fitnessFunctions.insert(std::make_pair("DCC", [] (std::map<std::string, int> env) { return 44; }));
    m_fitnessFunctions.insert(std::make_pair("DCD", [] (std::map<std::string, int> env) { return 45; }));
    m_fitnessFunctions.insert(std::make_pair("DDB", [] (std::map<std::string, int> env) { return 46; }));
    m_fitnessFunctions.insert(std::make_pair("DDC", [] (std::map<std::string, int> env) { return 47; }));
    m_fitnessFunctions.insert(std::make_pair("DDD", [] (std::map<std::string, int> env) { return 48; }));
}

int FitnessFunctions::getFitness(std::vector<std::string> genome, std::map<std::string, int> env) const {
    int fitnessSum = 0;
    // Get the fitness function and compute fitness for each gene
    for (int i = 0; i < genome.size(); i++) {
        std::function<int(std::map<std::string, int>)> func = m_fitnessFunctions.at(genome[i]);
        int geneFitness = func(env);
        // If fitness is null, creature is dead
        if (geneFitness == 0) {
            return 0;
        }
        else {
            fitnessSum += geneFitness;
        }
    }
    
    // Compute mean of fitness
    int fitness;
    if (genome.size() == 0) {
        fitness = 0;
    }
    else {
        fitness = fitnessSum / genome.size();
    }
    return fitness;
}
