#include "Dino.h"
#include "Console.h"
#include "Skill.h"
#include <iostream>

constexpr int Y_BASE = 20; // 공룡 초기 y축 위치
constexpr int MAX_JUMP = 6; // 1단 점프 높이
constexpr int MAX_JUMP_TWO = 12; // 2단 점프 높이


Dino::Dino() : nYPos(0), bIsSliding(false), bIsJumpping(false), bIsJumpped(false), bFootToggle(false), jumpCount(0), slideTime(0), prevSliding(false), invincibleTime(0) {}

// 점프 상태로 변경
void Dino::SetJump() { 
    if (jumpCount < 2 && !bIsSliding) { // 점프 최대 2번, 슬라이딩 상태에서 점프 불가
        bIsJumpping = true;
        jumpCount++; // 점프 카운트 올리기
    }
}

// 현재 점프 상태 여부 리턴
bool Dino::IsJumping() const { return bIsJumpping; }

// 슬라이딩 상태로 변경
void Dino::SetSliding(){
    if (!bIsJumpping && nYPos == 0) { // 공중에서 슬라이딩 불가
        bIsSliding = true;
        slideTime = 20; // 슬라이딩 시간
    }
}

// 슬라이딩 여부 확인
bool Dino::IsSliding() const { return bIsSliding; }

// 무적 상태로 변경
void Dino::SetInvincible(bool status, int time){
    bisInvincible = status;
    invincibleTime = time;
}

// 무적 상태 여부 확인
bool Dino::IsInvincible() const { return bisInvincible; }

// 현재 y축 위치 리턴
int Dino::GetYPos() const { return nYPos; }

// 공룡 위치 업데이트
void Dino::Update()
{
    // 점프 중인지 확인
    if (bIsJumpping)
    {
        // 최고 지점이 아니면 y축 값 상승
        if (jumpCount == 1 && nYPos < MAX_JUMP && !bIsJumpped) // 1단 점프
            nYPos++;
        else if (jumpCount == 2 && nYPos < MAX_JUMP_TWO && !bIsJumpped) // 2단 점프
            nYPos++;

        // 최고 지점에 도달 후 점프가 끝나면 false 상태로 변경
        else if (bIsJumpped && nYPos == 0)
        {
            bIsJumpped = false;
            bIsJumpping = false;
            jumpCount = 0;
        }

        // 최고 지점 도달 후 y축 값 감소 (중력)
        else if (bIsJumpped)
            nYPos--;

        // 최고 지점에 도달한 경우
        else if (jumpCount == 1 && nYPos == MAX_JUMP)
            bIsJumpped = true; // 밑으로 내려가기 위한 bool 값
        else if (jumpCount == 2 && nYPos == MAX_JUMP_TWO)
            bIsJumpped = true; // 밑으로 내려가기 위한 bool 값
    }

    // 점프 중이 아닌데 공중에 있는 경우 y가 0이 될 때까지 감소 (중력)
    else if (nYPos > 0) nYPos--;
    else jumpCount = 0;
    
    // 슬라이딩 중인지 확인
    if (bIsSliding){
        slideTime--;
        if (slideTime <= 0){
            bIsSliding = false; // slideTime이 0이 되면 슬리이딩 끝
        }
    }

    // 무적 상태 관리
    if (bisInvincible){
        invincibleTime--;
    }
    if (invincibleTime <= 0){
        SetInvincible(false, 0);
    }
}

// 공룡 그리기
void Dino::DrawDino()
{
    // 이전 위치 지우기 (해당 공백으로 덮어서 지우기)
    if (prevSliding) {
        for (int i = 2; i < 5; i++) {
            Console::SetKeyCursor(0, Y_BASE + i);
            std::cout << "                   ";
        }
    } else {
        for (int i = 0; i < 6; i++) {
            Console::SetKeyCursor(0, Y_BASE - prevYPos + i);
            std::cout << "                   ";
        }
    }

    // 점프 시에만 발생하는 이펙트 효과 추가
    static int jumpEffect = 1;
    // 발 움직임을 위한 Toggle
    static bool bFootToggle = false;

    if (bisInvincible){
        if (bIsSliding){
        // 슬라이딩 상태
        Console::SetKeyCursor(0, Y_BASE + 2);
        std::cout << "                  *" << "\n";
        std::cout << "                   *" << "\n";
        std::cout << "                *" << "\n";
    }
    else{
        // 점프에 따라
        Console::SetKeyCursor(0, Y_BASE - nYPos);
        std::cout << "               *" << "\n";
        std::cout << "                *" << "\n";
        std::cout << "              *" << "\n";
        std::cout << "            *" << "\n";
        std::cout << "            *" << "\n";
        }
    }

    if (bIsSliding){
        // 슬라이딩 상태 그리기
        Console::SetKeyCursor(0, Y_BASE + 2);
        std::cout << "    .^^^________" << "\n";
        std::cout << " _/      _______)" << "\n";
        std::cout << "<_.\\_\\\\_\\" << "\n";
    }
    else{
        // 점프에 따라 공룡 위치 변경
        Console::SetKeyCursor(0, Y_BASE - nYPos);
        std::cout << "           __" << "\n";
        std::cout << "          / _)" << "\n";
        std::cout << "    .^^^-/ /" << "\n";
        std::cout << " _/      /" << "\n";
        if (bFootToggle)
            std::cout << "<_.|_||_|" << "\n";
        else
            std::cout << "<_.\\_\\\\_\\" << "\n";

        if (jumpCount == jumpEffect){
            std::cout << "@*@*@*@*@*@" << "\n";
            jumpEffect++;
        }
        if (jumpCount == 0){
            jumpEffect = 1;
        }
        // 공룡 발 위치 변경
        bFootToggle = !bFootToggle;
    }
    prevYPos = nYPos;
    prevSliding = bIsSliding;
    // 다음 프레임을 위한 상태 저장
}
