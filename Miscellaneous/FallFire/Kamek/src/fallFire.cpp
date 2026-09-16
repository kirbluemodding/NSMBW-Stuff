#include <game.h>
#include <sfx.h>

// actor class
// not entirely sure why it's called FallFire but whatever

class daFallFire_c : public dActorState_c {
    public:
        // model stuff
        mHeapAllocator_c allocator;
        nw4r::g3d::ResFile resFile;
        m3d::mdl_c model;
        u32 _430;
        m3d::anmTexSrt_c anmTexSrt;

        // random-but-also-important stuff
        u8 pad1[0x18];
        int type; // type/color/whatever
        mEf::es2 levelEffect; // these are our effects
        u8 pad2[0x4]; // could've just used a u32, but let's be somewhat consistent for once

        // replacement functions
        void newLoadModel();
        void newUpdateEffect();
        bool newHitEffect();

        // called in the Move state
        void calculatePositions_Maybe();

        // virtual overrides

        int onCreate();
        int onDelete();
        int onExecute();
        int onDraw();

        void willBeDeleted();

        ~daFallFire_c();

        virtual void initializeState_Move();
        virtual void initializeState_Hit();

        // may not be needed, but i might as well keep it for documentation's sake
        USING_STATES(daFallFire_c);
        REF_NINTENDO_STATE(Wait);
        REF_NINTENDO_STATE(Move);
        REF_NINTENDO_STATE(Hit);
};


// let's do our model first


const char *modelNames[] = {
    "larry_attack",
    "roy_attack",
    "iggy_attack",
    "koopa_attack"
};

void daFallFire_c::newLoadModel() {
    allocator.link(-1, GameHeaps[0], 0, 0x20);

    // actual model
    resFile = getResource("boss_ef_attack", "g3d/boss_ef_attack.brres");
    nw4r::g3d::ResMdl bmdl = resFile.GetResMdl(modelNames[type]);
    model.setup(bmdl, &allocator, 0x224, 1, 0);
    SetupTextures_Map(&model, 0);

    nw4r::g3d::ResAnmTexSrt resAnmTexSrt = resFile.GetResAnmTexSrt(modelNames[type]);
    anmTexSrt.setup(bmdl, resAnmTexSrt, &allocator, 0, 1);
    anmTexSrt.bindEntry(&model, resAnmTexSrt, 0, 1);
    anmTexSrt.setEntryByte34(0, 0);
    model.bindAnim(&anmTexSrt, 1.0f);

    allocator.unlink();
}


// now the constant effect for when it's moving around


const char *effectNames[] = {
    "Wm_la_magicattack",
    "Wm_ro_magicattack",
    "Wm_ig_magicattack",
    "Wm_jr_fireattack"
};

void daFallFire_c::newUpdateEffect() {
    levelEffect.spawn(effectNames[type], 0, &pos, NULL, &scale);
}


// ...ok getting there let's also do the hit effect name


const char *effectHitNames[] = {
    "Wm_mr_larryattackhit",
    "Wm_mr_royattackhit",
    "Wm_mr_iggyattackhit",
    "Wm_jr_firehit"
};

bool daFallFire_c::newHitEffect() {
    return SpawnEffect(effectHitNames[type], 0, &pos, NULL, NULL);
}


// finally let's change the sounds since bowser jr.'s flames sound different than the magic


void daFallFire_c::initializeState_Move() {
    calculatePositions_Maybe();
    
    if (type == 3) {
        PlaySoundAsync(this, SE_BOSS_JR_FIRE_SHOT);
    }
    else {
        PlaySoundAsync(this, SE_BOSS_CMN_MAGIC_SHOT);
    }
}

void daFallFire_c::initializeState_Hit() {
    newHitEffect();

    if (type == 3) {
        PlaySoundAsync(this, SE_BOSS_JR_FIRE_DISAPP);
    }
    else {
        PlaySoundAsync(this, SE_BOSS_CMN_MAGIC_DISAPP);
    }

    Delete(true);
}