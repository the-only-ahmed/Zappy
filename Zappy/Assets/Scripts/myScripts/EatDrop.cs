using UnityEngine;
using System.Collections;

public class EatDrop : MonoBehaviour {

	protected AnimateState CharacterAnimationState = AnimateState.idle;
	protected enum AnimateState
	{
		jump,
		idle
	}

	public void jump()
	{
		CharacterAnimationState = AnimateState.jump;
		PlayAnimation();
		CharacterAnimationState = AnimateState.idle;
		PlayAnimation();
	}

	protected void PlayAnimation () {
		switch (CharacterAnimationState)
		{
		case AnimateState.idle:animation.CrossFade("idle");
			break;
		case AnimateState.jump:animation.CrossFade("jump_pose");
			break;
		}
	}
}
