using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace Application
{
    public class Spot
    {
        private static Random rng = new Random();

        /*
         * Pointer to world
         */
        private World m_world;

        /*
         * Horizontal coordinate of the position in the world grid
         */
        private int m_x;

        /*
         * Vertical coordinate of the position in the world grid
         */
        private int m_y;

        /*
         * List of Creatures (pointers) on this spot
         */
        private List<Creature> m_creatures = null;

        /*
         * Dictionary describing the environment
         */
        private Dictionary<string, int> m_env;

        /*
         * Spot constructor
         * @param world Pointer to the world
         * @param x Horizontal coordinate
         * @param y Vertical coordinate
         * @param env Dictionnary describing the environment
         */
        public Spot(World world, int x, int y, Dictionary<string, int> env)
        {
            m_world = world;
            m_x = x;
            m_y = y;
            m_env = env;
        }

        /*
         * Give the number of creatures on the spot
         * @return The length of m_creatures
         */
        public int getNbCreatures() {
            return m_creatures.Count;
        }

        /*
         * Give the pointer to a specific creature of the spot
         * @param id Index of the desired creature in m_creatures
         * @return The value of m_creatures[id]
         */
        public Creature getCreatureFromIndex(int id) {
            return m_creatures[id];
        }

        /*
         * Accessor of the m_env variable
         * @return The value of m_env
         */
        public Dictionary<string, int> getEnv() {
            return m_env;
        }

        /*
         * Add a creature to the spot
         * @param creaturePointer The added Creature
         */
        public void addCreature(Creature creature) {
            m_creatures.Add(creature);
        }

        /*
         * Remove a specific creature from the spot
         * @param id Identifier of the creature to remove from m_creatures
         */
        public void removeCreature(int id) {
            var itemToRemove = m_creatures.SingleOrDefault(r => r.getId() == id);
            if (itemToRemove != null)
            {
                m_creatures.Remove(itemToRemove);
            }
        }

        /*
         * Genetic algorithm reproduction step. Each pair of parents create 10 offsprings
         */
        public void nextStepPop() {
            // Create new generation
            List<Creature> newGeneration = null;

            // Get random order of creatures
            m_creatures.Shuffle();

            // For each creature decide if reproduction
            Creature firstParent = null;
            Creature secondParent = null;
            for (int i = 0; i < m_creatures.Count; i++)
            {
                int dice = rng.Next(0,101);
                int fitness = m_creatures[i].getFitness();
                if (dice < fitness)
                {
                    if (firstParent == null)
                    {
                        firstParent = m_creatures[i];
                    }
                    else
                    {
                        secondParent = m_creatures[i];
                        //Ten offsprings
                        for (int c = 0; c < 10; c++)
                        {
                            newGeneration.Add(sexualReproduction(firstParent, secondParent));
                        }
                        firstParent = null;
                        secondParent = null;
                    }
                }
                Test.Print("test");
            }

            //Remove old generation
            m_creatures.Clear();

            // Cap population at 50 creatures
            newGeneration.Shuffle();
            List<Creature> newGenerationCut = newGeneration.GetRange(0, 50);

            // Distribute new generation between this spot and its neighbours
            for (int i = 0; i < newGenerationCut.Count; i++)
            {
                int xModifier = rng.Next(0, 3) - 1;
                int yModifier = rng.Next(0, 3) - 1;
                int xReal = (m_x + xModifier + m_world.getSize()) % m_world.getSize();
                int yReal = (m_y + yModifier + m_world.getSize()) % m_world.getSize();
                m_world.getSpot(xReal, yReal).addCreature(newGenerationCut[i]);
            }
        }

        /*
         * Creature a descendant of two Creatures
         * @param firstParent One parent Creature
         * @param secondParent One parent Creature
         * @return The child Creature
         */
        public Creature sexualReproduction(Creature firstParent, Creature secondParent) {
            Tuple<int, int> parentCoords = firstParent.getCoord();

            // Genome is that of combination of parents plus mutation step
            List<string> parentGenomes = null;
            parentGenomes.Add(firstParent.getGenome());
            parentGenomes.Add(secondParent.getGenome());
            int selectedParent = 0;
            string genome = "";
            const int i = 100000;
            for (int c = 0; c < parentGenomes[selectedParent].Length; c++)
            {
                // Copy selected parent genome
                char newBase = parentGenomes[selectedParent][c];
                genome += newBase;

                int r = rng.Next(0,i);
                if (r <= m_world.getCrossoverRate() * i)
                {
                    // Crossover
                    // Change the selected parent genome
                    selectedParent = (selectedParent + 1) % 2;
                }

                r = rng.Next(0, i);
                if (r <= m_world.getMutationRate() * i)
                {
                    //Mutation
                    List<char> bases = m_world.getPossibleBases();
                    char mutationBase = bases[rng.Next(0, bases.Count)];
                    //genome[c] = mutationBase;
                    StringBuilder sb = new StringBuilder(genome);
                    sb[c] = mutationBase;
                    genome = sb.ToString();
                }
            }

            return new Creature(m_world.getNewCreatureId(), genome, parentCoords.Item1, parentCoords.Item1, m_env);
        }
    }

    public static class List {

        private static Random rng = new Random();

        /*
         * Shuffle a list
         * @param list The list to shuffle
         */
        public static void Shuffle<T>(this IList<T> list)
        {
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = rng.Next(n + 1);
                T value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }
    }
}
