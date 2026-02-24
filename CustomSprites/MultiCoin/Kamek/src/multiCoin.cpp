#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>

// externs
extern "C" void incCoin(int playerID); // 0x80060250
extern "C" void addScore(int score, int playerID); // 0x80060690
extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);
extern "C" void displayScoreAddPopup(Vec pos, int smallScoreID, int playerID, bool showForever);  // https://note.com/reaz0n23/n/nb504e036da6d#143de39b-221f-4909-94f8-cc11e4dbdfdd

class dMultiCoin_c : public dEn_c {
	public:
		static dActor_c *build();

		int onCreate();
		int onExecute();
		int onDelete();
		int onDraw();

		int type;
		int coinValue;

		mHeapAllocator_c allocator;
		m3d::mdl_c bodyModel;

		void updateModelMatrices();

		void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
		void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

		bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat5_Mario(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat8_FencePunch(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat11_PipeCannon(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther); 
		bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther); 
};

const SpriteData multiCoinSpriteData = {ProfileId::EN_COIN_MULTI, 0, 0, 0, 0, 0x100, 0x100, 0, 0, 0, 0, 2};
Profile multiCoinProfile(&dMultiCoin_c::build, SpriteId::EN_COIN_MULTI, &multiCoinSpriteData, ProfileId::EN_COIN_MULTI, ProfileId::EN_COIN_MULTI, "EN_COIN_MULTI");

dActor_c *dMultiCoin_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(dMultiCoin_c));
	return new(buffer) dMultiCoin_c;
}

void dMultiCoin_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int dMultiCoin_c::onCreate() {
	type = (this->settings >> 28);

    allocator.link(-1, GameHeaps[0], 0, 0x20);

	if (type == 0) {
		nw4r::g3d::ResFile rf(getResource("obj_coin", "g3d/obj_coin.brres"));
    	bodyModel.setup(rf.GetResMdl("obj_coin_ten"), &allocator, 0x224, 1, 0);
    	SetupTextures_MapObj(&bodyModel, 0);
	}
	else if (type == 1) {
		nw4r::g3d::ResFile rf(getResource("obj_coin", "g3d/obj_coin.brres"));
    	bodyModel.setup(rf.GetResMdl("obj_coin_hundred"), &allocator, 0x224, 1, 0);
    	SetupTextures_MapObj(&bodyModel, 0);
	}

    allocator.unlink();

	float distToEdge = (type == 1) ? 24.0f : 16.0f;

	ActivePhysics::Info HitMeBaby;
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;
	HitMeBaby.xDistToEdge = distToEdge;
	HitMeBaby.yDistToEdge = distToEdge;
	HitMeBaby.category1 = 0x5;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0xFFBAFFFE;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	// model scale
	if (type == 0) {
		this->scale.x = 0.0625;
		this->scale.y = 0.0625;
		this->scale.z = 0.0625;
	}
	else if (type == 1) {
		this->scale.x = 0.09375;
		this->scale.y = 0.09375;
		this->scale.z = 0.09375;
	}
	else {
		this->scale.x = 1.0;
		this->scale.y = 1.0;
		this->scale.z = 1.0;
	}

	// monetary rewards
	if (type == 0) { this->coinValue = 10; }
	else if (type == 1) { this->coinValue = 100; }
	else { this->coinValue = 0; }

	this->onExecute();
	return true;
}

int dMultiCoin_c::onExecute() {
	updateModelMatrices();

	this->rot.y += 0x400;

	return true;
}

int dMultiCoin_c::onDelete() { return true; }

int dMultiCoin_c::onDraw() {
    bodyModel.scheduleForDrawing();
	return true;
}

// collisions

void dMultiCoin_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
    this->aPhysics.removeFromList();

    for (int i = 0; i < this->coinValue; i++) {
        incCoin(1);
    }
	if (type == 0) {
		SpawnEffect("Wm_ob_starcoinget", 0, &this->pos, &(S16Vec){0,0,0}, &(Vec){1.0, 1.0, 1.0});
    	PlaySoundAsync(this, SE_OBJ_GOAL_GET_COIN_BONUS);
		displayScoreAddPopup(this->pos, 0, apOther->owner->which_player, false);
    	addScore(100, apOther->owner->which_player);
	}
	else if (type == 1) {
		SpawnEffect("Wm_ob_starcoinget", 0, &this->pos, &(S16Vec){0,0,0}, &(Vec){1.5, 1.5, 1.5});
    	PlaySoundAsync(this, SE_OBJ_GOAL_GET_COIN_BONUS);
		// personally i feel like the 1000 points here mixed with the 1UP message looks a little ugly. if you want it, you can obviously re-enable it though
		/*displayScoreAddPopup(this->pos, 4, apOther->owner->which_player, false);
    	addScore(1000, apOther->owner->which_player);*/
	}
    this->Delete(1);
}

bool dMultiCoin_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	PlaySoundAsync(this, SE_OBJ_FIREBALL_DISAPP);
	return true;
}

bool dMultiCoin_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	PlaySoundAsync(this, SE_OBJ_PNGN_ICEBALL_DISAPP);
    // weird
    Vec2 iceballpos = apOther->positionOfLastCollision;
    Vec iceballpos3 = {iceballpos.x, iceballpos.y, this->pos.z};
    SpawnEffect("Wm_ob_icemisshit", NULL, &iceballpos3, &(S16Vec){0,0,0}, &(Vec){1, 1, 1});
    SpawnEffect("Wm_ob_icemisshit_smk", NULL, &iceballpos3, &(S16Vec){0,0,0}, &(Vec){1, 1, 1});
	return true;
}

void dMultiCoin_c::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) { return this->playerCollision(apThis, apOther); }
bool dMultiCoin_c::collisionCat5_Mario(ActivePhysics *apThis, ActivePhysics *apOther) { this->playerCollision(apThis, apOther); return true; }
bool dMultiCoin_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCat11_PipeCannon(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat5_Mario(apThis, apOther); }
bool dMultiCoin_c::collisionCat8_FencePunch(ActivePhysics *apThis, ActivePhysics *apOther) { return true; }
bool dMultiCoin_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) { return true; }
bool dMultiCoin_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) { return this->collisionCat1_Fireball_E_Explosion(apThis, apOther); }