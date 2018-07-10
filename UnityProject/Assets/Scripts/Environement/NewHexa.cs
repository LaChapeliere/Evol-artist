using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Application
{
    public class NewHexa : MonoBehaviour
    {

        public Test test;
        public Collider2D col;

        // Use this for initialization
        void Start()
        {
            test = GameObject.Find("Simulation").GetComponent<Test>();
            col = gameObject.GetComponent<Collider2D>();
            col.enabled = false;
        }

        // Update is called once per frame
        void Update()
        {
            if (test.Card == null)
            {
                col.enabled = false;
            }
            else
            {
                col.enabled = true;
            }
        }

        private void OnMouseEnter()
        {
            if (test.Card != null)
            {
                test.Card.hexa = gameObject;
            }
        }

        private void OnMouseExit()
        {
            if (test.Card != null)
            {
                test.Card.hexa = null;
            }
        }
    }
}
