using UnityEngine;
using System.Collections;
using System;

public class menu_object : MonoBehaviour {

	public bool isQuit=false;

	public string host;
	public string port;

	void OnGUI ()
	{

		GUI.BeginGroup(new Rect(Screen.width / 2 - 200, Screen.height / 2 + 50, 400, 75));

			GUI.Box(new Rect(0, 0, 400, 75), "");

				host = GUI.TextField(new Rect(50, 25, 300, 25), host);
				port = GUI.TextField(new Rect(50, 50, 300, 25), port);

				PlayerPrefs.SetString("host", host);
				PlayerPrefs.SetString("port", port);
				PlayerPrefs.SetString("pin", "false");

		GUI.EndGroup();
	}

	void OnMouseEnter()
	{
		renderer.material.color=Color.red;
	}

	void OnMouseExit()
	{
		renderer.material.color=Color.white;
	}

	void OnMouseDown()
	{
		if(isQuit)
		{
			Application.Quit();
		}
		else
		{
			if (!String.IsNullOrEmpty(host) && !String.IsNullOrEmpty(port))
				Application.LoadLevel(1);
		}
	}
}
