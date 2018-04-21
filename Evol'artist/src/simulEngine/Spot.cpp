//
//  Spot.cpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017


#include "Spot.hpp"

Spot::Spot(const int x, const int y): m_x(x), m_y(y) {
}

const int Spot::getNbCreatures() const {
    return (int)m_creatures.size();
}

Creature* Spot::getCreatureFromIndex(const int id) const {
    return m_creatures[id];
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
