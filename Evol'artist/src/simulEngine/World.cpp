//
//  World.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017
#include <iostream>
#include "World.hpp"

World::World(const int size, const int nbCreatures, const std::string genome, std::map<std::string, std::pair<int, int>> globalEnv): m_size(size) {
    m_age = 0;
    m_incubationTime = 0;
    m_lastCreatureId = -1;
    m_bases.push_back('B');
    m_bases.push_back('C');
    m_bases.push_back('D');
    
    std::default_random_engine generator;
    
    //Create grid of Spots
    for (int y = 0; y < m_size; y++) {
        for (int x = 0; x < m_size; x++) {
            std::map<std::string, int> env;
            for (auto const &envChar : globalEnv) {
                std::normal_distribution<double> distribution(envChar.second.first, envChar.second.second);
                double envCharValue = distribution(generator);
                env.insert(std::make_pair(envChar.first, envCharValue));
            }
            Spot* spot = new Spot(this, x, y, env);
            m_grid.push_back(spot);
        }
    }
    
    for (int y = 0; y < m_size; y++) {
        for (int x = 0; x < m_size; x++) {
            //std::cout << x << " " << y << std::endl;
            std::map<std::string, int> spotEnv = m_grid[x + y * m_size]->getEnv();
            for (auto const &envChar : spotEnv) {
                std::cout << envChar.first << " " << envChar.second << std::endl;
            }
        }
    }
    
    srand(time(NULL));
    
    //Add the Creatures in the grid
    for (int i = 0; i < nbCreatures; i++) {
        int randX = rand() % m_size;
        int randY = rand() % m_size;
        std::map<std::string, int> env;
        env.insert(std::make_pair("global", 29));
        Creature* newCreature = new Creature(getNewCreatureId(), genome, randX, randY, m_grid[randX + randY * m_size]->getEnv());
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

const int World::getNbCreatures() const {
	int nb = 0;
	int stupid= 0;
	for (int i = 0; i < m_size * m_size; i++)
	{
		int creaSpot = m_grid[i]->getNbCreatures();
		std::cout << creaSpot;
		if (creaSpot < 10) std::cout << " ";
		std::cout << "|";
		if (stupid++ == (m_size-1))
		{
			std::cout << std::endl;
			stupid=0;
		}
		
		nb += m_grid[i]->getNbCreatures();
	}
	std::cout << std::endl;
	return nb;
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
        /*std::cout << s->getNbCreatures() << std::endl;
        for (int i = 0; i < s->getNbCreatures(); i++) {
            Creature* c = s->getCreatureFromIndex(i);
                std::cout << c->getId() << " " << c->getFitness() << " " << c->getGenome() << std::endl;
        }*/
        s->nextStepPop();
    }
    //std::cout << std::endl << std::endl;
}

int World::getPercentageGene(std::string gene) const {
    int totalPop = 0;
    int genePop = 0;
    
    for (int x = 0; x < m_size; x++) {
        for (int y = 0; y < m_size; y++) {
            Spot* s = getPointerToSpot(x, y);
            int spotCreatur = s->getNbCreatures();
            totalPop += spotCreatur;
            for (int i = 0; i < spotCreatur; i++) {
                Creature* c = s->getCreatureFromIndex(i);
                if (c->hasGene(gene)) {
                    genePop += 1;
                }
            }
        }
    }
    
    if (totalPop == 0) {
        return 0;
    }
    else {
        return 100 * genePop / totalPop;
    }
}
