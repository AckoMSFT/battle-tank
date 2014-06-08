#ifndef LINUX_SPEC_H_INCLUDED
#define LINUX_SPEC_H_INCLUDED

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void);

void Sleep(int time);
#endif // KBHIT_LINUX_H_INCLUDED
