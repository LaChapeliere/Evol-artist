using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Threading;

namespace Application
{
    public class Test : MonoBehaviour
    {
        Thread m_thread;
        public int size = 6;
        public int nbCreature = 100;
        public int nbGeneration = 10;
        //public List<string> DictionaryName = new List<string>();
        //public List<List<int>> DictionaryValue = new List<List<int>>();
        public Dictionary<string, Tuple<int, int>> globalEnv;
        public string[] DictionaryName = new string[0];
        public int[] DictionaryValue1 = new int[0];
        public int[] DictionaryValue2 = new int[0];

        // Use this for initialization
        void Start()
        {
            m_thread = new Thread(TestFunction);
            m_thread.Start();
        }

       void TestFunction()
        {
            //Debug.Log("Pre-init");
            globalEnv = new Dictionary<string, Tuple<int, int>>();
            //globalEnv.Add("test", new Tuple<int, int>(50, 10));
            //globalEnv.Add("test2", new Tuple<int, int>(45, 0));
            if (DictionaryValue1.Length >= DictionaryName.Length & DictionaryValue2.Length >= DictionaryName.Length)
            {
                for (int i = 0; i < DictionaryName.Length; i++)
                {
                    globalEnv.Add(DictionaryName[i], new Tuple<int, int>(DictionaryValue1[i], DictionaryValue2[i]));
                }
            }
            else
            {
                Debug.Log("Error, environement can't be load");
            }

            string testGenome = "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";

            //Debug.Log("Pre-world");
            World myWorld = new World(size, nbCreature, testGenome, globalEnv);
            //Debug.Log("Post-world");
            for (int i = 0; i < nbGeneration; i++)
            {
                //Debug.Log("Pre-simulation step");
                myWorld.RunSimulationStep();
                Debug.Log(myWorld.GetPercentageGene("CC"));
            }
            Debug.Log("End");
        }

        // Update is called once per frame
        void Update()
        {

        }

        public static void Print(string message)
        {
            //Debug.Log(message);
        }

        private void OnApplicationQuit()
        {
            m_thread.Abort();
        }
    }
}