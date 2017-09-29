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
    
    //Create grid of Spots
    for (int y = 0; y < m_size; y++) {
        for (int x = 0; x < m_size; x++) {
            m_grid.push_back(Spot(x, y));
        }
    }
    
    //Add the Creatures in the grid
    for (int i = 0; i < nbCreatures; i++) {
        addCreature();
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

Spot const* World::getPointerToSpot(const int x, const int y) const {
    return &(m_grid[y * m_size + x]);
}

void World::addCreature() {
    //Generate random coordinates in world space
    const int x = rand() % m_size;
    const int y = rand() % m_size;
    
    addCreature(x, y);
}

void World::addCreature(const int x, const int y) {
    //Create creature
    m_lastCreatureId++;
    Creature* creaturePtr = new Creature(m_lastCreatureId, x, y);
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

void World::evalEnvCreatures() {
    //For each Creature
    for (int c = 0; c < m_creatures.size(); c++) {
        m_creatures[c]->perceiveLocalEnv(this);
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
    // For now, dummy reproduction: each Spot with more than one Creature generates a new random Creature in one of the neighboring spots. The Creature is not added immediately but will be born in the simulation resolving step
    for (int x = 0; x < m_size; x++) {
        for (int y = 0; y < m_size; y++) {
            if (m_grid[y * m_size + x].getNbCreatures() > 1) {
                //Create creature
                int newX = (x + (rand() % 2 - 1)) % m_size;
                int newY = (y + (rand() % 2 - 1)) % m_size;
                m_lastCreatureId++;
                Creature* newCreaturePtr = new Creature(m_lastCreatureId, newX, newY);
                m_toBeBornCreatures.push_back(newCreaturePtr);
            }
        }
    }
}

void World::interactCreaturesEnv() {
    //For each Spot
    for (int s = 0; s < (int)m_grid.size(); s++) {
        m_grid[s].feedCreatures();
    }
}

void World::resolveTurn() {
    //Update health and hunger for each Creature, then check if it's alive, remove it if not
    for (int c = (int)m_creatures.size() - 1; c >= 0; c--) {
        m_creatures[c]->hungerImpactHealth();
        m_creatures[c]->growHungry();
        if (!m_creatures[c]->isAlive()) {
            removeCreature(m_creatures[c]->getId());
        }
    }
    
    //Give birth to new Creatures
    for (int c = 0; c < m_toBeBornCreatures.size(); c++) {
        m_creatures.push_back(m_toBeBornCreatures[c]);
        const std::pair<int, int> coord = m_toBeBornCreatures[c]->getCoord();
        
        //Add creature to grid
        m_grid[coord.first + coord.second * m_size].addCreature(m_creatures[m_creatures.size() -1]);
    }
    m_toBeBornCreatures.clear();
    
    //Update vegetation on Spot objects
    for (int s = 0; s < m_grid.size(); s++) {
        m_grid[s].growFood();
    }
    
    //Update age and incubation time
    m_age++;
    m_incubationTime++;
}

void World::runSimulationStep() {
    evalEnvCreatures();
    moveCreatures();
    interactBtwCreatures();
    interactCreaturesEnv();
    resolveTurn();
}
