#include "Manager.h"
#include "Dino.h"
#include "Obstacle.h"
#include "UIManager.h"
#include "Console.h"
#include "GameStage.h"
#include "Skill.h"
#include <conio.h>
#include <Windows.h>
#include <ctime>

constexpr int KEY_ESC = 27;
constexpr int KEY_UP = 105; // 점프 i
constexpr int KEY_DOWN = 106; // 슬라이딩 j
constexpr int SLEEP_TIME = 35;
constexpr int KEY_L = 108; // 모드 l
constexpr int BASE_SPEED = SLEEP_TIME;

// 키 입력 받기
int GetKeyDown()
{
    if (_kbhit() != 0) return _getch();
    return 0;
}

void Manager::GameStart()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    while (true)
    {
        UIManager::StartScreen();
        int key = GetKeyDown();
        if (key == KEY_UP){
            Console::ClearConsole();
            GameStage gameStage;
            Dino dino;
            Obstacle obs;
            Skill skill;

            bool bIsCollision = false;
            while(true){
                if (obs.IsOutOfScreen()) {
                    system("cls");
                    obs = Obstacle(); // 위치 초기화 + 랜덤 타입 설정
                }
                UIManager::DrawScore(gameStage, skill);
                // 입력 받은 키 값 확인
                int nCurKey = GetKeyDown();
                if (nCurKey == KEY_ESC) return;
                if (nCurKey == KEY_UP) dino.SetJump(); // 점프
                if (nCurKey == KEY_DOWN) dino.SetSliding(); // 슬라이딩
                
                // ✅ 모드 전환 키 입력 처리
                if (nCurKey == KEY_L) 
                    skill.TryActivateMode();

                obs.Update();
                obs.DrawTree();

                // 공룡, 장애물 위치 계속 업데이트
                dino.Update();
                dino.DrawDino();

                // ✅ 무적 상태가 아니면 충돌 판정
                if (!skill.IsInvincible() && obs.CheckCollision(dino.GetYPos(), dino.IsSliding())) {
                    bIsCollision = true;
                }

                skill.Update();   // ✅ 모드 지속 시간 관리
                if (!skill.InSpeedMode() && !skill.InSlowMode()) {
                    skill.AddGauge();
                }

                Sleep(gameStage.GetSpeed() + skill.GetModeSpeedOffset()); // ✅ 모드에 따른 속도 조절
                gameStage.AddScore(1);

                if (bIsCollision) {
                    UIManager::ShowGameOver(gameStage);
                    break;
                }
            }
        }
        else if(key == KEY_ESC){
            return ;
        }
    }
}