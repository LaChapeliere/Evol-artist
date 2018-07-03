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
            m_fitnessFunctions.Add("BB", (env) => { return 100; });
            m_fitnessFunctions.Add("BC", (env) => { return 110; });
            m_fitnessFunctions.Add("BD", (env) => { return 120; });
            m_fitnessFunctions.Add("CB", (env) => { return 130; });
            m_fitnessFunctions.Add("CC", (env) => { return (445 * env["Humidite"] / 10); }); //humidité
            m_fitnessFunctions.Add("CD", (env) => { return 700; });
            m_fitnessFunctions.Add("DB", (env) => { return 160; });
            m_fitnessFunctions.Add("DC", (env) => { return 170; });
            m_fitnessFunctions.Add("DD", (env) => { return 180; });
            m_fitnessFunctions.Add("BBB", (env) => { return 200; });
            m_fitnessFunctions.Add("BBC", (env) => { return 210; });
            m_fitnessFunctions.Add("BBD", (env) => { return 220; });
            m_fitnessFunctions.Add("BCB", (env) => { return 230; });
            m_fitnessFunctions.Add("BCC", (env) => { return 640; });
            m_fitnessFunctions.Add("BCD", (env) => { return 250; });
            m_fitnessFunctions.Add("BDB", (env) => { return 260; });
            m_fitnessFunctions.Add("BDC", (env) => { return 270; });
            m_fitnessFunctions.Add("BDD", (env) => { return 280; });
            m_fitnessFunctions.Add("CBB", (env) => { return 300; });
            m_fitnessFunctions.Add("CBC", (env) => { return 310; });
            m_fitnessFunctions.Add("CBD", (env) => { return 320; });
            m_fitnessFunctions.Add("CCB", (env) => { return 330; });
            m_fitnessFunctions.Add("CCC", (env) => { return 340; });
            m_fitnessFunctions.Add("CCD", (env) => { return 350; });
            m_fitnessFunctions.Add("CDB", (env) => { return 360; });
            m_fitnessFunctions.Add("CDC", (env) => { return 370; });
            m_fitnessFunctions.Add("CDD", (env) => { return 380; });
            m_fitnessFunctions.Add("DBB", (env) => { return 400; });
            m_fitnessFunctions.Add("DBC", (env) => { return 410; });
            m_fitnessFunctions.Add("DBD", (env) => { return 420; });
            m_fitnessFunctions.Add("DCB", (env) => { return 430; });
            m_fitnessFunctions.Add("DCC", (env) => { return 440; });
            m_fitnessFunctions.Add("DCD", (env) => { return 450; });
            m_fitnessFunctions.Add("DDB", (env) => { return 460; });
            m_fitnessFunctions.Add("DDC", (env) => { return 470; });
            m_fitnessFunctions.Add("DDD", (env) => { return 480; });
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
