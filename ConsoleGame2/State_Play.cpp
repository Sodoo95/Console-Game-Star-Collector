#include "State_Play.h"
int counter;

void State_Play::Start()
{
	counter = 0;

	for (int i = 0; i < MAX_OBJ; i++)
	{
		gameObjects[i].isActive = true;
		gameObjects[i].id = i;
		gameObjects[i].currentPos = { (short)(31 + (rand() % 69)), (short)(6+(rand() % 24)) };
		gameObjects[i].dir = (Direction)(rand() % 4);
		gameObjects[i].lastPos = gameObjects[i].currentPos;
	}
	printBorder({30,5}, {100,30});
	printBorder({ 30, 2 }, { 52, 5 });
	printBorder({ 2, 14 }, { 30, 24 });
	printBorder({ 100, 6 }, { 125, 13 });
	
	{
		CursorScope scope(5,16);
		printf(" 動き      上");												scope.newLine();
		printf(" 方法      |     ");											scope.newLine();
		printf("          [\033[1;32mW\033[0m]");							scope.newLine();
		printf("  左--[\033[1;32mA\033[0m]     [\033[1;32mD\033[0m]--右");	scope.newLine();
		printf("          [\033[1;32mS\033[0m]");							scope.newLine();
		printf("           |     ");										scope.newLine();
		printf("           下");												scope.newLine();
	}

	{
		CursorScope scope(103, 8);
		printf("\033[1;32mゲームルール：　\033[0m");												scope.newLine();
		printf("　");												scope.newLine();
		printf("　星を全部を集めて\033[1;33m@\033[0mへ");												scope.newLine();
		printf("　行ってください！！！");												scope.newLine();

	}
	{
		CursorScope scope(103, 15);
		printf("[ \033[1;33m↑\033[0m ] : プレイヤー"); scope.newLine();
		printf("[ \033[1;31m*\033[0m ] : 星"); scope.newLine();
		printf("[ \033[1;32m*\033[0m ] : 集めた星"); scope.newLine();
		printf("[ \033[1;34m*\033[0m ] : 流れ星"); scope.newLine();
		printf("[ \033[1;33m@\033[0m ] : ゴール"); scope.newLine();
	}

	{
		CursorScope scope(6, 10);
		printf("\033[1;33m ///");												scope.newLine();
		printf("d^_^b");												scope.newLine();
		printf("-| |-");												scope.newLine();
		printf(" / |\033[0m");												scope.newLine();
	}
	{
		CursorScope scope(11, 7);
		printf("  *--------------*");												scope.newLine();
		printf("  |              |");												scope.newLine();
		printf("  |              |");												scope.newLine();
		printf(" /               |");												scope.newLine();
		printf("/________________*");												scope.newLine();

	}


}

void State_Play::Update()
{
	
	counter++;


	Input();
	if (counter == 100)
	{
		for (int i = MAX_OBJ - ShStars; i < MAX_OBJ; i++)
		{
			ShootingStar(gameObjects[i]);
		}
		counter = 0;
	}

}

void State_Play::Render()  
{  
	for (GO& obj : gameObjects)
	{
		if (obj.isActive)
		{
			if (obj.id != PLAYER)
			{
				if (obj.lastPos != obj.currentPos)
				{
					CursorScope scope(obj.lastPos.x, obj.lastPos.y);
					printf(" ");
				}
			}
			CursorScope scope(obj.currentPos.x, obj.currentPos.y);
			if (obj.id == PLAYER)
			{
				switch (obj.dir)
				{
				case    UP:  printf("\033[1;33m↑\033[0m");  break;
				case  DOWN:  printf("\033[1;33m↓\033[0m");  break;
				case  LEFT:  printf("\033[1;33m←\033[0m");  break;
				case RIGHT:  printf("\033[1;33m→\033[0m");  break;
				}

			}
			else if (obj.id == GOAL)
			{
				printf("\033[1;33m@\033[0m");
			}
			else if (obj.id >= MAX_OBJ - ShStars)
			{
				printf("\033[1;34m*\033[0m");
			}
			else
			{
				printf("\033[1;31m*\033[0m");
			}
		}
    }  



}

void State_Play::Input()
{
	if (!_kbhit())
		return;	
	Position newPos = {0, 0};

	int key = _getch();

	
	switch (key)
	{
		case 'w':
			if (gameObjects[PLAYER].currentPos.y > 6 && isMovebale)
			{ 
				Check();
				newPos.y = -1;
				Check();
				gameObjects[PLAYER].dir = UP;
			}
			break;
		case 's':
			if (gameObjects[PLAYER].currentPos.y < 29 && isMovebale)
			{
				Check();
				newPos.y = 1;
				Check();
				gameObjects[PLAYER].dir = DOWN;
			}
			break;
		case 'a':
			if (gameObjects[PLAYER].currentPos.x > 31 && isMovebale)
			{
				Check();
				newPos.x = -1;
				Check();
				gameObjects[PLAYER].dir = LEFT;
			}
			break;
		case 'd':
			if (gameObjects[PLAYER].currentPos.x < 99 && isMovebale)
			{
				Check();
				newPos.x = 1;
				Check();
				gameObjects[PLAYER].dir = RIGHT;
			}
			break;
		case 'm':
			State_Manager::getInstance().changeState(std::make_unique<State_Menu>());
			return;
		default:
			break;
	}
	UpdatePosition(newPos, gameObjects[PLAYER]);
	UpdateTails();

	{
		CursorScope scope(35, 3);
		printf("集めた星: %d", currentTailPos); scope.newLine();
		printf("頑張って!!!");
	}

		
}
void State_Play::UpdatePosition(Position newPos, GO& gameObject)
{
	gameObject.lastPos = gameObject.currentPos;
	gameObject.currentPos = gameObject.currentPos + newPos;
}
void State_Play::UpdateTails()
{
	tails[0].lastPos = tails[0].currentPos;
	tails[0].currentPos = gameObjects[PLAYER].lastPos;

	for (int i = 1; i < MAX_OBJ; i++)
	{
		tails[i].lastPos = tails[i].currentPos;
		tails[i].currentPos = tails[i - 1].lastPos;
	}

	for (int i = 0; i < MAX_OBJ; i++)
	{
		if (tails[i].isActive)
		{
			{
				CursorScope scope(tails[i].currentPos.x, tails[i].currentPos.y);
				printf("\033[1;32m*\033[0m");
			}
			{
				CursorScope scope(tails[i].lastPos.x, tails[i].lastPos.y);
				printf(" ");
			}
		}
		
		if(currentTailPos == 0)
		{
			CursorScope scope(gameObjects[PLAYER].lastPos.x, gameObjects[PLAYER].lastPos.y);
			printf(" ");
		}

	}
}
void State_Play::Check()
{
	for (int i = 0; i < MAX_OBJ; i++)
	{
		if (gameObjects[i].id != PLAYER && gameObjects[i].id != GOAL)
		{
			if (gameObjects[PLAYER].currentPos == gameObjects[i].currentPos)
			{
				gameObjects[i].isActive = false;
				gameObjects[i].currentPos = { 140, 0 };

				tails[currentTailPos].isActive = true;
				currentTailPos++;		
				if (!switcher) 
				{
					CursorScope scope(15, 8);
					printf("%s", "すごいです。"); scope.newLine();
					printf("%s", "　　　　　　"); scope.newLine();
					printf("%s", "　　　　　　"); scope.newLine();
					switcher = true;
				}
				else
				{
					CursorScope scope(15, 8);
					printf("%s", "もうちょっと"); scope.newLine();
					printf("%s", "　　　　　　"); scope.newLine();
					printf("%s", "　　　　　　"); scope.newLine();
					switcher = false;
				}

				
			}
		}
	}

	if (gameObjects[PLAYER].currentPos == gameObjects[GOAL].currentPos)
	{
		if (currentTailPos == MAX_OBJ - 2)
		{	
			{
				CursorScope scope(64, 10);
				printf("\033[1;33mお\033[0m"); scope.newLine();
				Sleep(500);
				printf("\033[1;33mめ\033[0m"); scope.newLine();
				Sleep(500);
				printf("\033[1;33mで\033[0m"); scope.newLine();
				Sleep(500);
				printf("\033[1;33mと\033[0m"); scope.newLine();
				Sleep(500);
				printf("\033[1;33mう\033[0m"); scope.newLine();
				Sleep(500);
				printf("\033[1;33m。\033[0m"); scope.newLine();
				Sleep(500);
				printf("\033[1;33m。\033[0m"); scope.newLine();
			}

			for (GO obj : gameObjects) obj.isActive = false;

			{
				CursorScope scope(50, 18);
				printf("\033[1;32m[M]\033[0mを押してメニューへ戻ってください。");
			}
			isMovebale = false;
			
		}
		else 
		{			
			{
				CursorScope scope(15, 8);
				printf("%s", "まだです！！"); scope.newLine();
				printf("%s", "もう星が"); scope.newLine();
				printf("%s", "　あります。"); scope.newLine();

			}
		} 

	}
}

void State_Play::printBorder(Position Start, Position End)
{
	for (short x = Start.x; x <= End.x; x++)
	{
		for (short y = Start.y; y <= End.y; y++)
		{
			CursorScope scope(x, y);
			if (y == Start.y || y == End.y)
			{
				printf("*");
			}
			else if (x == Start.x || x == End.x)
			{
				printf("*");
			}
		}
	}
}

void State_Play::ShootingStar(GO& go)
{
	Position newPos = { 0,0 };


	switch (go.dir)
	{
	case UP:
		if (go.currentPos.y > 6)
		newPos.y = -1;
		else go.dir = DOWN;
		break;
	case DOWN:
		if (go.currentPos.y < 29)
		newPos.y = 1;
		else go.dir = UP;
		break;
	case LEFT:
		if (go.currentPos.x > 31)
		newPos.x = -1;
		else go.dir = RIGHT;
		break;
	case RIGHT:
		if (go.currentPos.x < 99)
		newPos.x = 1;
		else go.dir = LEFT;
		break;
	}
	UpdatePosition(newPos, go);
}


