using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Application
{
    public class PlayerCreature : MonoBehaviour
    {
        public GameObject selection;
        public List<GameObject> hexagone;
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
                isClick = false;
                selection.SetActive(false);
                int i = 0;
                while (destination != hexagone[i] && i < 38)
                {
                    i++;
                }
                Hexagone NewHexa = hexagone[i].GetComponent<Hexagone>();
                Hexagone hexa = hexagone[CaseActu].GetComponent<Hexagone>();
                if ((NewHexa.x <= hexa.x + 1 || NewHexa.x >= hexa.x - 1) && (NewHexa.y <= hexa.y + 1 || NewHexa.y >= hexa.y - 1)) {
                    transform.position = destination.transform.position;
                    hexa.Creature = false;
                    CaseActu = i;
                    NewHexa.Creature = true;
                    Deplacement--;
                }
            }
        }
    }
}
