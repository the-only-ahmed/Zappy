using UnityEngine;
using System.Collections;
using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;

public class Client : MonoBehaviour {

	internal Boolean		socketReady = false;

	public Texture			grass;
	public Texture			oeuf;
	public GameObject[]		particles = new GameObject[6];
	public GameObject		player;

	public String			Host;// = "127.0.0.1";
	public Int32			Port;// = 4242;

	private bool			go = false;
	private TcpClient		mySocket;
	private NetworkStream	theStream;
	private StreamWriter	theWriter;
	private StreamReader	theReader;

	private int				teamsNb = 0;
	public List<GameObject>	team = new List<GameObject>();
	private string			message = "test";
	private TheGame			game = new TheGame();

	private bool			said = false;
	private int				frame = 0;
	private int				sgt = 0;

	void Start ()
	{
		Host = PlayerPrefs.GetString("host");
		Port = Convert.ToInt32(PlayerPrefs.GetString("port"));
		player.name = "player ";
		setupSocket();
		message = readSocket();
		if (message.Equals("BIENVENUE"))
		{
			go = true;
			writeSocket("GRAPHIC");
		}
	}

	void Update()
	{
		if (!PlayerPrefs.GetString("pin").Equals("false"))
		{
			if (!said)
			{
				writeSocket("pin " + PlayerPrefs.GetString("pin"));
				writeSocket("plv " + PlayerPrefs.GetString("plv"));
				said = true;
			}
		}
		else
			said = false;

		message = readSocket();

		if (String.IsNullOrEmpty(message))
		{
			if ((teamsNb == 0 || frame >= 20) && go)
			{
				frame = 0;
				writeSocket("fuck");
			}
		}

		if (message.Length > 3 && message.Substring(0, 3).Equals("tna"))
		{
			teamsNb = message.Split(' ').Length;
			string[] args = message.Split(' ');
			bool i = false;
			foreach (string str in args)
			{
				if (!i)
					i = true;
				else
				{
					GameObject obj = new GameObject();
					obj.name = str;
					team.Add(obj);
				}
			}
		}
		else if (go && (message.Length > 3 && message.Substring(0, 3).Equals("seg")))
		{
			PlayerPrefs.SetString("winner", message);
			Application.LoadLevel(2);
		}
		if (message.Length > 3 && message.Substring(0, 3).Equals("sgt"))
		{
			string[] args = message.Split(' ');
			sgt = int.Parse(args[1]);
		}
		else if (go)
			game.goGame(message, grass, player, team, oeuf, particles);

		frame++;
	}

	void OnGUI()
	{
		GUI.Box(new Rect(25, Screen.height - 30, 100, 25), "Time : " + sgt);
		if (GUI.Button(new Rect(5, Screen.height - 30, 20, 25), "+"))
		{
			sgt += 10;
			writeSocket("sst " + sgt);
		}
		if (GUI.Button(new Rect(125, Screen.height - 30, 20, 25), "-"))
		{
			if (sgt > 10)
			{
				sgt -= 10;
				writeSocket("sst " + sgt);
			}
		}

		if (teamsNb > 0)
		{
			GUI.BeginGroup(new Rect(0, 10, 40 * teamsNb, 25 * teamsNb));
			GUI.Box(new Rect(0, 0, 40 * teamsNb, 25 * teamsNb), "");
				for (int i = 0;i < team.Count;i++)
					GUI.Label(new Rect(0, 25 * i + 1, 100, 25), " " + (i + 1) + "- " + team[i].name);
			GUI.EndGroup();
		}
	}

	public void setupSocket()
	{
		try {
			mySocket = new TcpClient(Host, Port);
			theStream = mySocket.GetStream();
			theWriter = new StreamWriter(theStream);
			theReader = new StreamReader(theStream);
			socketReady = true;
		}
		catch (Exception e) {
			Debug.Log("Socket error: " + e);
			Application.LoadLevel(0);
		}
	}

	public void writeSocket(string theLine)
	{
		if (!socketReady)
			return;
		string foo = theLine + "\n";
		theWriter.Write(foo);
		theWriter.Flush();
	}

	public String readSocket()
	{
		if (!socketReady)
			return "";
		if (theStream.DataAvailable)
			return theReader.ReadLine();
		else
			return "";
	}

	public void closeSocket()
	{
		if (!socketReady)
			return;
		theWriter.Close();
		theReader.Close();
		mySocket.Close();
		socketReady = false;
	}
}
