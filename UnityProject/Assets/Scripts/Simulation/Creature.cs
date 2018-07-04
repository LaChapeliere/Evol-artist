using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
namespace Application
{
    public class Creature
    {
        /*
         * Identifier of the creature
         */
        private int m_id;

        /*
         * Single chromosome genome
         */
        private string m_genome;

        /*
         * List of genes by alphabetical order
         */
        private List<string> m_genes;

        /*
         * Fitness (between 0 and 100)
         */
        private int m_fitness;

        /*
         * Horizontal coordinate of the creature in the world grid
         */
        private int m_x;

        /*
         * Vertical coordinate of the creature in the world grid
         */
        private int m_y;

        /*
         * Creature constructor with specified coordinates
         * @param id Creature id
         * @param genome Single chromosome genome
         * @param x Horizontal coordinate
         * @param y Vertical coordinate
         * @param env Dict describing environment
         */
        public Creature(int id, string genome, int x, int y, Dictionary<string, int> env)
        {
            //Initialise attributes
            m_id = id;
            m_genome = genome;
            Test.Print("pre-interpret");
            m_genes = interpretGenome();

            // Get fitness
            FitnessFunctions f = new FitnessFunctions();
            Test.Print("between-fitness");
            m_fitness = f.getFitness(m_genes, env);
            Test.Print("post-fitness");

            //Coordinates
            m_x = x;
            m_y = y;
        }

        /*
         * Creature copy constructor
         * @param creature The Creature object to copy
         */
        public Creature(Creature creature)
        {
            //Initialise attributes
            m_id = creature.m_id;
            m_genome = creature.m_genome;
            m_genes = creature.m_genes;
            m_fitness = creature.m_fitness;
            //Coordinates
            m_x = creature.m_x;
            m_y = creature.m_y;
        }

        /*
         * Identifier accessor
         * @return m_id
         */
        public int getId() {
            return m_id;
        }

        /*
         * Genome accessor
         * @return m_genome
         */
        public string getGenome() {
            return m_genome;
        }

        /*
         * Fitness accessor
         * @return m_fitness
         */
        public int getFitness() {
            return m_fitness;
        }

        /*
         * Coordinates accessor
         * @return The pair of horizontal and vertical coordinates
         */
        public Tuple<int, int> getCoord() {
            return new Tuple<int, int> (m_x, m_y);
        }

        /*
         * Interpret genome as genes
         * @return A list of valide gene strings
         */
        public List<string> interpretGenome() {
            // Get list of genes using regular expressions
            Regex genesRegex = new Regex("A[BCD]{2,3}E");
            List<string> genes = new List<string>();
            Test.Print(m_genome);
            Match match = genesRegex.Match(m_genome);
            while (match.Success) {
                Test.Print(match.Value);
                string gene = match.Value;
                gene = gene.Substring(1, gene.Length - 2);
                genes.Add(gene);
                match = match.NextMatch();
            }
            Test.Print("End while");
            return genes;
        }

        /*
         * Check if has a specific gene
         * @param gene The string of the gene
         * @return True if the gene is present
         */
        public bool hasGene(string gene) {
            return m_genes.Exists(s => s == gene);
        }
    }
}
