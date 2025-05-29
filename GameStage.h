#ifndef GAMESTAGE_H
#define GAMESTAGE_H

// 점수에 따라 스테이지, 속도 조절
class GameStage{
private:
    int score; // 점수
    int stage; // 스테이지
    int speed; // 속도 (값이 작을수록 빠름)

public:
    GameStage();
    void AddScore(int amount = 1); // 점수 카운트
    // 각 필드를 반환하는 getter
    int GetScore() const;
    int GetStage() const;
    int GetSpeed() const;
    void UpdateStage(); // 점수에 따라 스테이지, 속도 조절
};
#endif