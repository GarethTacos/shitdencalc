#!/usr/bin/env bash
clang examplewillexplode.c -lopenal -lm $(pkg-config --cflags --libs opusfile) -Werror -Wall -Wextra -std=c99 -O2 -pipe -o debug

