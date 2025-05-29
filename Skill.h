#ifndef SKILL_H
#define SKILL_H

class Skill {
private:
    int gauge;
    bool isSpeedMode;
    bool isSlowMode;
    bool isInvincible;
    int modeTimer;

    static constexpr int maxGauge = 100;
    static constexpr int gaugeGainPerFrame = 1;
    static constexpr int speedDuration = 150;
    static constexpr int slowConsumePerFrame = 1; // 슬로우 모드 시 매 프레임 게이지 소모량

public:
    Skill();

    void Update();
    void TryActivateMode();
    void AddGauge();
    void ResetModes();

    int GetGauge() const;
    int GetModeSpeedOffset() const;

    bool InSpeedMode() const;
    bool InSlowMode() const;
    bool IsInvincible() const;
};
#endif