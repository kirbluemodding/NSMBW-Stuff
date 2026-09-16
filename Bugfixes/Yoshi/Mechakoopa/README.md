# Mechakoopa Yoshi Collision Fixes
Allows Yoshi to interact properly with Mechakoopas in levels. Fixes include:
- Preventing Yoshi from getting hurt by a Mechakoopa when colliding with it in any way that isn't a ground pound
- Changing Yoshi's ground pound to act like the player's, rather than instantly defeating the Mechakoopa

## Setup
- Add `mechaKoopa.yaml` to your Kamek patch's root folder (where the other `.yaml` files are)
- Add `/src/mechaKoopa.cpp` to your Kamek patch's `src` folder (where the other `.cpp` files are)
- Add the following addresses into your Kamek patch's `kamek_pal.x` file (the other regions are calculated automatically), if they're not already there:
```
__vt__16daEnMechaKoopa_c = 0x80afb9c8;
__dt__16daEnMechaKoopa_cFv = 0x80a668a0;
onCreate__16daEnMechaKoopa_cFv = 0x80a64cd0;
onDelete__16daEnMechaKoopa_cFv = 0x80a64ec0;
onExecute__16daEnMechaKoopa_cFv = 0x80a64df0;
onDraw__16daEnMechaKoopa_cFv = 0x80a64e90;
kill__16daEnMechaKoopa_cFv = 0x80a64fa0;
_vf74__16daEnMechaKoopa_cFv = 0x80a64fc0;
itemPickedUp__16daEnMechaKoopa_cFv = 0x80a65010;
spriteCollision__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a65090;
playerCollision__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a65200;
collisionCatD_Drill__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a65520;
collisionCat7_GroundPound__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a65530;
collisionCat9_RollingObject__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a656f0;
collisionCat1_Fireball_E_Explosion__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a658b0;
collisionCat2_IceBall_15_YoshiIce__16daEnMechaKoopa_cFP13ActivePhysicsP13ActivePhysics = 0x80a658e0;
dieFall_Begin__16daEnMechaKoopa_cFv = 0x80a667d0;
dieFall_Execute__16daEnMechaKoopa_cFv = 0x80a66830;
dieFall_End__16daEnMechaKoopa_cFv = 0x80a66820;
CreateIceActors__16daEnMechaKoopa_cFv = 0x80a641d0;
_vf230__16daEnMechaKoopa_cFv = 0x80a642f0;
_vf5C__16daEnMechaKoopa_cFv = 0x80a64f90;
initializeState_Carry__16daEnMechaKoopa_cFv = 0x80a65ed0;
executeState_Carry__16daEnMechaKoopa_cFv = 0x80a66060;
finalizeState_Carry__16daEnMechaKoopa_cFv = 0x80a65f80;
```