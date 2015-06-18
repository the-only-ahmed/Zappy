using UnityEngine;
using System.Collections;
using System;

public class Inventory : MonoBehaviour {

	private int		nourriture;
	private int		linemate;
	private int		deraumere;
	private int		sibur;
	private int		mendiane;
	private int		phiras;
	private int		thystame;
	private int		level;

	private bool	show = false;
	private bool	broad = false;

	private string	msg = "";

	public int		getNourriture() {return nourriture;}
	public int		getLinemate() {return linemate;}
	public int		getDeraumere() {return deraumere;}
	public int		getSibur() {return sibur;}
	public int		getMendiane() {return mendiane;}
	public int		getPhiras() {return phiras;}
	public int		getThystame() {return thystame;}
	public int		getLevel() {return level;}

	public void		setNourriture(int nourriture) {this.nourriture = nourriture;}
	public void		setLinemate(int linemate) {this.linemate = linemate;}
	public void		setDeraumere(int deraumere) {this.deraumere = deraumere;}
	public void		setSibur(int sibur) {this.sibur = sibur;}
	public void		setMendiane(int mendiane) {this.mendiane = mendiane;}
	public void		setPhiras(int phiras) {this.phiras = phiras;}
	public void		setThystame(int thystame) {this.thystame = thystame;}
	public void		setLevel(int level) {this.level = level;}
	public void		setBroadcast(string msg, bool broad) {this.msg = msg; this.broad = broad;}

	public Inventory()
	{
		level = 1;
		nourriture = 0;
		linemate = 0;
		deraumere = 0;
		sibur = 0;
		mendiane = 0;
		phiras = 0;
		thystame = 0;
	}

	private IEnumerator waiting(int bol)
	{
		yield return new WaitForSeconds(3);
		if (bol == 0)
			show = false;
		else
			broad = false;
	}

	void OnGUI()
	{
		if (show)
		{
			PlayerPrefs.SetString("pin", "false");
			PlayerPrefs.SetString("plv", "false");
			GUI.BeginGroup(new Rect(Screen.width - 400, 10, 400, 300));

				GUI.Box(new Rect(0, 0, 400, 300), "");

				GUIStyle style = new GUIStyle();
				style.fontSize = 25;
				style.normal.textColor = Color.red;

				GUI.Label(new Rect(165, 10, 100, 25), transform.name, style);

				GUI.color = Color.white;
				GUI.Label(new Rect(175, 50, 100, 25), "Level : ");
				GUI.color = Color.green;
				GUI.Label(new Rect(220, 50, 100, 25), level.ToString());

				GUI.color = Color.white;
				GUI.Label(new Rect(175, 75, 100, 25), "Team : ");
				GUI.color = Color.blue;
				GUI.Label(new Rect(220, 75, 100, 25), transform.parent.name);

				GUI.color = Color.white;
				GUI.Label(new Rect(175, 100, 100, 25), "nourriture = " + nourriture);
				GUI.Label(new Rect(175, 125, 100, 25), "linemate = " + linemate);
				GUI.Label(new Rect(175, 150, 100, 25), "deraumere = " + deraumere);
				GUI.Label(new Rect(175, 175, 100, 25), "sibur = " + sibur);
				GUI.Label(new Rect(175, 200, 100, 25), "mendiane = " + mendiane);
				GUI.Label(new Rect(175, 225, 100, 25), "phiras = " + phiras);
				GUI.Label(new Rect(175, 250, 100, 25), "thystame = " + thystame);

			GUI.EndGroup();

			StartCoroutine("waiting", 0);
		}
		if (broad)
		{

			Vector3 screenPos = Camera.main.WorldToScreenPoint(transform.position);
			GUI.Box(new Rect(screenPos.x, screenPos.z, msg.Length * 15, 25), msg);
			StartCoroutine("waiting", 1);
		}
	}

	private void OnMouseDown() {
		show = true;
		PlayerPrefs.SetString("pin", transform.name.Substring(7));
		PlayerPrefs.SetString("plv", transform.name.Substring(7));
	}

}
