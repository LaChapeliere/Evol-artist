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
    std::map<std::string, std::function<int()>> m_fitnessFunctions;
    
public:
    /**
     * FitnessFunctions constructor
     */
    FitnessFunctions();
    
    /**
     * m_fitnessFunctions accessor
     * @param gene The gene to fetch the fitness function for
     * @return m_fitnessFunctions[gene]
     */
    std::function<int()> getFitnessFunction(std::string gene) const;
};

#endif /* FitnessFunctions_hpp */

