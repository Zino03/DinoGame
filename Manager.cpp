#include "Manager.h"
#include "Dino.h"
#include "Obstacle.h"
#include "UIManager.h"
#include "Console.h"
#include "GameStage.h"
#include "Skill.h"
#include "Item.h"
#include <conio.h>
#include <Windows.h>
#include <ctime>

#include <fstream>

constexpr int KEY_ESC = 27; // 종료 esc
constexpr int KEY_UP = 105; // 점프 i
constexpr int KEY_DOWN = 106; // 슬라이딩 j
constexpr int KEY_L = 108; // 모드 l

// 키 입력 받기
int GetKeyDown()
{
    if (_kbhit() != 0) return _getch();
    return 0;
}

void Manager::GameStart()
{
    srand(static_cast<unsigned int>(time(nullptr))); // 시드
    while (true)
    {
        UIManager::StartScreen(); // 시작 화면
        int key = GetKeyDown(); // 키 입력 받기
        if (key == KEY_UP){ // 게임 시작
            system("cls"); // 화면 지우기
            // 각 객체들 생성
            GameStage gameStage;
            Dino dino;
            Obstacle obs;
            Skill skill;
            Item item;
            int itemSpawnCooldown = 0;
            bool bIsCollision = false;

            while(true){
                UIManager::DrawScore(gameStage, skill); // 점수판 및 게이지 출력
                
                // 입력 받은 키 값 확인
                int nCurKey = GetKeyDown();
                if (nCurKey == KEY_ESC) return; // 종료
                if (nCurKey == KEY_UP) dino.SetJump(); // 점프
                if (nCurKey == KEY_DOWN) dino.SetSliding(); // 슬라이딩
                
                // 모드 전환 키 입력 처리
                if (nCurKey == KEY_L) 
                    skill.TryActivateMode(dino);
                    
                // 모드 지속 시간 및 게이지 관리
                skill.Update(dino); 

                // 아이템 생성
                if (itemSpawnCooldown-- <= 0 && !item.IsActive()) {
                    item.Spawn();
                    itemSpawnCooldown = 100 + rand() % 100; // 아이템 생성 시간 관리
                }
                item.Update();
                item.DrawItem();

                // 아이템과 충돌 여부 체크
                if (dino.GetBoundingBox().Intersects(item.GetBoundingBox()) && item.IsActive()) {
                    Beep(750, 100); // 750Hz 소리, 100ms
                    switch (item.GetType()) {
                        // 아이템에 따라 다른 효과 함수 호출
                        case SCORE_ITEM: gameStage.AddScore(100); break;
                        case GAUGE_ITEM: skill.AddGauge(20); break;
                        case INVINCIBLE_ITEM: 
                            dino.SetInvincible(true, 100);
                            break;
                    }
                    item.Deactivate(); // 아이템 비활성화
                }
                
                if (obs.IsOutOfScreen()) { // 장애물이 화면을 벗어났을 때 새로운 장애물 생성
                    system("cls");
                    obs = Obstacle(); // 위치 초기화 + 랜덤 타입 설정
                }

                // 공룡, 장애물 위치 계속 업데이트
                obs.Update();
                obs.DrawObstacle();
                dino.Update();
                dino.DrawDino();

                // 무적 상태가 아니면 충돌 판정
                if (!dino.IsInvincible() && dino.GetBoundingBox().Intersects(obs.GetBoundingBox())) {
                    bIsCollision = true;
                }

                // 게임 속도 조절
                Sleep(gameStage.GetSpeed() + skill.GetModeSpeedOffset()); // 모드에 따른 속도 조절
                gameStage.AddScore(1); // 점수 증가

                // 장애물 충돌 시 게임 오버 화면 호출
                if (bIsCollision) {
                    Beep(750, 100); // 750Hz 소리, 100ms
                    UIManager::ShowGameOver(gameStage);
                    break;
                }
            }
        }
        else if(key == KEY_ESC){ // 게임 종료
            return ;
        }
    }
}