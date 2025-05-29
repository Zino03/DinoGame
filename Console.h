#ifndef CONSOLE_H
#define CONSOLE_H

// 콘솔 출력 및 커서 제어
class Console
{
public:
    static void CursorSettings(); // 커서 숨기기
    static void SetKeyCursor(int _nX, int _nY); // 커서를 특정 좌표로 이동
    // 특정 좌표에 Draw 하기 위함
};

#endif