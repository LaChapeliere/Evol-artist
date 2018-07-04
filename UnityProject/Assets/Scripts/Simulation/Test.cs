using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Threading;

namespace Application
{
    public class Test : MonoBehaviour
    {
        World myWorld;
        Hexagone hexa;
        public PlayerCreature player;
        Thread m_thread;
        public string testGenome = "ABCEBDDEBCDBBDCBCADDCEBCDBBCDDDCEBCDBBCDADDDEBCDBBDBBCBCCDDCABCADCCEBDEBBDABDCBEBDDEEDABCCECADDDEBCADBCE";
        public int Size;
        public int NbCreature;
        public int NbGeneration;
        public string[] Environement;
        public int[] Value1;
        public int[] Value2;

        public GameObject info;
        public bool infoActiv = false;

        public bool first = true;

        public Card Card;
        public GameObject[] card;

        // Use this for initialization
        void Start()
        {
            info.SetActive(false);
        }

       void TestFunction()
        {
            //Debug.Log("Pre-init");
            Dictionary<string, Tuple<int, int>> globalEnv = new Dictionary<string, Tuple<int, int>>();
            if (Value1.Length >= Environement.Length && Value2.Length >= Environement.Length)
            {
                for (int i = 0; i < Environement.Length; i++)
                {
                    globalEnv.Add(Environement[i], new Tuple<int, int>(Value1[i], Value2[i]));
                }
            }
            //globalEnv.Add("test", new Tuple<int, int>(50, 10));
            //globalEnv.Add("test2", new Tuple<int, int>(45, 0));

            //Debug.Log("Pre-world");
            if (first)
            {
                myWorld = new World(Size, NbCreature, testGenome, globalEnv);
            }
            else
            {
                myWorld.NewEnvironement(globalEnv);
            }
            //Debug.Log("Post-world");
            for (int i = 0; i < NbGeneration; i++)
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

        private void OnApplicationQuit()
        {
            m_thread.Abort();
        }

        public void StartSimulation()
        {
            hexa = player.hexagone[player.CaseActu].GetComponent<Hexagone>();
            Value1[0] = hexa.Value[0];

            int output = UnityEngine.Random.Range(0, card.Length - 1);
            GameObject obj;
            obj = Instantiate(card[output], new Vector3(-12.5f, -4.3f, 0), transform.rotation);
            obj.GetComponent<Card>().move = false;
            obj.transform.position = new Vector3(-12.5f, -4.3f, 0);

            m_thread = new Thread(TestFunction);
            m_thread.Start();
        }

        public void CloseInfo()
        {
            info.SetActive(false);
            infoActiv = false;
        }
    }
}