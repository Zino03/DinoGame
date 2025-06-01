#include "Skill.h"
#include "Dino.h"
#include <Windows.h>

Skill::Skill() 
    : gauge(0), isSpeedMode(false), isSlowMode(false), modeTimer(0) {}

void Skill::Update(Dino &dino) {
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
    else if (isSpeedMode) {
        // 스피드 모드일 때는 게이지가 좀 더 빨리 감소
        if (gauge > 0)
            gauge -= speedConsumePerFrame;  // 감속할 양을 상수로 지정
        else {
            // 게이지 다 소모되면 스피드 모드 해제
            gauge = 0;
            isSpeedMode = false;
            modeTimer = 0;
        }
    }

    // 스피드 모드 혹은 슬로우 모드 유지 시간 관리
    if ((isSpeedMode || isSlowMode) && --modeTimer <= 0) {
        system("cls");
        isSpeedMode = false;
        isSlowMode = false;
        dino.SetInvincible(false, 0);
    }
}

void Skill::TryActivateMode(Dino &dino) {
    if (gauge >= maxGauge) { // 게이지가 꽉 찼을 때 누르면 스피드 모드
        // 스피드 모드 발동
        isSpeedMode = true;
        dino.SetInvincible(true, maxGauge);
        modeTimer = maxGauge / 2;
    } else if (gauge > 0) { // 게이지가 다 차지 않으면 슬로우 모드
        // 슬로우 모드 발동
        isSlowMode = true;
        dino.SetInvincible(false, 0);
        modeTimer = gauge; // 현재 게이지에 따라 슬로우 모드 지속 시간 결정
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

// 업데이트 외부에서 게이지를 증가시킬 때 사용
void Skill::AddGauge(int amount) {
    if (gauge + amount <= maxGauge)
        gauge += amount;
    else
        gauge = maxGauge;
}

// 현재 모드에 따른 속도 조정값 반환
int Skill::GetModeSpeedOffset() const {
    if (isSpeedMode) return -25;   // 빠르게
    if (isSlowMode) return +25;    // 느리게
    return 0;                      // 기본
}
