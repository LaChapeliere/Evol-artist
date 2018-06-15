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
            Spot spot = Spot(this, x, y);
            m_grid.push_back(spot);
        }
    }
    
    srand(time(NULL));
    
    //Add the Creatures in the grid
    for (int i = 0; i < nbCreatures; i++) {
        int randX = rand() % m_size;
        int randY = rand() % m_size;
        std::map<std::string, int> env;
        env.insert(std::make_pair("global", 29));
        Creature* newCreature = new Creature(getNewCreatureId(), "ABBCEBDDEADDCEADDDE", randX, randY, m_grid[randX + randY * m_size].getEnv());
        m_grid[randX + randY * m_size].addCreature(newCreature);
        addCreature(newCreature);
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

const int World::getLastCreatureId() const {
    return m_lastCreatureId;
}

const int World::getNewCreatureId() {
    m_lastCreatureId = m_lastCreatureId + 1;
    return m_lastCreatureId;
}

const int World::getNbCreatures() const {
    return (int)m_creatures.size();
}

const double World::getMutationRate() const {
    return m_mutationProb;
}

const double World::getCrossoverRate() const {
    return m_crossoverProb;
}

const std::vector<char> World::getPossibleBases() const {
    return m_bases;
}

Spot const* World::getPointerToSpot(const int x, const int y) const {
    return &(m_grid[y * m_size + x]);
}

void World::addCreature(Creature* creature) {
    m_creatures.push_back(creature);
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
        /*
        //Remove from grid
        m_grid[x + y * m_size].removeCreature(creatureId);
        
        //Remove from world
        m_creatures.erase(m_creatures.begin() + indexInMCreatures);
        delete creaturePtr;*/
    }
}

void World::moveCreatures() {
    /*//For each Creature
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
    }*/
}


void World::runSimulationStep() {
    for (int i = 0; i < m_size * m_size; i++) {
        Spot s = m_grid[i];
        std::cout << s.getNbCreatures() << std::endl;
        s.nextStepPop();
        std::cout << s.getNbCreatures() << std::endl;
    }
    std::cout << std::endl;
}
