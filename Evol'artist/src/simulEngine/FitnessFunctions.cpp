//
//  FitnessFunctions.cpp
//  Evol'artist
//
//  Created by Emma Barme on 22/04/2018.
//  Copyright © 2018 LaChapeliere. All rights reserved.
//

#include "FitnessFunctions.hpp"


FitnessFunctions::FitnessFunctions() {
    
    m_fitnessFunctions.insert(std::make_pair("BB", [] () { return 0; }));
}

std::function<int()> FitnessFunctions::getFitnessFunction(std::string gene) const {
    return m_fitnessFunctions.at(gene);
}
