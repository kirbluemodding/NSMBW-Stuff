## What's currently here:
### SpriteTex fixes
- Falling Stardust (`env_stardust`) crash fix
    - The model left behind for this in both NewerSMBW and NSMBWer+ has unfinished/placeholder textures, which look hideous in-game, so a model is provided to fix that as well.
### SpriteTex additions
- Seaweed (`obj_sea_wakame`) for Nybble 6
- Palm Tree (`obj_yashi`) for Nybble 6
- Spiny Cheep Cheep (`pukupuku_toge`) for Nybble 6

## Setup
### SpriteTex fixes
1. Find the original patch code in `spritetex.S`/`spritetex.yaml`
2. Replace the existing patch in your codebase with its fixed version from this repository
3. Compile your game patch
### SpriteTex additions
1. Copy the new patch from this repository's `spritetex.S`, and paste it into your version of the same file in an appropriate location
    * If you need help finding a good place to put it, I'd recommend putting it right below where `# The below was added by Tempus` is written.
2. Repeat the same process for this repository's `spritetex.yaml`, adding the new patch into your version of the same file in an appropriate location
    * Coincidentally, a good place to put it in the YAML file is also right below `# The below was added by Tempus`.
3. Compile your game patch
4. Update your model in the riivolution patch to support SpriteTex
    * Even if you compile this successfully, without editing the model to support it, the game will obviously end up crashing. To fix this, duplicate the original BRRES of whatever you've added SpriteTex support for (i.e. `kanban_yajirushi.brres`) and rename it to `t00.brres`. For a better point of reference, you should look at how NewerSMBW sets their SpriteTex up.