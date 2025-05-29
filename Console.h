#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
public:
    static void CursorSettings();
    static void SetKeyCursor(int _nX, int _nY);
    static void ClearConsole();
};

#endif