#!/usr/bin/env bash
x86_64-w64-mingw32-gcc main.c -static -I/nix/store/j18rq7rz06sa02rrvd1mrk718685b81f-gmp-with-cxx-6.3.0-dev/include -L/nix/store/yryimqrapgfsmqahbjq8zhwi6xivicpd-gmp-with-cxx-x86_64-w64-mingw32-6.3.0/lib -lgmp.dll -o main.exe
