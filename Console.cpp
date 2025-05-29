#include "Console.h"
#include <Windows.h>

// 커서 안 보이게 설정
void Console::CursorSettings()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 커서 이동(x, y 특정 좌표로 이동시켜 도형을 원하는 위치에 그림)
void Console::SetKeyCursor(int _nX, int _nY)
{
    COORD cursorPos = { (SHORT)_nX, (SHORT)_nY };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

void Console::ClearConsole()
{
    COORD topLeft = { 0, 0 };
    DWORD written, cells;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    cells = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', cells, topLeft, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, topLeft, &written);
    SetConsoleCursorPosition(hConsole, topLeft);
}