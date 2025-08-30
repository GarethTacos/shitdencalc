#!/usr/bin/env bash
clang main.c misc.c audio.c -fsanitize=address,leak,undefined -lm $(pkg-config --cflags --libs opusfile openal) -lgmp -Werror -Wall -Wextra -std=c99 -O1 -pipe -g -o ../bin/debug

