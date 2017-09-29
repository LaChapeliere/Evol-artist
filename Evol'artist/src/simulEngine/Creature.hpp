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
     * Vision capacity of the creature
     */
    const int m_visionCap;
    
    /**
     * Maximum range of perception
     */
    int m_maxPercepCap;
    
    /**
     * Movement capacity of the creature
     */
    const int m_moveCap;
    
    /**
     * Horizontal coordinate of the creature in the world grid
     */
    int m_x;
    
    /**
     * Vertical coordinate of the creature in the world grid
     */
    int m_y;
    
    /**
     * Health of the creature
     */
    int m_health;
    
    /**
     * Hunger of the creature
     */
    int m_hunger;
    
    /**
     * Flattened matrix of the perceived local environment, centered on current position
     */
    std::vector<int> m_env;
    
public:
    /**
     * Creature constructor with specified coordinates
     * @param id Creature id
     * @param x Horizontal coordinate
     * @param y Vertical coordinate
     */
    Creature(const int id, const int x, const int y);
    
    /**
     * Creature constructor at random location
     * @param id Creature id
     */
    Creature(const int id);
    
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
     * Vision capacity accessor
     * @return m_visionCap
     */
    const int getVisionCap() const;
    
    /**
     * Maximum perception capacity accessor
     * @return m_maxPercepCap
     */
    const int getmaxPercepCap() const;
    
    /**
     * Coordinates accessor
     * @return The pair of horizontal and vertical coordinates
     */
    const std::pair<int, int> getCoord() const;
    
    /**
     * Check whether the creature should still be alive
     * @return False if the creature's health is negative
     */
    const bool isAlive() const;
    
    
    /**
     * Increase hunger as time goes
     */
    void growHungry();
    
    /**
     * Decrease health according to hunger
     */
    void hungerImpactHealth();
    
    /**
     * Feed creature to quell hunger
     * @param food The feeding power of the food
     */
    int feed(const int food);
    
    /**
     * Build local perception map
     * @param world A pointer to the World object
     */
    void perceiveLocalEnv(World const* world);
    
    /**
     * Move the creature towards the visible spot with highest feeding power
     * @param worldSize The size of the world grid
     * @return The pair of new horizontal and vertical coordinates
     */
    const std::pair<int, int> move(const int worldSize);
    
    /**
     * Determine the target for moving, in the local perception map
     * @return The pair of horizontal and vertical coordinates of the target
     */
    const std::pair<int, int> findTarget();
    
};

// Declaration of the A* utility function
/**
 * A Function to find the shortest path between a given source cell to a destination cell according to A* Search Algorithm
 * @param grid Reference to a flattened grid matrix with the scores
 * @param src The coordinates of the source in the grid
 * @param dest The coordinates of the target in the grid
 * @param moveCap The maximum number of moves
 * @param maxScore The maximum score for a Spot in the grid
 * @return The coordinates of the Spot reached after moveCap moves on the shortest path to the target
 */
std::pair<int, int> aStarSearch(std::vector<int>& grid, std::pair<int, int> src, std::pair<int, int> dest, const int moveCap, const int maxScore);


#endif /* Creature_hpp */
