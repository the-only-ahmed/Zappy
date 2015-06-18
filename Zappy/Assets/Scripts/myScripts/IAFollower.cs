using UnityEngine;
using System.Collections;
using System;

public class IAFollower : MonoBehaviour {

	public float movingSpeed = 5 ;
	protected AnimateState CharacterAnimationState = AnimateState.idle ;
	protected enum AnimateState
	{
		run,
		idle
	}

	protected bool	isMoving = false;
	private int orientation = 0;

	private int dist = 0;

	private float x, z;

	virtual protected void Update () {
		if (isMoving)
		{
			walk(orientation);
			PlayAnimation();
		}
	}

	private bool isOnIt()
	{
		bool isOnX = transform.position.x >= x - 0.4f && transform.position.x <= x + 0.4f;
		bool isOnZ = Math.Abs(transform.position.z) >= z - 0.4f && Math.Abs(transform.position.z) <= z + 0.4f;
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
	}

	protected void walk (int orientation) {

		Vector3 target = choseTarget(orientation);

		if (!isOnIt() && dist < 6)
		{
			CharacterAnimationState = AnimateState.run;
			transform.position += target * movingSpeed * (float)Time.deltaTime;
			dist++;
		}
		else {
			CharacterAnimationState = AnimateState.idle;
			isMoving = false;
			dist = 0;
		}
	}

	protected void PlayAnimation () {
		switch (CharacterAnimationState)
		{
		case AnimateState.idle:animation.CrossFade("idle");
			break;
		case AnimateState.run:animation.CrossFade("run");
			break;
		}
	}
}
