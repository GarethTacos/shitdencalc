#!/usr/bin/env bash
x86_64-w64-mingw32-gcc main.c -I../openalsoft4win/openal-soft-1.24.3-bin/include -L../openalsoft4win/openal-soft-1.24.3-bin/libs/Win64 -lOpenAL32.dll -lm $(pkg-config --cflags --libs opusfile) -Werror -Wall -Wextra -std=c99 -O2 -pipe -o debug
