#!/usr/bin/env bash
clang main.c misc.c audio.c -lcubeb -lm -lgmp -Werror -Wall -Wextra -std=c99 -O2 -pipe -o debug

