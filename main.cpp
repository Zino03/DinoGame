#include "Console.h"
#include "Manager.h"

int main(void)
{	
    Console::CursorSettings(); // 커서 숨기기
    Manager manager;
    manager.GameStart();
    return 0;
}

// 해당 게임은 하나의 메인 루프 기반 구조
// 입력에 따라 점프, 장애물이 좌측으로 이동
// 충돌 판정 후 종료 또는 점수 증가가 반복
// 상태 기반 게임 루프(Finite State Machine 구조)
// 키 입력 → 상태 갱신 → 렌더링 → 출력 → 반복
