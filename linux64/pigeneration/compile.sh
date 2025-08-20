#!/usr/bin/env bash
clang main.c -lmpfr -lm -lgmp -Werror -Wall -Wextra -std=c99 -O2 -pipe -o debug

