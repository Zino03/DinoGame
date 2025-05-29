#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "GameStage.h"
#include "Skill.h"

class UIManager
{
public:
    static void StartScreen();
    static void DrawScore(const GameStage& gameStage, const Skill& skill);
    static void ShowGameOver(const GameStage& gameStage);
    static void DrawGauge(int gauge);
    
};

#endif
