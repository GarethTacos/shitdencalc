#!/usr/bin/env bash
clang main.c -lm $(pkg-config --cflags --libs luajit) -Werror -Wall -Wextra -std=c99 -O2 -pipe -fsanitize=address,leak -o debug

