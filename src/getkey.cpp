#include "getkey.h"

#ifdef __linux__
#include <termio.h>
#include <unistd.h>
#include <cstdio>

int getkey(void)
{
    struct termios tm, old_tm;
    int ch;
    // STDIN_FILENO 为终端文件描述符
    /* 文件描述符在形式上是一个非负整数。实际上，它是一个索引值，
    指向内核为每一个进程所维护的该进程打开文件的记录表。
    当程序打开一个现有文件或者创建一个新文件时，内核向进程返回一个文件描述符
    习惯上，标准输入（standard input）的文件描述符是 0，
    标准输出（standard output）是 1，标准错误（standard error）是 2。
    */
    /*
    POSIX 定义了 STDIN_FILENO、STDOUT_FILENO 和 STDERR_FILENO 来代替 0、1、2。
    这三个符号常量的定义位于头文件 unistd.h。
    */
    if (tcgetattr(STDIN_FILENO, &tm) < 0)
    {
        return -1;
    }

    old_tm = tm; // 保存原始终端设置

    // 设置终端模式为原始模式，该模式下所有输入数据一字节为单位来处理
    cfmakeraw(&tm);

    // 更改终端设置（上面的设置）
    /*
    TCSANOW：不等数据传输完毕就立即改变属性。
    TCSADRAIN：等待所有数据传输结束才改变属性。
    TCSAFLUSH：清空输入输出缓冲区才改变属性。*/
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tm) < 0)
    {
        return -1;
    }

    ch = getchar();
    if(ch == 0x1B){ // 方向键, 输出实际的三个字符
        ch = (ch << 8) + getchar();
        ch = (ch << 8) + getchar();
    }

    // 恢复终端原始设置
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_tm) < 0)
    {
        return -1;
    }

    return ch;
}
#endif // ifdef __linux__

#ifdef _WIN32
#include <conio.h>

int getkey(void)
{
    int ch = _getch();
    if(ch == 0xE0){ // 方向键, 输出实际的两个字符
        ch = (ch << 8) + _getch();
    }
    return ch;
}
#endif // ifdef _WIN32