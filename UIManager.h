#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "GameStage.h"
#include "Skill.h"

// 시작화면, 게임 오버 화면, 점수판, 게이지 출력
class UIManager
{
public:
    static void StartScreen(); // 시작 화면
    static void DrawScore(const GameStage& gameStage, const Skill& skill); // 점수판
    static void ShowGameOver(const GameStage& gameStage); // 게임 오버 화면
    static void DrawGauge(const Skill& skill); // 게이지 화면
};

#endif
