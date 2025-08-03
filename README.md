# shitdencalc
magic sauce calculator with bgm, json update mechanism (cancelled TUI because not enough energy)\
currently testing json update mechanism, will push in 1.1.1 (first patch! yay)

> [!NOTE]  
> May consider Libtommath because it can go WASM\
> Or just rewrite in JS with the same principles (but it can be tiring)\
> No more noaudio builds because too lazy to segment my code properly\
> OpenAL Soft instead of Cubeb because Mozilla's documentation is pain\
> And added Licenses if not my shit is technically illegal

## about the files
- gru.flac is short audio to test the audio.c (Blue Archive OST 253)
- audio.c and audio.h handle background audio via OpenAL Soft (not cubeb sorry forgor update)
- misc.c and misc.h handles title and help texts
- main.c does the mathing because ues
- iamu_miku.flac is the audio shitden requested himself (I Nan Desu)
- debug is just debug binary (linux64)
- compile.sh is the flags i use for clang (important if you want deterministic output)

## Extra Notes:
- I didn't make it loop because it would be annoying\ and I would have to play around with threads and cause unsafe behaviours again.
- you can technically replace the iamu_miku.flac or modify the source code to play another flac.\ (I won't stop you because I don't care)
## And as per standard procedure... (Licensing)
This project is licensed under the GPL-3.0-or-later.  

This program uses:
- GMP, licensed under LGPL-3.0-or-later
- OpenAL Soft, licensed under LGPL-2.0-or-later
Their license texts are provided in LICENSES/.
