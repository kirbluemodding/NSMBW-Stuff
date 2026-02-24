# 10/100 Coin
A complete remake/overhaul of surrealism's recreation of the SMM2 10/30/50 coin (what a mouthful). The model is the NSMB2 10/100 coins found in roulette blocks and rainbow levels. This sprite quite easily supports more types than just the 10/100 coin provided by default. If you wish to add more types, up to 14 more options should be supported by default, although you could probably add even more.

## Setup
- `EN_COIN_MULTI` is this sprite's profile name. As mentioned by the Custom Sprites general README, you will need to define this in the MoreSprites header files.
- Add `obj_coin_ten.mdl0` and `obj_coin_hundred.mdl0` into your mod's `obj_coin.arc` file. If you do not already have one, add these files into a copy of the vanilla file.
- Add the code from `sprites.py` and `spritedata.xml` into the files of the same name in your Reggie Patch
    - **Do not replace the files. This sprite only has the code for itself, and you will end up breaking your Reggie Patch (yikes).**
- Add the sprite images into your Reggie Patch's `/sprites` folder
- Add `multiCoin.cpp` into your Kamek patch's `/src` folder
- Add `multiCoin.yaml` into your Kamek patch's root folder, and make sure you reference it in the project YAML.
- In `kamek_pal.x` (do not use the other region files), add the following symbols:
```cpp
	/* 10 coin */
	incCoin = 0x80060250;
	addScore = 0x80060690;
	displayScoreAddPopup = 0x800B3540;
```