using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace Application
{
    public class Test : MonoBehaviour
    {

        // Use this for initialization
        void Start()
        {
            Dictionary<string, Tuple<int, int>> globalEnv = new Dictionary<string, Tuple<int, int>>();
            globalEnv.Add("test", new Tuple<int, int>(50, 10));
            globalEnv.Add("test2", new Tuple<int, int>(45, 0));

            string testGenome = "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";

            World myWorld = new World(6, 100, testGenome, globalEnv);
            for (int i = 0; i < 1; i++)
            {
                myWorld.RunSimulationStep();
                Debug.Log(myWorld.GetPercentageGene("CC"));
            }
        }

        // Update is called once per frame
        void Update()
        {

        }
    }
}