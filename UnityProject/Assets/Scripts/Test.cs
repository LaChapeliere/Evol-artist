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

        // Use this for initialization
        void Start()
        {
            m_thread = new Thread(TestFunction);
            m_thread.Start();
        }

       void TestFunction()
        {
            Debug.Log("Pre-init");
            Dictionary<string, Tuple<int, int>> globalEnv = new Dictionary<string, Tuple<int, int>>();
            globalEnv.Add("test", new Tuple<int, int>(50, 10));
            globalEnv.Add("test2", new Tuple<int, int>(45, 0));

            string testGenome = "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";

            Debug.Log("Pre-world");
            World myWorld = new World(6, 100, testGenome, globalEnv);
            Debug.Log("Post-world");
            for (int i = 0; i < 10; i++)
            {
                Debug.Log("Pre-simulation step");
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
            Debug.Log(message);
        }

        private void OnApplicationQuit()
        {
            m_thread.Abort();
        }
    }
}