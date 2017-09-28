//
//  Creature.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//

#include "Creature.hpp"
#include "World.hpp"

Creature::Creature(const int id, const int x, const int y): m_id(id), m_visionCap(3), m_moveCap(1) {
    //Initialise attributes
    m_x = x;
    m_y = y;
    m_health = 100;
    m_hunger = 0;
    
    m_maxPercepCap = m_visionCap;
}

Creature::Creature(const int id): m_id(id), m_visionCap(3), m_moveCap(1) {
    //Generate random coordinates in world space
    const int x = rand() % 1000;
    const int y = rand() % 1000;
    
    //Initialise attributes
    m_x = x;
    m_y = y;
    m_health = 100;
    m_hunger = 0;
    
    m_maxPercepCap = m_visionCap;
}

Creature::Creature(const Creature& creature): m_id(creature.m_id), m_visionCap(creature.m_visionCap), m_moveCap(creature.m_moveCap), m_x(creature.m_x), m_y(creature.m_y), m_health(creature.m_health), m_hunger(creature.m_hunger), m_maxPercepCap(creature.m_maxPercepCap) {}

Creature Creature::operator=(const Creature& creature) {
    return Creature(creature);
}

const int Creature::getId() const {
    return m_id;
}

const int Creature::getVisionCap() const {
    return m_visionCap;
}

const int Creature::getmaxPercepCap() const {
    return m_maxPercepCap;
}

const std::pair<int, int> Creature::getCoord() const {
    return std::pair<int, int> (m_x, m_y);
}

const bool Creature::isAlive() const {
    return (m_health > 0);
}

void Creature::growHungry() {
    m_hunger += 5;
    m_hunger = fmax(m_hunger, 0);
}

void Creature::hungerImpactHealth() {
    //Hunger is always positive
    if (m_hunger >= 0) {
        m_health -= m_hunger;
    }
}

int Creature::feed(const int food) {
    //Feeding power must be positive
    if (food >= 0) {
        int eating = fmin(food, m_hunger);
        m_hunger -= eating;
        return eating;
    }
    else {
        return 0;
    }
}

void Creature::perceiveLocalEnv(World const* world) {
    // Initialise the local map to a square of side m_maxPercepCap*2+1
    m_env.clear();
    const int localEnvSize = m_maxPercepCap*2+1;
    m_env.assign(pow(localEnvSize,2),0);
    
    //For each spot in local environment, get the Spot object to evaluate
    const int worldSize = world->getSize();
    for (int y = 0; y < localEnvSize; y++) {
        for (int x = 0; x < localEnvSize; x++) {
            const int yWorld = (y + m_y - m_maxPercepCap + worldSize) % worldSize;
            const int xWorld = (x + m_x - m_maxPercepCap + worldSize) % worldSize;
            Spot const* spot = world->getPointerToSpot(xWorld, yWorld);
            // For now, compute score depending on the food available and the availability of other creatures on the spot
            int score = round(spot->getFood() / 10.0);
            if (spot->getNbCreatures() > 0) {
                score += 5;
            }
            
            m_env[y * localEnvSize + x] = score;
        }
    }
}

const std::pair<int, int> Creature::move() {
    //Dummy implementation, no move
    return getCoord();
}
