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
            m_fitnessFunctions.Add("BD", (env) => { return 12; });
            m_fitnessFunctions.Add("CB", (env) => { return 13; });
            m_fitnessFunctions.Add("CC", (env) => { return 89 + env["Humidity"]; });
            m_fitnessFunctions.Add("CD", (env) => { return 70; });
            m_fitnessFunctions.Add("DB", (env) => { return 16; });
            m_fitnessFunctions.Add("DC", (env) => { return 17; });
            m_fitnessFunctions.Add("DD", (env) => { return 18; });
            m_fitnessFunctions.Add("BBB", (env) => { return 20; });
            m_fitnessFunctions.Add("BBC", (env) => { return 21; });
            m_fitnessFunctions.Add("BBD", (env) => { return 22; });
            m_fitnessFunctions.Add("BCB", (env) => { return 23; });
            m_fitnessFunctions.Add("BCC", (env) => { return 64; });
            m_fitnessFunctions.Add("BCD", (env) => { return 25; });
            m_fitnessFunctions.Add("BDB", (env) => { return 26; });
            m_fitnessFunctions.Add("BDC", (env) => { return 27; });
            m_fitnessFunctions.Add("BDD", (env) => { return 28; });
            m_fitnessFunctions.Add("CBB", (env) => { return 30; });
            m_fitnessFunctions.Add("CBC", (env) => { return 31; });
            m_fitnessFunctions.Add("CBD", (env) => { return 32; });
            m_fitnessFunctions.Add("CCB", (env) => { return 33; });
            m_fitnessFunctions.Add("CCC", (env) => { return 34; });
            m_fitnessFunctions.Add("CCD", (env) => { return 35; });
            m_fitnessFunctions.Add("CDB", (env) => { return 36; });
            m_fitnessFunctions.Add("CDC", (env) => { return 37; });
            m_fitnessFunctions.Add("CDD", (env) => { return 38; });
            m_fitnessFunctions.Add("DBB", (env) => { return 40; });
            m_fitnessFunctions.Add("DBC", (env) => { return 41; });
            m_fitnessFunctions.Add("DBD", (env) => { return 42; });
            m_fitnessFunctions.Add("DCB", (env) => { return 43; });
            m_fitnessFunctions.Add("DCC", (env) => { return 44; });
            m_fitnessFunctions.Add("DCD", (env) => { return 45; });
            m_fitnessFunctions.Add("DDB", (env) => { return 46; });
            m_fitnessFunctions.Add("DDC", (env) => { return 47; });
            m_fitnessFunctions.Add("DDD", (env) => { return 48; });
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
