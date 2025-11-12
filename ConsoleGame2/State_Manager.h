#pragma once
#include "GameState.h"
#include "CursorScope.h"
class State_Manager
{
private:
	State_Manager();
	State_Manager(const State_Manager&) = delete;
	State_Manager& operator=(const State_Manager&) = delete;
public:
	std::unique_ptr<GameState> currentState;
	static State_Manager& getInstance();
	void changeState(std::unique_ptr<GameState> newState);
	void update();
	void render();
};

