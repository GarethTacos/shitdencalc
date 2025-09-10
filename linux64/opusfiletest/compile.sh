#!/usr/bin/env bash
clang main.c -ljemalloc -lopenal -lm $(pkg-config --cflags --libs opusfile) -Werror -Wall -Wextra -std=c99 -O2 -pipe -fsanitize=address,leak -o debug
