using UnityEngine;
using System.Collections;

public class BoxHandler : MonoBehaviour {

	void OnTriggerEnter(Collider other)
	{
		GameObject player = other.gameObject;
		if (player.name.Substring(0, 6) == "player")
		{
			IAFollower ia = player.GetComponent<IAFollower>();
			ia.move(false);
			transform.GetComponent<CapsuleCollider>().enabled = false;
			transform.GetComponent<MeshRenderer>().enabled = false;
		}
	}

}
