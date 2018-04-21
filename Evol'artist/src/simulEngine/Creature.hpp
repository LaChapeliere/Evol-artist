//
//  Creature.hpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//
//  Last modified by Emma Barme on 29/09/2017

#ifndef Creature_hpp
#define Creature_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <math.h>
#include <utility>

//Forward declaration of World class
class World;

//Class for the creatures
class Creature
{
private:
    /**
     * Identifier of the creature
     */
    const int m_id;
    
    /**
     * Single chromosome genome
     */
    const std::string m_genome;
    
    /**
     * Horizontal coordinate of the creature in the world grid
     */
    int m_x;
    
    /**
     * Vertical coordinate of the creature in the world grid
     */
    int m_y;
    
public:
    /**
     * Creature constructor with specified coordinates
     * @param id Creature id
     * @param genome Single chromosome genome
     * @param x Horizontal coordinate
     * @param y Vertical coordinate
     */
    Creature(const int id, const std::string genome, const int x, const int y);
    
    /**
     * Creature copy constructor
     * @param creature The Creature object to copy
     */
    Creature(const Creature& creature);
    
    Creature operator=(const Creature& creature);
    
    /**
     * Identifier accessor
     * @return m_id
     */
    const int getId() const;
    
    /**
     * Genome accessor
     * @return m_genome
     */
    const std::string getGenome() const;
    
    /**
     * Coordinates accessor
     * @return The pair of horizontal and vertical coordinates
     */
    const std::pair<int, int> getCoord() const;
    
    /**
     * Interpret genome as characteristics
     */
    void interpretGenome();
    
    /**
     * Move the creature towards the visible spot with highest feeding power
     * @param worldSize The size of the world grid
     * @return The pair of new horizontal and vertical coordinates
     */
    const std::pair<int, int> move(const int worldSize);
};

#endif /* Creature_hpp */
