#ifndef SKILL_H
#define SKILL_H
#include "Dino.h"

// 스킬 시스템 관리, 게이지 기반으로 모드 선택
class Skill {
private:
    int gauge; // 게이지
    bool isSpeedMode; // 스피드 모드 여부
    bool isSlowMode; // 슬로우 모드 여부
    int modeTimer; // 모드 지속 시간 관리

    static constexpr int maxGauge = 100; // 게이지 최대치
    static constexpr double gaugeGainPerFrame = 1; // 프레임 당 게이지 증가량
    static constexpr int speedConsumePerFrame = 2; // 스피드 모드 지속 시간
    static constexpr int slowConsumePerFrame = 1; // 슬로우 모드 시 매 프레임 게이지 소모량

public:
    Skill();

    void Update(Dino &dino); // 상태 업데이트
    void TryActivateMode(Dino &dino); // 모드 발동
    void AddGauge(int amount); // 외부에서 게이지 증가s

    int GetGauge() const; // 현재 게이지 리턴
    int GetModeSpeedOffset() const; // 모드에 따른 속도 변화

    // 상태 반환
    bool InSpeedMode() const; 
    bool InSlowMode() const;
};
#endif