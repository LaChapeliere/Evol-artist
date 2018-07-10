using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Application
{
    public class PlayerCreature : MonoBehaviour
    {
        public GameObject selection;
        public GameObject[] hexagone;
        public Test test;
        public int CaseActu = 0;
        public bool isClick = false;
        public int Deplacement = 1;
        // Use this for initialization
        void Start()
        {
            transform.position = hexagone[CaseActu].transform.position;
            hexagone[CaseActu].GetComponent<Hexagone>().Creature = true;
            selection.SetActive(false);
        }

        // Update is called once per frame
        void Update()
        {
            if(Input.GetKeyDown(KeyCode.Mouse1))
            {
                Annuler();
            }
        }

        public void Annuler()
        {
            isClick = false;
            selection.SetActive(false);
        }

        public void Click()
        {
            isClick = true;
            selection.SetActive(true);
        }

        public void Move(GameObject destination)
        {
            if (Deplacement > 0)
            {
                transform.position = destination.transform.position;
                isClick = false;
                selection.SetActive(false);
                int i = 0;
                while (destination != hexagone[i])
                {
                    i++;
                }
                hexagone[CaseActu].GetComponent<Hexagone>().Creature = false;
                CaseActu = i;
                hexagone[CaseActu].GetComponent<Hexagone>().Creature = true;
                Deplacement--;
                Deplacement--;
            }
        }
    }
}
