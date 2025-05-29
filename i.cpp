#include <iostream>
#include <Windows.h>
#include <conio.h>

#define PRINTLN(STR)	{printf(STR);printf("\n");} // 줄바꿈 매크로

constexpr int KEY_ESC = 27;			// ESC 키
constexpr int KEY_SPACE = 32;		// SpaceBar 키
// _getch()는 아스키코드로 키를 반환하기 때문에 숫자 상수로 비교하도록 함

constexpr int MAX_JUMP = 6;			// 최대 점프 높이
constexpr int Y_BASE = 10;			// 공룡의 초기 Y축 위치
constexpr int Y_COLLISION = 4;		// Y축의 충돌 기준 위치
constexpr int TREE_COLLISION = 7;	// 나무가 공룡과 충돌 가능한 X축 위치
constexpr int TREE_START = 50;		// 나무가 생성되는 위치
constexpr int TREE_END = -6;		// 나무가 사라지는 위치
constexpr int SLEEP_TIME = 35;		// 게임 갱신 주기


/**
키 눌림 확인
@param
@return
*/
int GetKeyDown()
{
	if (_kbhit() != 0) // 키가 눌렸는지 확인
		return _getch(); // 버퍼 없이 키가 눌린 즉시 읽음
	return 0; // 키가 없으면 0 반환
}


/**
커서 관련 설정 (커서 안보이기)
@param
@return
*/
void CursorSettings()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE; // 커서를 화면에 보이지 않게 설정
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/**
커서 옮기기
@param		_nX		X위치
@param		_nY		Y위치
@return
*/
void SetKeyCursor(int _nX, int _nY)
{
	COORD cursorPos = { (SHORT)_nX, (SHORT)_nY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
	// 콘솔 커서를 특정 좌표로 이동시켜 도형을 원하는 위치에 그릴 수 있게 함
}

/**
점수판 그리기
@param		nScore	점수
@return
*/
void DrawScore(int nScore)
{
	SetKeyCursor(0, 0); // 맨 왼쪽 상단
	printf("Score : %d\n", nScore); // 점수 출력
}

/**
공룡 그리기
@param		nY		공룡의 Y위치
@return
*/
void DrawDino(int nY)
{
	static bool bFootToggle = false;	// 공룡 그리기가 갱신될 때 발의 위치를 바꿈
	SetKeyCursor(0, Y_BASE - nY);		// 공룡의 그리기 위치 변경 (점프 높이에 따라 위로 이동해서 그려짐)

	PRINTLN("    o");
	PRINTLN("    o");
	PRINTLN("oooo");
	if (bFootToggle)
		PRINTLN("  o") // 발 모양 1
	else
		PRINTLN("    o") // 발 모양 2

	bFootToggle = !bFootToggle;
}

/**
나무 그리기
@param		nX		나무의 X위치
@return
*/
void DrawTree(int nX)
{
	// 나무 위치에 따라 크기를 변경해서 멀어지는 효과 표현
	if (nX >= 0)
	{ // 기본 상태
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("    o");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("o  o");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("ooo");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("  o");
	}
	else if (nX >= -2)
	{ // 조금 멀어짐
		nX = 0;
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("  o");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("  o");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("oo");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("o");
	}
	else if (nX >= -4)
	{ // 더 멀어짐
		nX = 0;
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("o");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("o");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("o");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("");
	}
}

/**
게임 시작
@param
@return
*/
void GameStart()
{
	int nScore = 0;				// 점수
	int nCurKey = -1;			// 현재 눌린 키

	int nYPos = 0;				// 공룡의 Y위치 (점프에 쓰임)
	int nTreePos = TREE_START;	// 나무가 생성되는 초기 X위치

	bool bIsJumpping = false;	// 현재 공룡이 점프 중인가
	bool bIsJumpped = false;	// 현재 공룡이 점프하여 최고 지점에 올랐는가
	bool bIsCollision = false;	// 현재 공룡이 나무와 충돌하였는가

	while (true)
	{
		// 점수 출력
		DrawScore(nScore);

		// 키 입력 확인
		nCurKey = GetKeyDown();
		switch (nCurKey)
		{
			case KEY_ESC:		// ESC 키 -> 종료
				return;
			case KEY_SPACE:		// SPACE BAR 키 -> 점프
  				bIsJumpping = true;
				break;
			default:
				break;
		}

		// 점프 키를 누를 시 상승 후 최고점 도달 후 하강 순서, 
		// 점프 중이 아니지만 공중에 있으면 착지(중력)

		// 점프 중인지 확인
		if (bIsJumpping)
		{
			// 최고 지점에 이르지 않았다면 Y축 값 상승
			if (nYPos < MAX_JUMP &&
				bIsJumpped == false)
				nYPos++;
			// 최고 지점에 도달 후 점프가 끝났다면 
			else if (bIsJumpped &&
				nYPos == 0)
			{
				bIsJumpped = false;
				bIsJumpping = false; // 점프 중 아님
			}
			// 최고 지점에 도달 후라면 (중력을 표현) Y축 값 감소
			else if (bIsJumpped)
				nYPos--;
			// 최고 지점에 도달했다면 
			else if (nYPos == MAX_JUMP)
				bIsJumpped = true; // 이제 내려가기 위해 true 설정
		}
		// 점프 중이 아닌데 공중에 있으면 Y가 0이 될 때까지 감소
		else
		{
			if (nYPos > 0)
				nYPos--;
		}

		// 나무 위치 관련
		if (nTreePos > TREE_END)
			nTreePos -= 2; // 왼쪽으로 이동
		else
			nTreePos = TREE_START; // 오른쪽 끝에서 생성

		// 충돌 관련
		// 나무의 X위치가 충돌 가능 X위치라면
		if (nTreePos < TREE_COLLISION)
		{
			// 공룡의 Y위치가 충돌 가능 위치이고
			// 나무의 X위치가 충돌 가능 위치라면
			if (nYPos < Y_COLLISION &&
				nTreePos > TREE_END + 1)
				bIsCollision = true;
		}

		// 나무 그리기
		DrawTree(nTreePos);
		// 공룡 그리기
		DrawDino(nYPos);

		Sleep(SLEEP_TIME); // 대기
		system("cls"); // 콘솔 초기화

		// 충돌 시 게임 오버
		if (bIsCollision) // 충돌 여부 체크
		{
			printf("\n");
			printf("\n");
			printf("            Game Over\n");
			printf("           Score : %d\n", nScore);
			system("pause"); // 위와 같은 문구 출력 후 정지
			return;
		}
		// 충돌 상태가 아닐 때는 점수 증가
		else
		{
			nScore += 1;
		}
	}
}

int main(void)
{
	CursorSettings();
	GameStart();

	return 0;
}

// 해당 게임은 하나의 메인 루프 기반 구조
// 입력에 따라 점프, 장애물이 좌측으로 이동
// 충돌 판정 후 종료 또는 점수 증가가 반복
// 상태 기반 게임 루프(Finite State Machine 구조)
// 키 입력 → 상태 갱신 → 렌더링 → 출력 → 반복