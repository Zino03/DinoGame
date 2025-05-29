#include "Console.h"
#include <Windows.h>

// 커서 안 보이게 설정
void Console::CursorSettings()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; // 커서 사이즈
    cursorInfo.bVisible = FALSE; // 커서 보이기 여부 false (안 보이게 설정)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 설정한 커서 정보 적용
}

// 커서 이동(x, y 특정 좌표로 이동시켜 도형을 원하는 위치에 그림)
void Console::SetKeyCursor(int _nX, int _nY)
{
    COORD cursorPos = { (SHORT)_nX, (SHORT)_nY }; // 커서에 특정 좌표 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos); // 설정한 커서 정보 적용
}
