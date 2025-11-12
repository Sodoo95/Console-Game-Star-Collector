#pragma once
#include <iostream>
#include <Windows.h>
class CursorScope
{
    CONSOLE_SCREEN_BUFFER_INFO oldInfo;
    HANDLE hConsole;
    COORD newPos;

public:
    CursorScope(int x, int y) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsole, &oldInfo);

        newPos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hConsole, newPos);
    }

    ~CursorScope() {
        SetConsoleCursorPosition(hConsole, oldInfo.dwCursorPosition);
    }

    void newLine() {
        COORD newL = { newPos.X, newPos.Y + 1 };
        newPos = newL;
        SetConsoleCursorPosition(hConsole, newPos);
    }
};

