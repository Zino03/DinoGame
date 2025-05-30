#ifndef DINO_H
#define DINO_H

// 캐릭터(공룡)의 상태 관리 및 그리기
class Dino
{
private:
    int prevYPos; // 이전의 y 위치 저장 (화면에서 지우는 용도)
    bool prevSliding; // 이전 슬라이딩 상태
    int nYPos; // 현재 점프 높이 (클수록 점프 높이 커짐)
    bool bIsSliding;  // 슬라이딩 중인지 여부
    bool bIsJumpping; // 점프 중인지 여부
    bool bIsJumpped; // 최고 높이 도달 여부
    bool bFootToggle; // 발 움직임 구현 용도
    int jumpCount; // 점프 횟수 체크 (최대 2번)
    int slideTime; // 슬라이딩 유지 시간
    bool bisInvincible; // 무적 여부
    int invincibleTime; // 무적 시간

public:
    Dino();
    void Update(); // 상태 업데이트
    void DrawDino(); // 공룡 그리기
    void SetJump(); // 점프 상태 True
    void SetSliding(); // 슬라이딩 상태 True
    void SetInvincible(bool status, int time); // 무적 상태 True 
    int GetYPos() const; // 현재 점프 위치
    bool IsJumping() const; // 점프 중 여부 반환
    bool IsSliding() const; // 슬라이딩 중 여부 반환
    bool IsInvincible() const; // 무적 여부 반환
};

#endif
