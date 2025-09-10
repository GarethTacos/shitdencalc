#!/usr/bin/env bash
# same as debug.sh but for valgrind lol (just removed ASan)
clang main.c misc.c audio.c -lm $(pkg-config --cflags --libs opusfile openal) -lgmp -Werror -Wall -Wextra -std=c99 -O2 -pipe -g -o ../bin/valgrind_dbg

