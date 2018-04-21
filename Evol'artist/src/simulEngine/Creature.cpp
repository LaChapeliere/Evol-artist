//
//  Creature.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017

#include "Creature.hpp"
#include "World.hpp"

Creature::Creature(const int id, const std::string genome, const int x, const int y): m_id(id), m_genome(genome) {
    //Initialise attributes by default
    
    interpretGenome();
    
    //Coordinates
    m_x = x;
    m_y = y;
}

Creature::Creature(const Creature& creature): m_id(creature.m_id), m_x(creature.m_x), m_y(creature.m_y), m_genome(creature.m_genome) {}

Creature Creature::operator=(const Creature& creature) {
    return Creature(creature);
}

const int Creature::getId() const {
    return m_id;
}

const std::string Creature::getGenome() const {
    return m_genome;
}

const std::pair<int, int> Creature::getCoord() const {
    return std::pair<int, int> (m_x, m_y);
}

void Creature::interpretGenome() {
    
}

const std::pair<int, int> Creature::move(const int worldSize) {
    return std::make_pair(m_x, m_y);
}
