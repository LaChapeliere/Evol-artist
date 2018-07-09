using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Application
{
    public class Card : MonoBehaviour
    {
        public int[] Value;
        public GameObject spawn;
        public GameObject hexa;

        private Vector3 screenPoint;
        public bool move = false;
        public Test test;

        // Use this for initialization
        void Start()
        {
            test = GameObject.Find("Simulation").GetComponent<Test>();
        }

        // Update is called once per frame
        void Update()
        {
            if (move)
            {
                Vector3 p = new Vector3();
                Camera c = Camera.main;
                Event e = Event.current;
                Vector2 mousePos = new Vector2();

                mousePos.x = Input.mousePosition.x;
                mousePos.y = c.pixelHeight - Input.mousePosition.y;

                p = c.ScreenToWorldPoint(new Vector3(mousePos.x, -mousePos.y, c.nearClipPlane));
                transform.position = new Vector3(p.x, p.y + 10, p.z);
            }
            if (Input.GetKeyDown(KeyCode.Mouse1))
            {
                move = false;
                transform.position = new Vector3(-12.5f, -4.3f, 0);
            }
        }

        void OnMouseDrag()
        {
            if (!test.infoActiv)
            {
                test.Card = this;
                //move = true;
                Vector3 p = new Vector3();
                Camera c = Camera.main;
                Event e = Event.current;
                Vector2 mousePos = new Vector2();

                mousePos.x = Input.mousePosition.x;
                mousePos.y = c.pixelHeight - Input.mousePosition.y;

                p = c.ScreenToWorldPoint(new Vector3(mousePos.x, -mousePos.y, c.nearClipPlane));
                transform.position = new Vector3(p.x, p.y + 10, p.z);
            }
        }
        private void OnMouseUp()
        {
            transform.position = new Vector3(-12.5f, -4.3f, 1.75f);
            if(hexa != null)
            {
<<<<<<< HEAD
                NewHexa NHexa = hexa.GetComponent<NewHexa>();
                if (NHexa.x > 0 && NHexa.x < 8 && NHexa.y > 0 && NHexa.y < 8)
                {
                    if ((NHexa.x != 1 || NHexa.y != 5) && (NHexa.x != 2 || NHexa.y != 6) && (NHexa.x != 3 || NHexa.y != 7)) {
                        if ((NHexa.y != 1 || NHexa.x != 5) && (NHexa.y != 2 || NHexa.x != 6) && (NHexa.y != 3 || NHexa.x != 7)) {
                            GameObject newTerrain;
                            newTerrain = Instantiate(Terrain, hexa.transform.position, hexa.transform.rotation);
                            newTerrain.GetComponent<Hexagone>().Value = Value;
                            newTerrain.GetComponent<Hexagone>().x = NHexa.x;
                            newTerrain.GetComponent<Hexagone>().y = NHexa.y;
                            test.Card = null;
                            Destroy(gameObject);
                        }
                    }
                }
=======
                Colision(hexa);
>>>>>>> a5ec8ee236a120813838b939dcc68c6e85e45707
            }
        }
    }
}
