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

        public bool colCard = false;
        public GameObject col;
        public Test test;

        // Use this for initialization
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }

        private void OnMouseEnter()
        {
            transform.localScale = new Vector3(1.8f, 1.8f, 1.8f);
        }

        private void OnMouseExit()
        {
            transform.localScale = new Vector3(1.5f, 1.5f, 1.5f);
        }

        private void OnMouseUp()
        {
            if (!test.infoActiv)
            {
                if (Creature && !player.isClick && !colCard)
                {
                    player.Click();
                }
                else if(player.isClick && !colCard)
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
                    if (colCard)
                    {
                        col.SendMessage("Colision", gameObject);
                        colCard = false;
                    }
                    else
                    {
                        ShowInfo();
                    }
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

        private void OnTriggerEnter2D(Collider2D collision)
        {
            if (collision.gameObject.tag == "Card")
            {
                col = collision.gameObject;
                colCard = true;
            }
        }

        private void OnTriggerStay2D(Collider2D collision)
        {
            if (collision.gameObject.tag == "Card")
            {
                colCard = true;
            }
        }

        private void OnTriggerExit2D(Collider2D collision)
        {
            colCard = false;
        }

        public void ChangeValue(int[] NewValue)
        {
            for (int i = 0; i < Value.Length; i++)
            {
                Value[i] += NewValue[i];
            }
            colCard = false;
        }
    }
}
