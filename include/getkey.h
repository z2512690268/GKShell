#pragma once

#ifdef __linux__
    #define KEY_UP 0x1B5B41
    #define KEY_DOWN 0x1B5B42
    #define KEY_ENTER 13
    #define KEY_BACKSPACE 127
    #define KEY_CTRL_C 3

    int getkey(void);
#endif

#ifdef _WIN32
    #define KEY_UP 0xE048
    #define KEY_DOWN 0xE050
    #define KEY_ENTER 13
    #define KEY_BACKSPACE 8
    #define KEY_CTRL_C 3

    int getkey(void);
#endif