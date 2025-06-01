#include "UIManager.h"
#include "Console.h"
#include "GameStage.h"
#include "Skill.h"
#include <iostream>

// 시작 화면
void UIManager::StartScreen()
{
    Console::SetKeyCursor(0, 0);
    std::cout <<
        "======================================\n"
        "           Dino Game 2.0               \n"
        "======================================\n"
        "            __                      \n"
        "           / _)                     \n"
        "    .-^^^-/ /                       \n"
        " __/       /                        \n"
        "<__.|_|-|_|                         \n\n"
        "  Press 'i' to Start Game           \n"
        "  Press 'ESC' to Quit                \n\n"
        " Controls:                         \n"
        "  'i' - Jump                      \n"
        "  'j' - Slide                     \n"
        "  'l' - Slow/Speed Mode           \n"
        " Item:                            \n"
        "  '$' - Score + 100               \n"
        "  '+' - Gauge + 20%               \n"
        "  '*' - invincible                \n"
        "======================================\n";
}


// 점수판
void UIManager::DrawScore(const GameStage& gameStage, const Skill& skill)
{
    Console::SetKeyCursor(0, 0);
    // 현재 점수, 스테이지 출력
    std::cout << "Score : " << gameStage.GetScore() << "\tStage : " << gameStage.GetStage() << "\n";
    DrawGauge(skill); // 게이지 출력
}

// 게이지 생성
void UIManager::DrawGauge(const Skill& skill) {
    const int barWidth = 20; // 게이지 크기
    int filled = (skill.GetGauge() * barWidth) / 100;
    
    std::cout << "Gauge : [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filled)
            std::cout << "#";
        else
            std::cout << " ";
    }
    std::cout << "] " << skill.GetGauge() << "%\t";
    if(skill.InSlowMode()){
        std::cout << ">> SLOW MODE <<" << "\n";
    }
    else if(skill.InSpeedMode()){
         std::cout << ">> SPEED MODE!! <<" << "\n";
    }
}

// 게임 오버 화면
void UIManager::ShowGameOver(const GameStage& gameStage)
{
    system("cls");
    std::cout << "\n\n            Game Over\n";
    std::cout << "           Score : " << gameStage.GetScore() << "\n";
    system("pause");
    system("cls");
}
