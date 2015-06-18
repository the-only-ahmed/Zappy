using UnityEngine;
using System.Collections;

public class Winner : MonoBehaviour {

	private string		winner;

	void Start () {
		winner = PlayerPrefs.GetString("winner");
	}

	void OnGUI()
	{
		GUIStyle style = new GUIStyle();
		style.fontSize = 50;
		style.normal.textColor = Color.red;

		GUI.Label(new Rect(Screen.width / 2 - (winner.Length * 15), 10, 300, 50), winner, style);
	}
}
