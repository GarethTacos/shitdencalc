#!/usr/bin/env bash
clang main.c misc.c audio.c -lopenal -lm $(pkg-config --cflags --libs opusfile) -lgmp -Werror -Wall -Wextra -std=c99 -O2 -s -DNDEBUG -flto -pipe -o ../bin/release


