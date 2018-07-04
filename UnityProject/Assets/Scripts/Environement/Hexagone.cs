using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Hexagone : MonoBehaviour {

    public int[] Value;

    public Text[] text;
    public GameObject info;

    public bool colCard;
    public GameObject col;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnMouseEnter()
    {
        transform.localScale = new Vector3(1.8f, 1.8f, 1.8f);
    }

    private void OnMouseExit()
    {
        transform.localScale = new Vector3(1.5f, 1.5f, 1.5f);
    }

    private void OnMouseDown()
    {
        if(Input.GetKey(KeyCode.RightArrow))
        {
            transform.Translate(1, 1, 0);
        }
        if (colCard)
        {
            col.SendMessage("Colision", gameObject);
        }
        else
        {
            text[0].text = "Humidity: " + Value[0];
            text[1].text = "Food: " + Value[1];
            text[2].text = "Predator: " + Value[2];
            info.SetActive(true);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "Card")
        {
            col = collision.gameObject;
            colCard = true;
        }
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        colCard = false;
    }

    public void ChangeValue(int[] NewValue)
    {
        for(int i = 0; i < Value.Length; i++)
        {
            Value[i] += NewValue[i];
        }
        colCard = false;
    }
}
