#include "State_Manager.h"
State_Manager::State_Manager() : currentState(nullptr) {}

State_Manager& State_Manager::getInstance()
{
	static State_Manager instance;
	return instance;
}
void State_Manager::changeState(std::unique_ptr<GameState> newState)
{
	system("cls");
	currentState = move(newState);
	if (currentState) currentState->Start();
}
void State_Manager::update()
{
	if (currentState) currentState->Update();
}
void State_Manager::render()
{
	if (currentState) currentState->Render();
}