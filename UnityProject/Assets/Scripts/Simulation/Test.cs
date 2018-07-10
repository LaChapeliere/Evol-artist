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

        private int Percent;
        private bool IsPlaying = false;

        // Use this for initialization
        void Start()
        {
<<<<<<< HEAD
<<<<<<< HEAD
            //info.SetActive(false);
<<<<<<< HEAD
            Output = GameObject.Find("Output").GetComponent<Text>();
=======
            info.SetActive(false);
>>>>>>> a5ec8ee236a120813838b939dcc68c6e85e45707
=======
<<<<<<< HEAD
            info.SetActive(false);
>>>>>>> parent of e4663e3... Beta 1.1.0
=======
>>>>>>> parent of 0ce98fc... lands on grid with number
>>>>>>> 7920fa99a6449bacb124030e6a3f6c9b72926822
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

                int output = UnityEngine.Random.Range(0, card.Length - 1);
                GameObject obj;
                obj = Instantiate(card[output], new Vector3(-12.5f, -4.3f, 0), transform.rotation);
                obj.GetComponent<Card>().move = false;
                obj.transform.position = new Vector3(-12.5f, -4.3f, 0);

                IsPlaying = true;

                m_thread = new Thread(TestFunction);
                m_thread.Start();
            }
        }

        public void CloseInfo()
        {
            info.SetActive(false);
            infoActiv = false;
        }
    }
}