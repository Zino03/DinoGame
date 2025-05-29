#ifndef DINO_H
#define DINO_H
#define PRINTLN(STR) { printf(STR); printf("\n"); }

class Dino
{
private:
    int prevYPos;
    bool prevSliding;
    int nYPos;
    bool bIsSliding;
    bool bIsJumpping;
    bool bIsJumpped;
    bool bFootToggle;
    int jumpCount;
    int slideTime;

public:
    Dino();
    void Update();
    void DrawDino();
    void SetJump();
    void SetSliding();
    int GetYPos() const;
    bool IsJumping() const;
    bool IsSliding() const;
};

#endif
