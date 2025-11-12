#include "State_Menu.h"

void State_Menu::Start()
{
	system("cls"); 
	GameState::Start();
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	COORD currentPos = info.dwCursorPosition;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 3 });
	printf("                                     +-------------------- Sodo Production --------------------+\n");
	printf("                                     |                                                         |\n");
	printf("                                     |        *                                            *   |\n");
	printf("                                     |                                           *             |\n");
	printf("                                     |                                  *                      |\n");
	printf("                                     |       |#####|  |#####|     /###|  |######|  |#####|     |\n");
	printf("                                     |      /#/         |#|      /#/|#|  |#|  |#| /#/          |\n");
	printf("                                     |      |######|    |#|  *  /#/ |#|  |####|   |######|     |\n");
	printf("                                     |        *  |#|    |#|    /######|  |#|  |#|      |#|     |\n");
	printf("                                     |      |#####/     |#|   /#/   |#|  |#|  |#| |#####/      |\n");
	printf("                                     |                                                         |\n");
	printf("                                     |  *                  *                                   |\n");
	printf("                                     |                                                         |\n");
	printf("                                     |                               *                         |\n");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 17 });
	printf("                                     |                                              *          |\n");
	printf("                                     |    *                        *                           |\n");
	printf("                                     |                                                         |\n");
	printf("                                     |           *                                             |\n");
	printf("                                     |                  Press \033[1;32m'Enter' to START\033[0m         *       |\n");
	printf("                                     |                          *                       *      |\n");
	printf("                                     |                                                         |\n");
	printf("                                     |                   Press \033[1;31m'Esc' to QUIT\033[0m               *   |\n");
	printf("                                     |    *                                                    |\n");
	printf("                                     |                      *             *            *       |\n");
	printf("                                     |            *                                            |\n");
	printf("                                     +-------------------- Sodo Production --------------------+\n");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPos);
}

void State_Menu::Update()
{
	GameState::Update();
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
	{
		State_Manager::getInstance().changeState(std::make_unique<State_Play>());
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) 
	{
		printf("Exiting game...\n");
		exit(0);
	}
}

void State_Menu::Render()
{

}
