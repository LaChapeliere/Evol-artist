//
//  Spot.hpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//

#ifndef Spot_hpp
#define Spot_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Creature.hpp"

//Class for the spots in the grid
class Spot
{
private:
    /**
     * Horizontal coordinate of the position in the world grid
     */
    const int m_x;
    
    /**
     * Vertical coordinate of the position in the world grid
     */
    const int m_y;
    
    /**
     * List of Creatures (pointers) on this spot
     */
    std::vector<Creature*> m_creatures;
    
public:
    /**
     * Spot constructor
     * @param x Horizontal coordinate
     * @param y Vertical coordinate
     */
    Spot(const int x, const int y);
    
    /**
     * Give the number of creatures on the spot
     * @return The length of m_creatures
     */
    const int getNbCreatures() const;
    
    /**
     * Give the pointer to a specific creature of the spot
     * @param id Index of the desired creature in m_creatures
     * @return The value of m_creatures[id]
     */
    Creature* getCreatureFromIndex(const int id) const;
    
    /**
     * Add a creature to the spot
     * @param creaturePointer The pointer to the added Creature
     */
    void addCreature(Creature *const creaturePointer);
    
    /**
     * Remove a specific creature from the spot
     * @param id Identifier of the creature to remove from m_creatures
     */
    void removeCreature(const int id);
    
};

#endif /* Spot_hpp */
