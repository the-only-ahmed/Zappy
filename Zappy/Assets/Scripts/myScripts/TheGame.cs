using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class TheGame : MonoBehaviour {

	private GameObject[,]		cube = null;
	private List<GameObject>	spieler = new List<GameObject>();
	private List<GameObject>	eggs = new List<GameObject>();
	private List<GameObject>	incant = new List<GameObject>();

	public	TheGame() {}

	private GameObject[,] createMap(string msg, Texture grass)
	{
		string[] args = msg.Split(' ');

		int a = int.Parse(args[1]);
		int b = int.Parse(args[2]);

		GameObject[,] cube = new GameObject[a, b];

		float	x = 0.0f, y = 0.0f;
		for (int i = 0;i < a;i++)
		{
			float z = 0.0f;
			for (int j = 0;j < b;j++)
			{
				cube[i, j] = GameObject.CreatePrimitive(PrimitiveType.Cube);
				cube[i, j].transform.position = new Vector3(x, y, z);
				cube[i, j].transform.localScale = new Vector3(1.0f, 0.2f, 1.0f);
				cube[i, j].renderer.material.mainTexture = grass;

				cube[i, j].name = "X " + x + " Y " + (-z);

				GameObject target = GameObject.CreatePrimitive(PrimitiveType.Capsule);
				target.transform.parent = cube[i, j].transform;

				target.GetComponent<CapsuleCollider>().enabled = false;

				target.GetComponent<MeshRenderer>().enabled = false;
				target.transform.localScale = new Vector3(0.5f, 10, 0.5f);
				target.transform.position = new Vector3(x, 0.5f, z);
				target.name = "target";

				target.AddComponent<BoxHandler>();

				z--;
			}
			x++;
		}
		return cube;
	}

	private void	getContent(string msg)
	{
		string[] args = msg.Split(' ');

		Transform tr = cube[int.Parse(args[1]), int.Parse(args[2])].transform.Find("ressources");

		if (tr != null)
			Destroy(tr.gameObject);

		GameObject res = new GameObject("ressources");
		res.transform.parent = cube[int.Parse(args[1]), int.Parse(args[2])].transform;

		float x = cube[int.Parse(args[1]), int.Parse(args[2])].transform.position.x;
		float z = cube[int.Parse(args[1]), int.Parse(args[2])].transform.position.z;

		for (int i = 3;i < 10;i++)
		{
			for (int j = 0;j < int.Parse(args[i]);j++)
			{
				GameObject obj = GameObject.CreatePrimitive(PrimitiveType.Sphere);
				obj.GetComponent<SphereCollider>().enabled = false;
				obj.transform.parent = res.transform;
				obj.transform.position = new Vector3(UnityEngine.Random.Range(x - 0.4f, x + 0.4f), 0.1f, UnityEngine.Random.Range(z - 0.4f, z + 0.4f));
				obj.transform.localScale = new Vector3(0.05f, 0.05f, 0.05f);

				Rigidbody gameObjectsRigidBody = obj.AddComponent<Rigidbody>();
				obj.rigidbody.useGravity = false;
				gameObjectsRigidBody.mass = 5;
				switch (i)
				{
					case 3:
						obj.name = "Nourriture";
						obj.renderer.material.color = Color.red;
					break;
					case 4:
						obj.name = "Linemate";
						obj.renderer.material.color = Color.green;
					break;
					case 5:
						obj.name = "Deraumere";
						obj.renderer.material.color = Color.blue;
					break;
					case 6:
						obj.name = "Sibur";
						obj.renderer.material.color = Color.cyan;
					break;
					case 7:
						obj.name = "Mendiane";
						obj.renderer.material.color = Color.yellow;
					break;
					case 8:
						obj.name = "Phiras";
						obj.renderer.material.color = Color.black;
					break;
					default:
						obj.name = "Thystame";
						obj.renderer.material.color = Color.white;
					break;
				}
			}
		}
	}

	private void	createPlayer(string msg, GameObject player, List<GameObject> team)
	{
		string[] args = msg.Split(' ');

		float x = float.Parse(args[2]);
		float z = float.Parse(args[3]);

		GameObject obj = Instantiate(player) as GameObject;

		float cubeX = cube[Convert.ToInt32(x), Convert.ToInt32(z)].transform.position.x;
		float cubeY = cube[Convert.ToInt32(x), Convert.ToInt32(z)].transform.position.y + 1.0f;
		float cubeZ = cube[Convert.ToInt32(x), Convert.ToInt32(z)].transform.position.z;

		obj.transform.position = new Vector3(cubeX, cubeY, cubeZ);

		obj.transform.localScale = new Vector3(0.5f, 0.5f, 0.5f);
		switch (int.Parse(args[4]))
		{
			case 2:
				obj.transform.rotation = Quaternion.Euler(0.0f, 90.0f, 0.0f);
			break;
			case 3:
				obj.transform.rotation = Quaternion.Euler(0.0f, 180.0f, 0.0f);
			break;
			case 4:
				obj.transform.rotation = Quaternion.Euler(0.0f, 270.0f, 0.0f);
			break;
			default:
				obj.transform.rotation = Quaternion.Euler(0.0f, 0.0f, 0.0f);
			break;
		}
		obj.name = player.name + args[1];
		int id = team.FindIndex(delegate(GameObject item) {return item.name == args[6];});
		obj.transform.parent = team[id].transform;
		spieler.Add(obj);
	}

	protected void RotateTo (GameObject pl, int x)
	{
		switch (x)
		{
			case 2:
				pl.transform.rotation = Quaternion.Euler(0.0f, 90.0f, 0.0f);
			break;
			case 3:
				pl.transform.rotation = Quaternion.Euler(0.0f, 180.0f, 0.0f);
			break;
			case 4:
				pl.transform.rotation = Quaternion.Euler(0.0f, 270.0f, 0.0f);
			break;
			default:
				pl.transform.rotation = Quaternion.Euler(0.0f, 0.0f, 0.0f);
			break;
		}
	}

	private GameObject	movePlayer(string msg)
	{
		string[] args = msg.Split(' ');

		foreach (GameObject pl in spieler)
		{
			float x = pl.transform.position.x;
			float z = Math.Abs(pl.transform.position.z);
			string[] pln = pl.name.Split(' ');

			if (pln[1].Equals(args[1]))
			{
				if (!(x >= float.Parse(args[2]) - 0.5f && x <= float.Parse(args[2]) + 0.5f) || !(z >= float.Parse(args[3]) - 0.5f && z <= float.Parse(args[3]) + 0.5f))
				{
					GameObject target = GameObject.Find(cube[int.Parse(args[2]), int.Parse(args[3])].name + "/target");
					target.GetComponent<CapsuleCollider>().enabled = true;
					target.GetComponent<CapsuleCollider>().isTrigger = true;
					target.GetComponent<MeshRenderer>().enabled = true;
					int a = int.Parse(args[2]);
					int b = int.Parse(args[3]);
					pl.transform.position = new Vector3(a, cube[a, b].transform.position.y + 1.0f, -b);

				}

				return pl;
			}
		}
		return null;
	}

	private Vector3	killPlayer(string msg, GameObject failing)
	{
		string[] args = msg.Split(' ');
		Vector3 pos = new Vector3(0, 0, 0);

		if (args[0].Equals("pdi"))
		{
			foreach (GameObject pl in spieler)
			{
				string[] pln = pl.name.Split(' ');

				if (pln[1].Equals(args[1]))
				{
					pos = pl.transform.position;
					spieler.Remove(pl);
					Destroy(pl);

					GameObject fail = Instantiate(failing) as GameObject;
					fail.transform.position = new Vector3(pos.x, 0.5f, pos.z);
					fail.name = "fail";
					Destroy(fail, 5.0f);

					break;
				}
			}
		}
		else
		{
			foreach (GameObject pl in eggs)
			{
				string[] pln = pl.name.Split(' ');

				if (pln[1].Equals(args[1]))
				{
					pos = pl.transform.position;
					eggs.Remove(pl);
					Destroy(pl);

					GameObject fail = Instantiate(failing) as GameObject;
					fail.transform.position = new Vector3(pos.x, 0.5f, pos.z);
					fail.name = "fail";
					Destroy(fail, 5.0f);

					break;
				}
			}
		}
		return pos;
	}

	private void	setInventory(string msg, GameObject levelUp)
	{
		string[] args = msg.Split(' ');

		foreach (GameObject pl in spieler)
		{
			string[] pln = pl.name.Split(' ');

			if (pln[1].Equals(args[1]))
			{
				Inventory inv = pl.GetComponent<Inventory>();
				if (msg.Substring(0, 3).Equals("pin"))
				{
					inv.setNourriture(int.Parse(args[4]));
					inv.setLinemate(int.Parse(args[5]));
					inv.setDeraumere(int.Parse(args[6]));
					inv.setSibur(int.Parse(args[7]));
					inv.setMendiane(int.Parse(args[8]));
					inv.setPhiras(int.Parse(args[9]));
					inv.setThystame(int.Parse(args[10]));
				}
				else
				{
					if (inv.getLevel() < int.Parse(args[2]))
					{
						GameObject celeb = Instantiate(levelUp) as GameObject;
						celeb.transform.position = pl.transform.position;
						celeb.name = "levelUp";
						Destroy(celeb, 3.0f);
					}
					inv.setLevel(int.Parse(args[2]));
				}
				break;
			}
		}
	}

	private void	sendBroadcast(string msg)
	{
		string[] args = msg.Split(' ');

		foreach (GameObject pl in spieler)
		{
			string[] pln = pl.name.Split(' ');

			if (pln[1].Equals(args[1]))
			{
				Inventory inv = pl.GetComponent<Inventory>();
				inv.setBroadcast(args[2], true);
				break;
			}
		}
	}

	private void ResThings(string msg)
	{
		string[] args = msg.Split(' ');

		foreach (GameObject pl in spieler)
		{
			string[] pln = pl.name.Split(' ');

			if (pln[1].Equals(args[1]))
			{
				EatDrop res = pl.GetComponent<EatDrop>();
				res.jump();
				break;
			}
		}
	}

	private void eggManagement(string msg, Texture oeuf, GameObject particles)
	{
		string[] args = msg.Split(' ');

		if (args[0].Equals("enw"))
		{
			int x = int.Parse(args[3]);
			int z = -(int.Parse(args[4]));

			GameObject obj = GameObject.CreatePrimitive(PrimitiveType.Capsule);
			obj.GetComponent<CapsuleCollider>().enabled = false;

			obj.transform.position = new Vector3(UnityEngine.Random.Range(x - 0.3f, x + 0.3f), 0.5f, UnityEngine.Random.Range(z - 0.3f, z + 0.3f));
			obj.transform.localScale = new Vector3(0.1f, 0.1f, 0.1f);

			obj.renderer.material.mainTexture = oeuf;

			Rigidbody gameObjectsRigidBody = obj.AddComponent<Rigidbody>();
			obj.rigidbody.useGravity = false;
			gameObjectsRigidBody.mass = 5;

			obj.name = "oeuf " + args[1];
			eggs.Add(obj);

			GameObject egg = Instantiate(particles) as GameObject;
			egg.transform.position = obj.transform.position;
			egg.name = "egg";

			Destroy(egg, 3.0f);
		}
	}

	private void incantationStart(string msg, GameObject[] particles)
	{
		string[] args = msg.Split(' ');

		GameObject inc = Instantiate(particles[2]) as GameObject;
		inc.transform.position = new Vector3(float.Parse(args[1]), 0.5f, -float.Parse(args[2]));
		inc.name = "in X" + args[1] + " Y" + args[2];
		incant.Add(inc);
	}

	private void incantationEnd(string msg, GameObject[] particles)
	{
		string[] args = msg.Split(' ');
		string target = "in X" + args[1] + " Y" + args[2];

		foreach (GameObject inc in incant)
		{
			if (inc.name.Equals(target))
			{
				incant.Remove(inc);
				Destroy(inc, 5.0f);
				break;
			}
		}

		if (int.Parse(args[3]) == 1)
		{
			GameObject success = Instantiate(particles[3]) as GameObject;
			success.transform.position = new Vector3(float.Parse(args[1]), 0.5f, -float.Parse(args[2]));
			success.name = "success";

			Destroy(success, 5.0f);
		}
		else
		{
			GameObject fail = Instantiate(particles[4]) as GameObject;
			fail.transform.position = new Vector3(float.Parse(args[1]), 0.5f, -float.Parse(args[2]));
			fail.name = "fail";

			Destroy(fail, 5.0f);
		}
	}

	private void changeEgg(string msg, GameObject anim, GameObject kill)
	{
		string[] args = msg.Split(' ');

		Vector3 pos = killPlayer("edi " + args[1], kill);
		GameObject changed = Instantiate(anim) as GameObject;
		changed.transform.position = pos;
		changed.name = "born";

		Destroy(changed, 3.0f);
	}

	public void goGame(string msg, Texture grass, GameObject player, List<GameObject> team, Texture oeuf, GameObject[] particles)
	{
		if (msg.Length < 3)
			return ;

		switch (msg.Substring(0, 3))
		{
			case "msz":
				cube = createMap(msg, grass);
			break;
			case "bct":
				getContent(msg);
			break;
			case "pnw":
				createPlayer(msg, player, team);
			break;
			case "ppo":
			{
				GameObject pl = movePlayer(msg);
				string[] args = msg.Split(' ');
				RotateTo(pl, int.Parse(args[4]));
			}
			break;
			case "pdi":
			case "edi":
				killPlayer(msg, particles[4]);
			break;
			case "pin":
			case "plv":
				setInventory(msg, particles[1]);
			break;
			case "pgt":
			case "pfk":
			case "pdr":
				ResThings(msg);
			break;
			case "enw":
			case "eht":
				eggManagement(msg, oeuf, particles[0]);
			break;
			case "pic":
				incantationStart(msg, particles);
			break;
			case "pie":
				incantationEnd(msg, particles);
			break;
			case "ebo":
				changeEgg(msg, particles[5], particles[4]);
			break;
			case "pbc":
				sendBroadcast(msg);
			break;
		}
	}
}
