#ifndef GAMESTAGE_H
#define GAMESTAGE_H

class GameStage{
private:
    int score;
    int stage;
    int speed;

public:
    GameStage();

    void AddScore(int amount = 1);
    int GetScore() const;
    int GetStage() const;
    int GetSpeed() const;

    void UpdateStage();
};
#endif