#pragma once
#include "State_Manager.h"
#include "State_Play.h"
#include "GameState.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
class State_Menu : public GameState
{
	// Inherited via GameState
	void Start() override;
	void Update() override;
	void Render() override;
};

