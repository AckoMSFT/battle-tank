/**
 *  @file linux_spec.h
 *  @brief - Definicije funkcija kbhit() i Sleep() za linux sistem.
 */
#ifndef LINUX_SPEC_H_INCLUDED
#define LINUX_SPEC_H_INCLUDED

#ifndef _WIN32
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void);

void Sleep(int time);
#endif // _WIN32
#endif // KBHIT_LINUX_H_INCLUDED
