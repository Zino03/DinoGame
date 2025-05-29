#include "Skill.h"

Skill::Skill() 
    : gauge(0), isSpeedMode(false), isSlowMode(false), isInvincible(false), modeTimer(0) {}

void Skill::Update() {
    if (!isSpeedMode && !isSlowMode) {
        // 평소에는 게이지 증가
        if (gauge < maxGauge)
            gauge += gaugeGainPerFrame;
    }
    else if (isSlowMode) {
        // 슬로우 모드일 때는 게이지가 서서히 감소
        if (gauge > 0)
            gauge -= slowConsumePerFrame;  // 감속할 양을 상수로 지정
        else {
            // 게이지 다 소모되면 슬로우 모드 해제
            gauge = 0;
            isSlowMode = false;
            modeTimer = 0;
        }
    }

    // 스피드 모드 혹은 슬로우 모드 유지 시간 관리
    if ((isSpeedMode || isSlowMode) && --modeTimer <= 0) {
        isSpeedMode = false;
        isSlowMode = false;
        isInvincible = false;
    }
}

void Skill::TryActivateMode() {
    if (gauge >= maxGauge) {
        // 스피드 모드 발동
        isSpeedMode = true;
        isInvincible = true;
        modeTimer = speedDuration;
        gauge = 0;
    } else if (gauge > 0) {
        // 슬로우 모드 발동
        isSlowMode = true;
        isInvincible = false;
        modeTimer = gauge;
    }
}
int Skill::GetGauge() const {
    return gauge;
}

bool Skill::InSpeedMode() const {
    return isSpeedMode;
}

bool Skill::InSlowMode() const {
    return isSlowMode;
}

bool Skill::IsInvincible() const {
    return isInvincible;
}

void Skill::ResetModes() {
    isSpeedMode = false;
    isSlowMode = false;
    isInvincible = false;
    gauge = 0;
    modeTimer = 0;
}

void Skill::AddGauge() {
    if (gauge < maxGauge)
        gauge += gaugeGainPerFrame;
}

// ✅ 현재 모드에 따른 속도 조정값 반환
int Skill::GetModeSpeedOffset() const {
    if (isSpeedMode) return -15;   // 빠르게
    if (isSlowMode) return +25;    // 느리게
    return 0;                      // 기본
}
