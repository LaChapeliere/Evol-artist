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
            Spot* spot = new Spot(this, x, y);
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
        Creature* newCreature = new Creature(getNewCreatureId(), "ADDDEBDDEADDCEADDDE", randX, randY, m_grid[randX + randY * m_size]->getEnv());
        m_grid[randX + randY * m_size]->addCreature(newCreature);
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

const double World::getMutationRate() const {
    return m_mutationProb;
}

const double World::getCrossoverRate() const {
    return m_crossoverProb;
}

const std::vector<char> World::getPossibleBases() const {
    return m_bases;
}

Spot* const World::getPointerToSpot(const int x, const int y) const {
    return m_grid[y * m_size + x];
}

void World::runSimulationStep() {
    for (int i = 0; i < m_size * m_size; i++) {
        Spot* s = m_grid[i];
        std::cout << s->getNbCreatures() << std::endl;
        for (int i = 0; i < s->getNbCreatures(); i++) {
            Creature* c = s->getCreatureFromIndex(i);
            std::cout << c->getId() << " " << c->getFitness() << std::endl;
        }
        s->nextStepPop();
    }
    std::cout << std::endl;
}
