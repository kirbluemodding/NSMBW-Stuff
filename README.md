# Kirblue's NSMBW Stuff
This is collection of random stuff I've made over the years for NSMBW.

If you have trouble/issues setting up one of these things, feel free to open an issue (or a pull request if you want to fix a bug of some kind). However, it should be noted that **you are expected to know how to set up Riivolution patches and/or Kamek before making use of these. If you open an issue regarding setup of these two things, please do not expect any support.**

This is what's currently released:
- [SpriteTex](/SpriteTex) (NewerSMBW, NSMBWer+) - Fixes/additions for NewerSMBW's SpriteTex system, allowing for loading new models for actors that don't replace the original one
    - [Additions](/SpriteTex/Additions)
        - [Palm Tree](/SpriteTex/Additions/Palm%20Tree)
        - [Seaweed](/SpriteTex/Additions/Seaweed)
        - [Spiny Cheep Cheep](/SpriteTex/Additions/Spiny%20Cheep%20Cheep)
    - [Fixes](/SpriteTex/Fixes)
        - [Falling Stardust Crash Fix](/SpriteTex/Fixes/Falling%20Stardust)
- [Custom Sprites](/CustomSprites) (NewerSMBW (read note), NSMBWer+) - Custom actors
    - **NOTE:** NewerSMBW lacks support for [More Sprites](https://github.com/Developers-Collective/NSMBW-Custom-Sprites/releases/tag/MoreSprites) by default. As such, its installation is required before use of these custom sprites in NewerSMBW.
    - [Multi-Coin](/CustomSprites/MultiCoin) - Giant coin that rewards 10 or 100 coins, with a very simple setup for more types for it
    - [Crowd Clapper](/CustomSprites/CrowdClapper) - Event-triggered actor that plays the audience cheering sound, inspired by NewerSMBW's unused `crowdclapper` files
- [Bugfixes](/Bugfixes) (NewerSMBW, NSMBWer+) - Vanilla game fixes
    - [Yoshi Bugfixes](/Bugfixes/Yoshi) - Yoshi collision/miscellaneous fixes
        - [Mechakoopa](/Bugfixes/Yoshi/Mechakoopa)
- [Miscellaneous](/Miscellaneous) (NewerSMBW, NSMBWer+) - Things that do not fit into the other categories
    - [Bowser Jr. Fireball Spawn Area](/FallFire) - Replaces the duplicate fourth magic fireball spawn area type with Bowser Jr.'s flames

## Credits
When other people are involved in something made here, their name will be listed. **If you deserve credit but were not credited (very sorry), please open a pull request and make that change.**
- Newer Team: NewerSMBW SpriteTex
- ReaZ0N23: `displayScoreAddPopup` function documentation used for the Multi-Coin
- surrealism: Original 10 Coin sprite, which inspired the Multi-Coin and served as a rough base for it
- The wonderful people behind the tools that make NSMBW modding, and therefore this repository, possible