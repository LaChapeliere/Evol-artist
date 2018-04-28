//
//  FitnessFunctions.hpp
//  Evol'artist
//
//  Created by Emma Barme on 22/04/2018.
//  Copyright © 2018 LaChapeliere. All rights reserved.
//

#ifndef FitnessFunctions_hpp
#define FitnessFunctions_hpp

#include <map>
#include <string>
#include <functional>
#include <vector>

class FitnessFunctions {
private:
    /*
     * Map between genes and fitness functions
     */
    std::map<std::string, std::function<int(std::map<std::string, int>)>> m_fitnessFunctions;
    
    
public:
    /**
     * FitnessFunctions constructor
     */
    FitnessFunctions();
    
    /**
     * Compute the fitness of a genome
     * @param genome List of genes
     * @param env A dictionnary describing the environment
     * @return The fitness of the genome between 0 and 100
     */
    int getFitness(std::vector<std::string> genome, std::map<std::string, int> env) const;
};

#endif /* FitnessFunctions_hpp */

