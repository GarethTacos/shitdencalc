# shitdencalc
Magic calculator that isn't magic because yes.

> [!NOTE]
> Made it so that you can load any audio (however not safe for big audio yet)\
> Branding changed to NO3Calc because shitden is technically trademarked\
> and my product does not match shitdencalc's functionality\
> Windows release is now public because it stopped exploding.

## about the files
- audio.c and audio.h handle background audio via OpenAL Soft and libopusfile (not cubeb sorry forgor update)
- misc.c and misc.h handles title, ANSI escape codes and help texts
- main.c does the mathing because ues
- hachi2hoshimi.ogg is the new audio requested from shitden!!
- debug is just debug binary (linux64 is ./debug and windows is debug.exe)
- compile.sh is the flags i use for clang (important if you want deterministic output)

## Extra Notes:
- windows releases are slower than linux because it is easier to iterate changes on linux.
- fuck me, threads are back lol (for linux, pthreads hates me currently so windows will use blocking model)
- may consider C++ or maybe not because it is cursed.
- need to also add more functions and maybe even a new AST style input (so faster input, but will resemble gnu's bc which is bad)
- gmp has precision issues rn with floats. gonna have to fix by changing into rational via auto-input detection (another reason to switch to AST model).
- kotlin/JVM clone on the way because I need to learn Kotlin lol to port some good android apps to linux

## And as per standard procedure... (Licensing)
This project is licensed under the GPL-3.0-or-later.  

This program uses:
- GMP, licensed under LGPL-3.0-or-later
- OpenAL Soft, licensed under LGPL-2.0-or-later
- Libopusfile, licensed under BSD-3-Clause
- Tribute to Dr_FLAC for being the sole audio library in the early builds but since this program no longer uses it, license not included

Their license texts are provided in LICENSES/.
