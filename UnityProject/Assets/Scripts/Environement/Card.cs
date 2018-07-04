using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Application
{
    public class Card : MonoBehaviour
    {
        public int[] Value;
        public GameObject[] card;
        public GameObject spawn;

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

        void OnMouseDown()
        {
            if (!test.infoActiv)
            {
                move = true;
            }
        }

        public void Colision(GameObject col)
        {
            col.SendMessage("ChangeValue", Value);
            int output = Random.Range(0, card.Length - 1);
            GameObject obj;
            obj = Instantiate(card[output], new Vector3(-12.5f, -4.3f, 0), transform.rotation);
            obj.GetComponent<Card>().move = false;
            obj.transform.position = new Vector3(-12.5f, -4.3f, 0);
            Destroy(gameObject);
        }
    }
}
