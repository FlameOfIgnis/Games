﻿#pragma once
#include "Engine.h"

class S :public Actor {
public:

	S(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute, bool bPushable) : Actor(x, y, tag,delay, Direction, Attribute,bPushable) { } //inherits constructor from Actor base class

	void ActorTick() {
		if (ShouldItTick())
		{
			switch (GetDirection()) {		//this actor moves 1 space to its direction every frame
			case LEFT:AddPosition(-1, 0);
				break;
			case RIGHT:AddPosition(1, 0);
				break;
			case UP:AddPosition(0, -1);
				break;
			case DOWN:AddPosition(0, 1);
				break;
			}
		}
		
	}

	void OnCollision(Collision C){
		if (C.Instigator == (Actor*)ThisPlayer)
		{
			C.Instigator = this;		//if you hit player tell it you are the instigator and forward the collision struct
			ThisPlayer->OnCollision(C);
			return;
		}
		switch (GetDirection())		//if it collides with something it turns to the opposite direction
		{
		case RIGHT:		SetDirection(LEFT);
			break;
		case UP:		SetDirection(DOWN);
			break;
		case LEFT:		SetDirection(RIGHT);
			break;
		case DOWN:		SetDirection(UP);
			break;
		}
	}
};


class R :public Actor {		//this actor doesnt move, its just a boulder to collide with
public:
	R(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute, bool bPushable) : Actor(x, y, tag,delay, Direction, Attribute, bPushable) { }
private:
	Direction m_Direction;
	wchar_t m_tag;
};

class O :public Actor {
public:

	O(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute, bool bPushable) : Actor(x, y, tag, delay, Direction, Attribute, bPushable) { } //inherits constructor from Actor base class

	void ActorTick() {
		if (ShouldItTick())
		{
			switch (GetDirection()) {		//this actor moves 1 space to its direction every frame
			case LEFT:AddPosition(-1, 0);
				break;
			case RIGHT:AddPosition(1, 0);
				break;
			case UP:AddPosition(0, -1);
				break;
			case DOWN:AddPosition(0, 1);
				break;
			}
		}

	}

	void OnCollision(Collision C) {
		if (C.Instigator == (Actor*)ThisPlayer)
		{
			C.Instigator = this;		//if you hit player tell it you are the instigator and forward the collision struct
			ThisPlayer->OnCollision(C);
		}
			illShowMyselfOut();
			return;
	}
};


class T :public Actor {
public:

	T(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute, bool bPushable) : Actor(x, y, tag, delay, Direction, Attribute, bPushable) { } //inherits constructor from Actor base class

	void ActorTick() {
		if (ShouldItTick())
		{
			g_Engine->AppendToActors(new O(GetPosition().x, GetPosition().y+1, L'O', 10, DOWN, FOREGROUND_INTENSITY | FOREGROUND_RED | BACKGROUND,TRUE));
		}

	}

	void OnCollision(Collision C) {

	}
};

class Q :public Actor {
public:

	Q(int x, int y, wchar_t tag, int delay, Direction Direction, WORD Attribute, bool bPushable) : Actor(x, y, tag, delay, Direction, Attribute, bPushable) {  } //inherits constructor from Actor base class

	void ActorTick() {
	
	}

	void OnCollision(Collision C) {
		int x=GetPosition().x, y = GetPosition().y;
		switch (C.Direction) {		//this actor moves 1 space to its direction every frame
		case LEFT:x--;
			break;
		case RIGHT:x++;
			break;
		case UP:y--;
			break;
		case DOWN:y++;
			break;
		}

		if (C.Instigator == ThisPlayer)
		{
			struct s_node* cur = g_AllActors.head; //create pointer to start to the list containing all actors
			while (cur != NULL)						//traverse the list until the end
			{
				if (x == cur->thisActor->GetPosition().x		//for collision both current actor and node should have
					&& y == cur->thisActor->GetPosition().y		//same x,y and different adress pointer
					)
				{
					switch (C.Direction) {		//this actor moves 1 space to its direction every frame
					case LEFT:ThisPlayer->AddPosition(1, 0);
						break;
					case RIGHT:ThisPlayer->AddPosition(-1, 0);
						break;
					case UP:ThisPlayer->AddPosition(0, 1);
						break;
					case DOWN: ThisPlayer->AddPosition(0, -1);
						break;
					}
					break;
				}
				else {
					switch (C.Direction) {
					case LEFT:AddPosition(-1, 0);
						break;
					case RIGHT:AddPosition(1, 0);
						break;
					case UP:AddPosition(0, -1);
						break;
					case DOWN:AddPosition(0, 1);
						break;
					}
					break;
				}
				cur = cur->next;	//to next node
			}
		}
		
	}
private:

};

