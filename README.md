# shitdencalc
magic sauce calculator with bgm, json update mechanism and upcoming TUI/GUI (possibly in Rust)

> [!NOTE]  
> main.c has the audio imports and func commented out for faster compiles in debugging
> if you want audio it's as simple as uncommenting them :D

## about the files
- gru.flac is short audio to test the audio.c
- audio.c and audio.h handle background audio via cubeb
- misc.c and misc.h handles title and help
- main.c does the mathing
- iamu_miku.flac is the audio shitden requested himself
- debug is just debug
- compile.sh is the flags i use for clang
