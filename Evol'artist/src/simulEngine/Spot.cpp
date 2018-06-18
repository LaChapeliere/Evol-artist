//
//  Spot.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017


#include "Spot.hpp"
#include "World.hpp"

Spot::Spot(World* world, const int x, const int y): m_world(world), m_x(x), m_y(y) {
    // FOR NOW
    // Create basic env
    m_env.insert(std::make_pair("global", 1));
}

const int Spot::getNbCreatures() const {
    return (int)m_creatures.size();
}

Creature* Spot::getCreatureFromIndex(const int id) const {
    return m_creatures[id];
}

std::map<std::string, int> Spot::getEnv() const {
    return m_env;
}

void Spot::addCreature(Creature *const creaturePointer) {
    m_creatures.push_back(creaturePointer);
}

void Spot::removeCreature(const int id) {
    for (int c = 0; c < m_creatures.size(); c++) {
        if (m_creatures[c]->getId() == id) {
            m_creatures.erase(m_creatures.begin() + c);
            return;
        }
    }
    std::cout << "Trying to remove unexisting Creature from Spot" << std::endl;
}

void Spot::nextStepPop() {
    // Create new generation
    std::vector<Creature*> newGeneration;
    
    // Get random order of creatures
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(m_creatures), std::end(m_creatures), rng);
    
    // For each creature decide if reproduction
    Creature* firstParent = nullptr;
    Creature* secondParent = nullptr;
    for (int i = 0; i < m_creatures.size(); i++) {
        int dice = rand() % 101;
        int fitness = m_creatures[i]->getFitness();
        if (dice < fitness) {
            if (firstParent == nullptr) {
                firstParent = m_creatures[i];
            }
            else {
                secondParent = m_creatures[i];
                //Four offsprings
                for (int i = 0; i < 4; i++) {
                    newGeneration.push_back(sexualReproduction(firstParent, secondParent));
                }
                firstParent = nullptr;
                secondParent = nullptr;
            }
        }
    }
    
    //Remove old generation
    m_creatures.clear();
    
    // Distribute new generation between this spot and its neighbours
    // TODO: Add the move to neighbours
    for (int i = 0; i < newGeneration.size(); i++) {
        int xModifier = rand() % 3 - 1;
        int yModifier = rand() % 3 - 1;
        int xReal = (m_x + xModifier + m_world->getSize()) % m_world->getSize();
        int yReal = (m_y + yModifier + m_world->getSize()) % m_world->getSize();
        m_world->getPointerToSpot(xReal, yReal)->addCreature(newGeneration[i]);
    }
}


Creature* Spot::asexualReproduction(Creature* parent) {
    // New creature in the same spot
    std::pair<int, int> parentCoords = parent->getCoord();
    
    // Genome is that of parent plus mutation step
    std::string genome = parent->getGenome();
    const int i = 100000;
    for (char c = 0; c < genome.size(); c++) {
        int r = rand() % i;
        if (r <= m_world->getMutationRate() * i) {
            //Mutation
            std::vector<char> bases = m_world->getPossibleBases();
            const int newBase = bases[rand() % bases.size()];
            genome[c] = newBase;
        }
    }
    
    return new Creature(m_world->getNewCreatureId(), genome, parentCoords.first, parentCoords.second, m_env);
}

Creature* Spot::sexualReproduction(Creature* firstParent, Creature* secondParent) {
    std::pair<int, int> parentCoords = firstParent->getCoord();
    
    // Genome is that of combination of parents plus mutation step
    std::vector<std::string> parentGenomes;
    parentGenomes.push_back(firstParent->getGenome());
    parentGenomes.push_back(secondParent->getGenome());
    int selectedParent = 0;
    std::string genome = "";
    const int i = 100000;
    for (char c = 0; c < parentGenomes[selectedParent].size(); c++) {
        // Copy selected parent genome
        char base = parentGenomes[selectedParent][c];
        genome += base;
        
        int r = rand() % i;
        if (r <= m_world->getCrossoverRate() * i) {
            // Crossover
            // Change the selected parent genome
            selectedParent = (selectedParent + 1) % 2;
        }
        
        r = rand() % i;
        if (r <= m_world->getMutationRate() * i) {
            //Mutation
            std::vector<char> bases = m_world->getPossibleBases();
            const int newBase = bases[rand() % bases.size()];
            genome[c] = newBase;
        }
    }
    
    return new Creature(m_world->getNewCreatureId(), genome, parentCoords.first, parentCoords.second, m_env);
}

