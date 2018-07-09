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

        private int Percent;
        private bool IsPlaying = false;

        public Text Output;

        // Use this for initialization
        void Start()
        {
            //info.SetActive(false);
            Output = GameObject.Find("Output").GetComponent<Text>();
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
                Percent = myWorld.GetPercentageGene("CC");
                Debug.Log(Percent);
            }
            if (Percent > 10)
            {
                Debug.Log("End");
                first = false;
            }
            else
            {
                Debug.Log("your creature is dead");
                first = true;
            }
            IsPlaying = false;
        }

        // Update is called once per frame
        void Update()
        {
            Output.text = Percent.ToString();
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
            if (!IsPlaying)
            {
                hexa = player.hexagone[player.CaseActu].GetComponent<Hexagone>();
                Value1[0] = hexa.Value[0];
                player.Deplacement = 1;

                int output = UnityEngine.Random.Range(0, card.Length);
                GameObject obj;
                obj = Instantiate(card[output], new Vector3(-0.3f, -6, 2.75f), transform.rotation);
                obj.transform.position = new Vector3(-0.3f, -6, 2.75f);

                IsPlaying = true;

                m_thread = new Thread(TestFunction);
                m_thread.Start();
            }
        }

        public void CloseInfo()
        {
            //info.SetActive(false);
            infoActiv = false;
        }
    }
}