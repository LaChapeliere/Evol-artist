using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Application
{
    public class Hexagone : MonoBehaviour
    {
        public bool Creature = false;
        public PlayerCreature player;
        public int[] Value = new int[5];

        public Text[] text = new Text[3];
        public GameObject info;

        public Test test;

        // Use this for initialization
        void Start()
        {
            player = GameObject.Find("cat").GetComponent<PlayerCreature>();
            text[0] = GameObject.Find("Humidity").GetComponent<Text>();
            text[1] = GameObject.Find("Nourriture").GetComponent<Text>();
            text[2] = GameObject.Find("Predator").GetComponent<Text>();
            info = GameObject.Find("Info");
            test = GameObject.Find("Simulation").GetComponent<Test>();         
        }

        // Update is called once per frame
        void Update()
        {

        }

        private void OnMouseEnter()
        {
            transform.localScale = new Vector3(0.25f, 0.25f, 0.25f);
            /*if(test.Card != null)
            {
                test.Card.hexa = gameObject;
            }*/
        }

        private void OnMouseExit()
        {
            transform.localScale = new Vector3(0.2f, 0.2f, 0.2f);
            /*if (test.Card != null)
            {
                test.Card.hexa = null;
            }*/
        }

        private void OnMouseUp()
        {
            if (!test.infoActiv)
            {
                if (Creature && !player.isClick)
                {
                    player.Click();
                }
                else if(player.isClick)
                {
                    if (Creature)
                    {
                        ShowInfo();
                        player.isClick = false;
                        player.Annuler();
                    }
                    else
                    {
                        player.Move(gameObject);
                    }
                }
                else
                {
                    ShowInfo();
                }
            }
        }

        public void ShowInfo()
        {
            text[0].text = "Humidity: " + Value[0];
            text[1].text = "Food: " + Value[1];
            text[2].text = "Predator: " + Value[2];
            info.SetActive(true);
            //test.infoActiv = true;
        }

        public void ChangeValue(int[] NewValue)
        {
            for (int i = 0; i < Value.Length; i++)
            {
                Value[i] += NewValue[i];
            }
        }
    }
}
