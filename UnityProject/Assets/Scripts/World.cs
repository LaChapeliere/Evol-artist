using System;
using System.Collections.Generic;
namespace Application
{
    public class World
    {

        /*
         * Size of the world grid
         */
        private int m_size;

        /*
         * Time since initialization, in simulation steps
         */
        private int m_age;

        /*
         * Time since last manual modification, in simulation steps
         */
        private int m_incubationTime;

        /*
         * Flattened matrix of Spot objects, represent the grid
         */
        private List<Spot> m_grid;

        /*
         * Identifier of most recent Creature object
         */
        private int m_lastCreatureId;

        // Genetic attributes
        /*
         * Mutation probability for reproduction
         */
        private const double m_mutationProb = 0.05;

        /*
         * Cross-over probability for reproduction
         */
        private const double m_crossoverProb = 0.05;

        /*
         * Possible base in the genetic code
         */
        private List<char> m_bases = null;

        /*
         * World constructor
         * @param size The size of the square grid
         * @param nbCreatures The number of Creature objects to generate in the grid initially
         * @param genome The genome of the initial population
         * @param globalEnv The mean and std for each environmental variable
         */
        public World(int size, int nbCreatures, string genome, Dictionary<string, Tuple<int, int>> globalEnv)
        {
            m_size = size;
            m_age = 0;
            m_incubationTime = 0;
            m_lastCreatureId = -1;
            m_bases = new List<char>();
            m_grid = new List<Spot>();
            m_bases.Add('B');
            m_bases.Add('C');
            m_bases.Add('D');
            //Create grid of Spots

            //Test.print("Pre-spot");
            for (int y = 0; y < m_size; y++)
            {
                for (int x = 0; x < m_size; x++)
                {
                    Dictionary<string, int> env = new Dictionary<string, int>();
                    foreach (KeyValuePair<string, Tuple<int, int>> entry in globalEnv)
                    {
                        double envCharValue = normalDistribution(entry.Value.Item1, entry.Value.Item2);
                        env.Add(entry.Key, (int)envCharValue);
                    }
                    Spot spot = new Spot(this, x, y, env);
                    m_grid.Add(spot);
                }
            }
            //Test.print("Post-spot");
            /*
            for (int y = 0; y<m_size; y++) {
                for (int x = 0; x<m_size; x++) {
                    std::cout << x << " " << y << std::endl;
                    std::map<std::string, int> spotEnv = m_grid[x + y * m_size]->getEnv();
                    for (auto const &envChar : spotEnv) {
                        std::cout << envChar.first << " " << envChar.second << std::endl;
                    }
                }
            }*/

            //Add the Creatures in the grid
            Random rnd = new Random();
            //Test.print("Pre-creature");
            for (int i = 0; i < nbCreatures; i++)
            {
                int randX = rnd.Next(0, m_size);
                int randY = rnd.Next(0, m_size);
                //Test.print("Pre-creature");
                Creature newCreature = new Creature(getNewCreatureId(), genome, randX, randY, m_grid[randX + randY * m_size].getEnv());
                //Test.print("Post-creature");
                m_grid[randX + randY * m_size].addCreature(newCreature);
                //Test.print(i.ToString());
            }
            Test.Print2("nombre creature1 = " + m_grid[0].getNbCreatures().ToString());
            Test.Print2("nombre creature2 = " + m_grid[1].getNbCreatures().ToString());
            Test.Print2("nombre creature3 = " + m_grid[2].getNbCreatures().ToString());
            Test.Print2("nombre creature4 = " + m_grid[3].getNbCreatures().ToString());
            //Test.print("End world");
        }

        /*
         * Accessor of size of the world
         * @return m_size
         */
        public int getSize() {
            return m_size;
        }

        /*
         * Accessor of age of the world
         * @return m_age
         */
        public int getAge() {
            return m_age;
        }

        /*
         * Accessor of incubation time of the world
         * @return m_incubationTime
         */
        public int getIncubTime() {
            return m_incubationTime;
        }

        /* Get the id of the last Creature
         * @return m_lastCreatureId
         */
        public int getLastCreatureId() {
            return m_lastCreatureId;
        }

        /* Get the id of the last Creature and increment
         * @return m_lastCreatureId
         */
        public int getNewCreatureId() {
            m_lastCreatureId = m_lastCreatureId + 1;
            return m_lastCreatureId;
        }

        /*
         * Get the mutation rate
         * @return m_mutationProb
         */
        public double getMutationRate() {
            return m_mutationProb;
        }

        /*
         * Get the crossover rate
         * @return m_crossoverProb
         */
        public double getCrossoverRate() {
            return m_crossoverProb;
        }

        /*
         * Get the possible bases
         * @return m_bases
         */
        public List<char> getPossibleBases() {
            return m_bases;
        }

        /*
         * Accessor Spots in the grid
         * @param x The horizontal coordinate of the desired Spot in the grid
         * @param y The vertical coordinate of the desired Spot in the grid
         * @return The corresponding Spot object
         */
        public Spot getSpot(int x, int y) {
            return m_grid[y * m_size + x];
        }

        /*
         * Run one simulation step
         */
        public void RunSimulationStep() {
            for (int i = 0; i < m_size * m_size; i++) {
                //Test.print("pre-simulation");
                Spot s = m_grid[i];
                /*std::cout << s->getNbCreatures() << std::endl;
                for (int i = 0; i < s->getNbCreatures(); i++) {
                    Creature* c = s->getCreatureFromIndex(i);
                        std::cout << c->getId() << " " << c->getFitness() << " " << c->getGenome() << std::endl;
                }*/
                s.nextStepPop();
                //Test.print("post-simulation");
            }
            //Test.print("End simulation");
            //std::cout << std::endl << std::endl;
        }


        // Information functions

        /*
         * Get percentage of the world population with a given gene
         * @return The percentage
         */
        public int GetPercentageGene(string gene) {
            int totalPop = 0;
            int genePop = 0;
    
            for (int x = 0; x<m_size; x++) {
                for (int y = 0; y<m_size; y++) {
                    Spot s = getSpot(x, y);
                    totalPop += s.getNbCreatures();
                    for (int i = 0; i<s.getNbCreatures(); i++) {
                        Creature c = s.getCreatureFromIndex(i);
                        if (c.hasGene(gene)) {
                           genePop += 1;
                        }
                    }
                }
            }
    
            if (totalPop == 0) {
                return 0;
            }
            else {
                return 100 * genePop / totalPop;
            }   
        }


        // Utility functions

        /*
         * Get a random number according to normal distribution
         * @param mean The center of the normal distribution
         * @param std The standard deviation of the normal distribution
         * @return A random double
         */
        private double normalDistribution(int mean, int std) {
            Random rand = new Random();
            double u1 = 1.0 - rand.NextDouble(); //uniform(0,1] random doubles
            double u2 = 1.0 - rand.NextDouble();
            double randStdNormal = Math.Sqrt(-2.0 * Math.Log(u1)) *
            Math.Sin(2.0 * Math.PI * u2); //random normal(0,1)
            double randNormal = mean + std * randStdNormal; //random normal(mean,stdDev^2)
            return randNormal;
        }

        public void NewEnv(Dictionary<string, Tuple<int, int>> globalEnv)
        {
            for (int y = 0; y < m_size; y++)
            {
                for (int x = 0; x < m_size; x++)
                {
                    Dictionary<string, int> env = new Dictionary<string, int>();
                    foreach (KeyValuePair<string, Tuple<int, int>> entry in globalEnv)
                    {
                        double envCharValue = normalDistribution(entry.Value.Item1, entry.Value.Item2);
                        env.Add(entry.Key, (int)envCharValue);
                    }
                    m_grid[y*x].NewEnv(env);
                }
            }
        }
    }
}
