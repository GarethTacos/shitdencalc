#!/usr/bin/env bash
clang main.c misc.c audio.c -lm -lpthread $(pkg-config --cflags --libs opusfile openal) -lgmp -Werror -Wall -Wextra -std=c99 -O2 -s -DNDEBUG -flto -pipe -o ../bin/release


