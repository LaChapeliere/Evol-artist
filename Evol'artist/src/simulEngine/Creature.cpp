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

Creature::Creature(const int id, const std::string genome, const int x, const int y, std::map<std::string, int> env): m_id(id), m_genome(genome) {
    //Initialise attributes by default
    
    m_genes = interpretGenome();
    
    // Get fitness
    FitnessFunctions f = FitnessFunctions();
    m_fitness = f.getFitness(m_genes, env);
    
    //Coordinates
    m_x = x;
    m_y = y;
}

Creature::Creature(const Creature& creature): m_id(creature.m_id), m_x(creature.m_x), m_y(creature.m_y), m_genome(creature.m_genome), m_genes(creature.m_genes), m_fitness(creature.m_fitness) {}

Creature Creature::operator=(const Creature& creature) {
    return Creature(creature);
}

const int Creature::getId() const {
    return m_id;
}

const std::string Creature::getGenome() const {
    return m_genome;
}

const int Creature::getFitness() const {
    return m_fitness;
}

const std::pair<int, int> Creature::getCoord() const {
    return std::pair<int, int> (m_x, m_y);
}

std::vector<std::string> Creature::interpretGenome() {
    // Get list of genes using regular expressions
    std::regex genesRegex("A[BCD]{2,3}E");
    auto genesBegin = std::sregex_iterator(m_genome.begin(), m_genome.end(), genesRegex);
    auto genesEnd = std::sregex_iterator();
    std::vector<std::string> genes;
    for (std::sregex_iterator i = genesBegin; i != genesEnd; ++i) {
        std::smatch match = *i;
        std::string gene = match.str();
        gene = gene.substr(1,gene.size() - 2); //Strip A and E
        genes.push_back(gene);
    }
    
    return genes;
}

const std::pair<int, int> Creature::move(const int worldSize) {
    return std::make_pair(m_x, m_y);
}
