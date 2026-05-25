# Event-activated Crowd Clapper
Plays the audience clapping sound effect whenever a specified event is triggered, and then deletes itself. If you need more than one in a level, you can always add another one bound to another event ID.

## Setup
> [!WARNING]  
> If you are using NewerSMBW or NSMBWer+ as your mod's base, it is highly likely that there are already files named `crowdclapper` present. If your file manager asks you to replace these files, you probably need to.
- `AC_EVENT_CLAP` is this sprite's profile name. As mentioned by the Custom Sprites general README, you will need to define this in the MoreSprites header files.
- Add the code from `spritedata.xml` into the file of the same name in your Reggie Patch
    - **Do not replace the file. This sprite only has the code for itself, and you will end up breaking your Reggie Patch (yikes).**
- Add `crowdClapper.cpp` into your Kamek patch's `/src` folder
- Add `crowdClapper.yaml` into your Kamek patch's root folder, and make sure you reference it in the project YAML.
- (optional) Delete `crowdclapper.S` and the other original unused files if still present from your Kamek patch's `/src` folder for cleanliness, as this file/these files will no longer be used or mentioned in any way.
- You'll probably need to update your `NewerProject.yaml` file (or similar) to include `crowdClapper.yaml` instead of `crowdclapper.yaml`, as the compiler can be quite picky about casing.