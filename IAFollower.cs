using UnityEngine;
using System.Collections;

public class IAFollower : MonoBehaviour {

	#region Attributes
	public float movingSpeed = 0.3f;
	private Animator animator;
	protected AnimateState CharacterAnimationState = AnimateState.idle;
	protected enum AnimateState
	{
		walk_forward,
		idle
	}
	
	protected bool	isMoving = false;
	private int orientation = 0;
	private int dist = 0;
	
	private float x, z;
	#endregion

	void Start() {
		animator = GetComponent<Animator>();
	}

	virtual protected void Update () {
		if (Input.GetMouseButton(0) || isMoving)
		{
			isMoving = true;
			CharacterAnimationState = AnimateState.walk_forward;
			walk(orientation);
			PlayAnimation();
		}
	}

//	Vector3 curScreenPoint = new Vector3(Input.mousePosition.x, Input.mousePosition.y, screenPoint.z);
//	Vector3 curPosition = Camera.main.ScreenToWorldPoint(curScreenPoint) + offset;

	/*private bool isOnIt()
	{
		bool isOnX = transform.position.x >= x - 0.4f && transform.position.x <= x + 0.4f;
		bool isOnZ = Mathf.Abs(transform.position.z) >= z - 0.4f && Mathf.Abs(transform.position.z) <= z + 0.4f;
		print("bool = " + isOnZ);
		print("actual z = " + transform.position.z);
		print("box z = " + z);
		
		return (isOnX && isOnZ);
	}
	
	public void move(float x, float z, int orientation)
	{
		this.orientation = orientation;
		this.x = x;
		this.z = z;
		isMoving = true;
	}
	
	public void move(bool isMoving)
	{
		this.isMoving = isMoving;
		if (!isMoving)
		{
			CharacterAnimationState = AnimateState.idle;
			PlayAnimation();
		}
	}
	
	protected Vector3 choseTarget(int orientation)
	{
		Vector3 target = transform.forward;
		switch (orientation)
		{
		case 1:
			target = new Vector3(0.0f, 0.0f, 1.0f);
			break;
		case 2:
			target = new Vector3(1.0f, 0.0f, 0.0f);
			break;
		case 3:
			target = new Vector3(0.0f, 0.0f, -1.0f);
			break;
		case 4:
			target = new Vector3(-1.0f, 0.0f, 0.0f);
			break;
		}
		return target;
	}*/
	
	protected void walk (int orientation) {
		Vector3 curScreenPoint = new Vector3(Input.mousePosition.x, Input.mousePosition.y, Input.mousePosition.z);
		Vector3 target = Camera.main.ScreenToWorldPoint(curScreenPoint);
		target.z = 0;

//		Vector3 target = choseTarget(orientation);
		
		CharacterAnimationState = AnimateState.walk_forward;
		transform.position += target * movingSpeed * (float)Time.deltaTime;
		dist++;

		CharacterAnimationState = AnimateState.idle;
		isMoving = false;
		dist = 0;
	}
	
	protected void PlayAnimation () {
		switch (CharacterAnimationState) {
		case AnimateState.idle : animator.SetTrigger ("idle");
			break;
		case AnimateState.walk_forward : animator.SetTrigger ("walk_forward");
			break;
		}

		
	}
}
