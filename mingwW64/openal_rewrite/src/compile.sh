#!/usr/bin/env bash
x86_64-w64-mingw32-gcc main.c misc.c -lm -lgmp -Werror -Wall -Wextra -std=c99 -O2 -pipe -o ../bin/debug

