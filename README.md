# shitdencalc
magic sauce calculator with bgm, json update mechanism and upcoming TUI/GUI (possibly in Rust)\
currently testing json update mechanism, will push in 1.1.1 (first patch! yay)

> [!NOTE]  
> changed the structure to linux64 for linux releases and wasm for web releases.\
> windows cross compilation isn't working out for me hehe...\
> also there is now noaudio builds and vanilla builds.\
> however i need to rework the structure to be more modular.

## about the files
- gru.flac is short audio to test the audio.c
- audio.c and audio.h handle background audio via cubeb
- misc.c and misc.h handles title and help
- main.c does the mathing
- iamu_miku.flac is the audio shitden requested himself
- debug is just debug
- compile.sh is the flags i use for clang
