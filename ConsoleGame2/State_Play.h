#pragma once
#include "GameState.h"
#include "Game.h"
#include "CursorScope.h"
#include "State_Menu.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>

#define PLAYER 0
#define GOAL 1
#define MAX_OBJ 22
#define ShStars MAX_OBJ / 2

enum Direction { UP, DOWN, LEFT, RIGHT };
struct Position
{ 
	short x; 
	short y; 
	Position(short x, short y) : x(x), y(y) {}

	Position operator + (const Position& other) const {	return Position(x + other.x, y + other.y); }
	Position operator - (const Position& other) const {	return Position(x - other.x, y - other.y); }
	bool operator ==(const Position& other) { return x == other.x && y == other.y; }
	bool operator !=(const Position& other) { return x != other.x || y != other.y; }


};
struct GO  
{  
	bool isActive = false;
	short id = 0;   
	Position currentPos = {0,0};  
	Position lastPos = {0,0};    
	Direction dir = UP;
};
struct Tails 
{
	bool isActive = false;
	Position currentPos = { 0,0 };
	Position lastPos = { 0,0 };
};


class State_Play : public GameState
{
	GO gameObjects[MAX_OBJ];
	int currentTailPos = 0;
	Tails tails[MAX_OBJ];
	bool switcher = false;
	bool isMovebale = true;
	// Inherited via GameState
	void Start() override;
	void Update() override;
	void Render() override;
	void Input();
	void UpdatePosition(Position newPos, GO& gameObject);
	void UpdateTails();
	void Check();
	void printBorder(Position Start, Position End);
	void ShootingStar(GO& go);
};

