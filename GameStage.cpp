#include "GameStage.h"

GameStage::GameStage()
    : score(0), stage(1), speed(60){} // speed 속 숫자는 게임 루프에서의 딜레이

// 점수 증가
void GameStage::AddScore(int amount) { 
    score += amount;
    UpdateStage();
}

int GameStage::GetScore() const {
    return score;
}

int GameStage::GetStage() const {
    return stage;
}

int GameStage::GetSpeed() const {
    return speed;
}

// 점수에 따라 stage, speed 값 변경
void GameStage::UpdateStage() {
    if (score >= 1500) {
        stage = 4;
        speed = 45;
    } else if (score >= 1000) {
        stage = 3;
        speed = 50;
    } else if (score >= 500) {
        stage = 2;
        speed = 55;
    } else {
        stage = 1;
        speed = 60;
    }
}
