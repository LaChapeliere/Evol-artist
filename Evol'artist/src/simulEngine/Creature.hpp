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
#include <regex>
#include <iterator>
#include "FitnessFunctions.hpp"

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
     * List of genes by alphabetical order
     */
    std::vector<std::string> m_genes;
    
    /**
     * Fitness (between 0 and 100)
     */
    int m_fitness;
    
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
     * @param env Dict describing environment
     */
    Creature(const int id, const std::string genome, const int x, const int y, std::map<std::string, int> env);
    
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
     * Fitness accessor
     * @return m_fitness
     */
    const int getFitness() const;
    
    /**
     * Coordinates accessor
     * @return The pair of horizontal and vertical coordinates
     */
    const std::pair<int, int> getCoord() const;
    
    /**
     * Interpret genome as genes
     * @return A list of valide gene strings
     */
    std::vector<std::string> interpretGenome();
    
    /**
     * Check if has a specific gene
     * @param gene The string of the gene
     * @return True if the gene is present
     */
    const bool hasGene(std::string gene) const;
};

#endif /* Creature_hpp */
