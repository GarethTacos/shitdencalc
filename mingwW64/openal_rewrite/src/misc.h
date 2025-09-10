/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * misc.h — shitdencalc
 * Copyright (c) 2025 GarethTacos
 */
// title.h renamed to misc.h because has misc stuff
#ifndef MISC_H
#define MISC_H

char* title();
char* help();

// Define the ESC character to make the codes cleaner
#define ESC "\033"

// Define the full ANSI escape sequences as macros

// --- Reset and Basic Attributes ---
#define ANSI_RESET          ESC "[0m"
#define ANSI_BOLD           ESC "[1m"
#define ANSI_UNDERLINE      ESC "[4m"
#define ANSI_REVERSE        ESC "[7m"

// --- Foreground Colors ---
#define ANSI_COLOR_BLACK    ESC "[30m"
#define ANSI_COLOR_RED      ESC "[31m"
#define ANSI_COLOR_GREEN    ESC "[32m"
#define ANSI_COLOR_YELLOW   ESC "[33m"
#define ANSI_COLOR_BLUE     ESC "[34m"
#define ANSI_COLOR_MAGENTA  ESC "[35m"
#define ANSI_COLOR_CYAN     ESC "[36m"
#define ANSI_COLOR_WHITE    ESC "[37m"

// --- Background Colors ---
#define ANSI_BG_BLACK       ESC "[40m"
#define ANSI_BG_RED         ESC "[41m"
#define ANSI_BG_GREEN       ESC "[42m"
#define ANSI_BG_YELLOW      ESC "[43m"
#define ANSI_BG_BLUE        ESC "[44m"
#define ANSI_BG_MAGENTA     ESC "[45m"
#define ANSI_BG_CYAN        ESC "[46m"
#define ANSI_BG_WHITE       ESC "[47m"

// --- Screen and Cursor Control ---
#define ANSI_CLEAR_SCREEN   ESC "[2J"
#define ANSI_CURSOR_HOME    ESC "[H"
#define ANSI_CLEAR_AND_HOME ANSI_CLEAR_SCREEN ANSI_CURSOR_HOME

#endif

