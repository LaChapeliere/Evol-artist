using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Threading;
using UnityEngine.UI;

namespace Application
{
    public class Test : MonoBehaviour
    {
        Thread m_thread;
        public int size = 6;
        public int nbCreature = 100;
        public int nbGeneration = 10;
        string testGenome = "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";
        private World myWorld;
        private Spot spot;
        //public List<string> DictionaryName = new List<string>();
        //public List<List<int>> DictionaryValue = new List<List<int>>();
        public Dictionary<string, Tuple<int, int>> globalEnv;
        public string[] DictionaryName = new string[0];
        public int[] DictionaryValue1 = new int[1];
        public int[] DictionaryValue2 = new int[1];
        public bool first = true;

        public Slider humidite;

        // Use this for initialization
        void Start()
        {
            globalEnv = new Dictionary<string, Tuple<int, int>>();
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

            Humidite();
            //m_thread = new Thread(TestFunction);
            //m_thread.Start();
        }

       void TestFunction()
        {
            globalEnv = new Dictionary<string, Tuple<int, int>>();
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

            if (first)
            {
                myWorld = new World(size, nbCreature, testGenome, globalEnv);
            }
            else
            {
                myWorld.NewEnv(globalEnv);
            }

            //Debug.Log("Pre-init");
            //globalEnv.Add("test", new Tuple<int, int>(50, 10));
            //globalEnv.Add("test2", new Tuple<int, int>(45, 0));
            //Debug.Log("Pre-world");
            //Debug.Log("Post-world");
            for (int i = 0; i < nbGeneration; i++)
            {
                //Debug.Log("Pre-simulation step");
                myWorld.RunSimulationStep();
                Debug.Log(myWorld.GetPercentageGene("CC"));
            }
            Debug.Log("End");
            first = false;
        }

        // Update is called once per frame
        void Update()
        {

        }

        public static void Print(string message)
        {
            //Debug.Log(message);
        }

        public static void Print2(string message)
        {
            Debug.Log(message);
        }

        private void OnApplicationQuit()
        {
            m_thread.Abort();
        }

        public void PlaySIM()
        {
            m_thread = new Thread(TestFunction);
            m_thread.Start();
        }

        public void Humidite()
        {
            DictionaryValue1[0] = (int)humidite.value;
            globalEnv["Humidite"] = new Tuple<int, int>(DictionaryValue1[0], DictionaryValue2[0]);
        }
    }
}