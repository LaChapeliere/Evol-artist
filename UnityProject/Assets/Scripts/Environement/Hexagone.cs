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
        public int[] Value;

        public Text[] text;
        public GameObject info;

        public Test test;

        public int x;
        public int y;

        // Use this for initialization
        void Start()
        {
<<<<<<< HEAD
<<<<<<< HEAD
            player = GameObject.Find("cat").GetComponent<PlayerCreature>();
            text[0] = GameObject.Find("Humidity").GetComponent<Text>();
            text[1] = GameObject.Find("Nourriture").GetComponent<Text>();
            text[2] = GameObject.Find("Predator").GetComponent<Text>();
            info = GameObject.Find("Info");
            test = GameObject.Find("Simulation").GetComponent<Test>();

            gameObject.GetComponent<SpriteRenderer>().sortingOrder = x + y;

            player.hexagone.Add(gameObject);
=======

>>>>>>> a5ec8ee236a120813838b939dcc68c6e85e45707
=======

>>>>>>> parent of e4663e3... Beta 1.1.0
        }

        // Update is called once per frame
        void Update()
        {

        }

        private void OnMouseEnter()
        {
            transform.localScale = new Vector3(1, 1, 1);
            if(test.Card != null)
            {
                test.Card.hexa = gameObject;
            }
        }

        private void OnMouseExit()
        {
            transform.localScale = new Vector3(0.8f, 0.8f, 0.8f);
            if (test.Card != null)
            {
                test.Card.hexa = null;
            }
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
            test.infoActiv = true;
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
