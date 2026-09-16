# Bowser Jr. Flames for the Magic Fireball Spawn Area Actor (aka FallFire / Sprite ID 392)
In retail, (this is a gross simplification but) the magic fireball spawning area sprite uses a list of four different possible colors it can load for the spawned flames:
- 0 loads the light blue flames shot by Larry
- 1 loads the purple flames shot by Roy
- 2 loads the green flames shot by Iggy
- 3 loads the light blue flames shot by Larry, again

Naturally, it would be nice to have the ability to replace the duplicate fourth option with a unique one, so that's exactly what I did. With this patch, making the sprite load the fourth color/variant/type of the magic fireball spawning area actor will make it spawn Bowser Jr.'s flames instead of Larry's. However, you can actually make it load almost anything you want (including the flames of the other Koopalings) if you want to edit the code, which I've tried to keep nice and simple.

> [!WARNING]
> The game does not load every effect file by default, causing certain effects to either not load or crash the game unless a sprite that DOES load it is in the level. You may not even encounter this issue without thinking about it, as most uses of the Magic Fireball Spawn Area are in a level that features the boss from which the fireballs should've came from. However, if you actually DO have this issue, the easiest fix is to force-load the sprite by going into Reggie's Area Options (tileset selection and whatnot) menu, then go to the Loaded Sprites tab and paste the ID of the Koopaling/boss whose effect file is not being loaded properly.

## Setup
### Kamek
- Add `fallFire.yaml` to your Kamek patch's root folder (where the other `.yaml` files are), and reference it in your project file (usually `NewerProject.yaml` or similar)
- Add `/src/fallFire.cpp` to your Kamek patch's `src` folder (where the other `.cpp` files are)
- Add the following address into your Kamek patch's `kamek_pal.x` file (the other regions are calculated automatically), if it's not already there:
```
calculatePositions_Maybe__12daFallFire_cFv = 0x807e7ba0;
```
### Reggie (optional)
- Add the contents of `spritedata.xml` into your Reggie patch's file of the same name