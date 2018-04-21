//
//  World.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017

#include "World.hpp"

World::World(const int size, const int nbCreatures): m_size(size) {
    m_age = 0;
    m_incubationTime = 0;
    m_lastCreatureId = -1;
    m_bases.push_back('B');
    m_bases.push_back('C');
    m_bases.push_back('D');
    
    //Create grid of Spots
    for (int y = 0; y < m_size; y++) {
        for (int x = 0; x < m_size; x++) {
            m_grid.push_back(Spot(x, y));
        }
    }
    
    //Add the Creatures in the grid
    for (int i = 0; i < nbCreatures; i++) {
        //addCreature();
    }
}

const int World::getSize() const {
    return m_size;
}

const int World::getAge() const {
    return m_age;
}

const int World::getIncubTime() const {
    return m_incubationTime;
}

const int World::getNbCreatures() const {
    return (int)m_creatures.size();
}

Spot const* World::getPointerToSpot(const int x, const int y) const {
    return &(m_grid[y * m_size + x]);
}

void World::addCreature(const int x, const int y) {
    //Create creature
    m_lastCreatureId++;
    Creature* creaturePtr = new Creature(m_lastCreatureId, "ABBOABCBO", x, y);
    m_creatures.push_back(creaturePtr);
    
    //Add creature to grid
    m_grid[x + y * m_size].addCreature(creaturePtr);
}

void World::removeCreature(const int creatureId) {
    //Find creature in grid
    std::pair<int, int> coord;
    int indexInMCreatures = -1;
    Creature* creaturePtr = NULL;
    for (int i = 0; i < m_creatures.size(); i++) {
        if (creatureId == m_creatures[i]->getId()) {
            coord = m_creatures[i]->getCoord();
            indexInMCreatures = i;
            creaturePtr = m_creatures[i];
            break;
        }
    }
    
    //If creature was found
    if (creaturePtr != NULL) {
        const int x = coord.first;
        const int y = coord.second;
        
        //Remove from grid
        m_grid[x + y * m_size].removeCreature(creatureId);
        
        //Remove from world
        m_creatures.erase(m_creatures.begin() + indexInMCreatures);
        delete creaturePtr;
    }
}

void World::moveCreatures() {
    //For each Creature
    for (int c = 0; c < m_creatures.size(); c++) {
        //Perform move of Creature
        const std::pair<int, int> oldCoord = m_creatures[c]->getCoord();
        std::pair<int, int> newCoord = m_creatures[c]->move(m_size);

        //Update the grid
        if (oldCoord.first!=newCoord.first || oldCoord.second!=newCoord.second) {
            //Remove Creature from old Spot
            m_grid[oldCoord.second * m_size + oldCoord.first].removeCreature(m_creatures[c]->getId());
            //Add Creature to new Spot
            m_grid[newCoord.second * m_size + newCoord.first].addCreature(m_creatures[c]);
        }
    }
}

void World::interactBtwCreatures() {
    // Get Creatures to interact
    for (int x = 0; x < m_size; x++) {
        for (int y = 0; y < m_size; y++) {
            if (m_grid[y * m_size + x].getNbCreatures() == 2) {
                // If exactly two Creatures in a Spot, reproduction
                m_lastCreatureId++;
                Creature* newCreaturePtr = sexualReproduction(m_grid[y * m_size + x].getCreatureFromIndex(0), m_grid[y * m_size + x].getCreatureFromIndex(1));
                m_toBeBornCreatures.push_back(newCreaturePtr);
            }
        }
    }
}

Creature* World::asexualReproduction(Creature* parent) {
    // New creature in a random neighbouring spot
    std::pair<int, int> parentCoords = parent->getCoord();
    const int childX = (parentCoords.first + (rand() % 2 - 1) + m_size) % m_size;
    const int childY = (parentCoords.second + (rand() % 2 - 1) + m_size) % m_size;
    
    // Genome is that of parent plus mutation step
    std::string genome = parent->getGenome();
    const int i = 100000;
    for (char c = 0; c < genome.size(); c++) {
        int r = rand() % i;
        if (r <= m_mutationProb * i) {
            //Mutation
            const int newBase = m_bases[rand() % m_bases.size()];
            genome[c] = newBase;
        }
    }
    
    return new Creature(m_lastCreatureId, genome, childX, childY);
}

Creature* World::sexualReproduction(Creature* firstParent, Creature* secondParent) {
    // New creature in a random neighbouring spot
    std::pair<int, int> parentCoords = firstParent->getCoord();
    const int childX = (parentCoords.first + (rand() % 2 - 1) + m_size) % m_size;
    const int childY = (parentCoords.second + (rand() % 2 - 1) + m_size) % m_size;
    
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
        if (r <= m_crossoverProb * i) {
            // Crossover
            // Change the selected parent genome
            selectedParent = (selectedParent + 1) % 2;
        }
        
        r = rand() % i;
        if (r <= m_mutationProb * i) {
            //Mutation
            const int newBase = m_bases[rand() % m_bases.size()];
            genome[c] = newBase;
        }
    }
    
    return new Creature(m_lastCreatureId, genome, childX, childY);
}

void World::runSimulationStep() {
    moveCreatures();
    interactBtwCreatures();
}
