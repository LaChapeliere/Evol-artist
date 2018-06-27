using System;
using System.Collections.Generic;
namespace Application
{
    public class FitnessFunctions
    {

        /*
         * Map between genes and fitness functions
         */
        private Dictionary<string, Func<Dictionary<string, int>, int>> m_fitnessFunctions;


        /*
         * FitnessFunctions constructor
         */
        public FitnessFunctions() {
            m_fitnessFunctions = new Dictionary<string, Func<Dictionary<string, int>, int>>();
            m_fitnessFunctions.Add("BB", (env) => { return 10; });
            m_fitnessFunctions.Add("BC", (env) => { return 11; });
        }

        /*
         * Compute the fitness of a genome
         * @param genome List of genes
         * @param env A dictionnary describing the environment
         * @return The fitness of the genome between 0 and 100
         */
        public int getFitness(List<string> genome, Dictionary<string, int> env) {
            int fitnessSum = 0;
            // Get the fitness function and compute fitness for each gene
            for (int i = 0; i < genome.Count; i++) {
                Func<Dictionary<string, int>, int> func = m_fitnessFunctions[genome[i]];
                int geneFitness = func(env);
                // If fitness is null, creature is dead
                if (geneFitness == 0) {
                    return 0;
                }
                else {
                    fitnessSum += geneFitness;
                }
            }

            // Compute mean of fitness
            int fitness;
            if (genome.Count == 0) {
                fitness = 0;
            }
            else {
                fitness = fitnessSum / genome.Count;
            }
            return fitness;
        }
    }
}   
