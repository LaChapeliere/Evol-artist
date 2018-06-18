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
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Creature.hpp"

//Forward declaration of World class
class World;

//Class for the spots in the grid
class Spot
{
private:
    /**
     * Pointer to world
     */
    World* m_world;
    
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
    
    /**
     * Dictionary describing the environment
     */
    std::map<std::string, int> m_env;
    
public:
    /**
     * Spot constructor
     * @param world Pointer to the world
     * @param x Horizontal coordinate
     * @param y Vertical coordinate
     */
    Spot(World* world, const int x, const int y);
    
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
     * Accessor of the m_env variable
     * @return The value of m_env
     */
    std::map<std::string, int> getEnv() const;
    
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
    
    /**
     * Genetic algorithm reproduction step. Each pair of parents create 4 offsprings
     */
    void nextStepPop();
    
    /**
     * Create a descendant of a Creature
     * @param parent The parent Creature
     * @return The child Creature
     */
    Creature* asexualReproduction(Creature* parent);
    
    /**
     * Creature a descendant of two Creatures
     * @param firstParent One parent Creature
     * @param secondParent One parent Creature
     * @return The child Creature
     */
    Creature* sexualReproduction(Creature* firstParent, Creature* secondParent);
};

#endif /* Spot_hpp */
