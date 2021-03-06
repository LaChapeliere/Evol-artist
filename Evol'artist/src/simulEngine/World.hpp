//
//  World.hpp
//  Evol'artist
//
//  Created by Emma Barme on 28/09/2017.
//  Copyright GNU General Public License v3.0
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <stdlib.h>
#include "Spot.hpp"
#include "Creature.hpp"


//Class for the world grid
class World
{
private:
    /**
     * Size of the world grid
     */
    const int m_size;
    
    /**
     * Time since initialization, in simulation steps
     */
    int m_age;
    
    /**
     * Time since last manual modification, in simulation steps
     */
    int m_incubationTime;
    
    /**
     * Flattened matrix of Spot objects, represent the grid
     */
    std::vector<Spot> m_grid;
    
    /**
     * Identifier of most recent Creature object
     */
    int m_lastCreatureId;
    
    /**
     * List of pointers to all Creature objects in the world
     */
    std::vector<Creature*> m_creatures;
    
    /**
     * List of pointers to Creature objects that will be added to the world during the simulation resolution step
     */
    std::vector<Creature*> m_toBeBornCreatures;
    
    // Genetic attributes
    /**
     * Mutation probability for reproduction
     */
    const double m_mutationProb = 0.4;
    
    /**
     * Cross-over probability for reproduction
     */
    const double m_crossoverProb = 0.05;
    
    /**
     * Possible base in the genetic code
     */
    std::vector<char> m_bases;
    
public:
    /**
     * World constructor
     * @param size The size of the square grid
     * @param nbCreatures The number of Creature objects to generate in the grid initially
     */
    World(const int size, const int nbCreatures);
    
    /**
     * Accessor of size of the world
     * @return m_size
     */
    const int getSize() const;
    
    /**
     * Accessor of age of the world
     * @return m_age
     */
    const int getAge() const;
    
    /**
     * Accessor of incubation time of the world
     * @return m_incubationTime
     */
    const int getIncubTime() const;
    
    /**
    * Get the number of Creature objects in the world
    * @return m_creatures.size()
    */
    const int getNbCreatures() const;
    
    /**
     * Accessor by pointer to Spots in the grid
     * @param x The horizontal coordinate of the desired Spot in the grid
     * @param y The vertical coordinate of the desired Spot in the grid
     * @return The pointer to the corresponding Spot object
     */
    Spot const* getPointerToSpot(const int x, const int y) const;
    
    
    /**
     * Add a Creature to the world, in a random position
     */
    void addCreature();
    
    /**
     * Add a Creature to the world, in a specified position
     */
    void addCreature(const int x, const int y);
    
    /**
     * Delete a Creature from the world, according to its identifier
     */
    void removeCreature(const int creatureId);
    
    /**
     * Evaluate environment for each Creature object
     */
    void evalEnvCreatures();
    
    /**
     * Move all Creature objects
     */
    void moveCreatures();
    
    /**
     * Have Creatures interact in each Spot
     */
    void interactBtwCreatures();
    
    /**
     * Have Creatures interact with their environment
     */
    void interactCreaturesEnv();
    
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
    
    /**
     * Survival and aging step
     */
    void resolveTurn();
    
    /**
     * Run one simulation step
     */
    void runSimulationStep();
};

#endif /* World_hpp */
