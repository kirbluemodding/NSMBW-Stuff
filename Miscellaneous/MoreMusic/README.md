# More Music
See, I can also name expansions on vanilla game features something that begins with "More"!

This is a (hopefully) much cleaner and less buggy system of adding custom music to your mod than the one included by default in NewerSMBW/NSMBWer+. Some features include:
- Automatic handling for Yoshi drums (previous systems forced all IDs before 200 to not have any, and anything above that value would always have it)
- Compatibility with retail game songs (previous systems would behave weirdly with certain tracks and/or remove dancing points in certain other tracks)
- Separation of fast tracks from their regular counterparts
    - IDs can use completely different songs for their fast variants (previous systems forced the songs to be named similarly, like `SONG` and `SONG_F`)
    - IDs can use the regular song for their fast variants by having the fast variant load the original track (previous systems would either not play any music for the fast variant if one was missing, or required you to duplicate the song for its fast variant)

> [!WARNING]
> This patch may cause issues with MoreSFX. However, some kind of Pysar replacement is almost certain to come about in the near future due to Pysar's release (in fact, I'm pretty sure you don't even need MoreSFX to add non-looping custom sound effects anymore!)

## Setup
### Base
- If your project has/uses `bugfixes.yaml`:
    - Remove `../src/music.cpp` from its inclusion list under `source_files`.
    - Remove the patch titled `MusicHax`, as well as the ones titled `MusicNukeBahps...` if you don't want to remove the dance points from vanilla songs anymore.
- Add `music.yaml` into your project's root folder (where the other `.yaml` files are), and make sure to reference it in your project file (i.e. `NewerProject.yaml`)
- Replace your current project's `music.cpp` file with the new one included here
- Remove `music.h` entirely
    - If MoreSFX or another file complains about it being missing, you can delete the line `#include "music.h"`, as it seemingly does not use it at all
    - If another file complains about it being missing, you'll need to look into it more deeply and figure out how to fix it (some may include the header for no good reason, or others like the Sing-Along minigame from NewerSMBW use it to play sound effects, in which case you'll probably need to change that to use MoreSFX or similar)
- Add the following addresses to your project's `kamek_pal.x` file (don't worry about the other regions, Kamek handles that automatically):
    ```
    instance__11SndSceneMgr = 0x8042a788;
    BrstmNormal = 0x802f69f0;
    BrstmFast = 0x802f6ad8;
    ```
- Compile your code
### Actually adding new songs
This tutorial shows you how to add one song; you'll need to repeat the process for fast variants and new songs.
#### Game
- Add your BRSTM file to the default song folder (usually `/Sound/stream` in NSMBWer+ or `/Music/stream` in NewerSMBW)
- In Pysar, do the following:
    - Open your mod's BRSAR file, `wiimj2d_sound.brsar` (usually in `/Sound` in NSMBWer+ or `/Music` in NewerSMBW), or open one from a dump of the retail game if it doesn't exist yet
    - In the `All Sounds` tab, hit `Add New Sound` in the top right corner:
        - Set the sound type to `STRM`
        - You can name the sound whatever you want, but it's probably best if you name it similarly to what you named your custom song file, i.e. `STRM_BGM_MY_COOL_SONG`
        - Adjust the volume to your liking; most vanilla songs leave it around or at 100, but any value greater than 0 is allowed
        - Set the player to `PLAYER_BGM_COURSE_MAIN [18]`
        - Set the external BRSTM path to your file's location, which should be something like `stream/STRM_BGM_MY_COOL_SONG.brstm`
        - Ensure that the BRSTM source is set to `Existing BRSTM`
        - Hit `Add sound` to add the sound (obviously)
    - Save your file:
        - If you opened one already in your mod's patch, then you're good to simply save your file
        - If you opened one from a dump of your game, you'll need to use `Save As...` and create a new `wiimj2d_sound.brsar` in your mod's patch file where it should've been before
#### Kamek
- (optional but highly recommended) In `sfx.h`, below the last sound effect currently defined in your file, add an identifier for your song name to avoid having to refer to it as a raw SFX ID like `1978`, which can be anything but should ideally be consistent with your other two names for it. Something like this is what you're probably looking for:
    ```cpp
    SE_GAKKI_L_2_ON = 1977,
    // new
    STRM_BGM_MY_COOL_SONG = 1978
    ```
- In `music.cpp`, add your normal and fast variants to the appropriate lists. You'll probably end up with something like this:
    ```cpp
    // custom lists (the stuff you edit)

    const Song NewBrstmNormal [] = {
        // if you didn't add an identifier for your stream, you'll need to use the raw ID visible in Pysar, i.e. 1978
        { STRM_BGM_MY_COOL_SONG, SE_DEMO_OP_DUMMY_U }, // 100
    };

    const Song NewBrstmFast [] = {
        // same rule as the normal list
        { STRM_BGM_MY_COOL_SONG_FAST, SE_DEMO_OP_DUMMY_U }, // 100
    };
    ```
#### Reggie (optional but also highly recommended)
- In your patch's `music.txt` (if you don't have one yet, copy the basic one from `reggiedata` and reference it appropriately in your `main.xml`), reference your new song(s) below the ones already present. You'll probably end up with something like this:
    ``` 
    27:Epilogue
    100:My Cool Song
    ```

If you've reached this point in the tutorial chronologically, and everything works, then you've survived. Congratulations!

## Credits
Ogu-99: Pysar, which makes this possible