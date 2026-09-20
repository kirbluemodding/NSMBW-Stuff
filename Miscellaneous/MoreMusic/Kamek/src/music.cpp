#include <game.h>
#include <sfx.h>

struct Song {
	u32 trackID;
	u32 controlTrackID; // seemingly always dummied out, i'll keep it here just in case
};


// custom lists (edit these)


const Song NewBrstmNormal [] = {
	{ /* put your song name defined in sfx.h, or your song ID here! */, SE_DEMO_OP_DUMMY_U }, // 100
};

const Song NewBrstmFast [] = {
	{ /* put your song name defined in sfx.h, or your song ID here! */, SE_DEMO_OP_DUMMY_U }, // 100
};


// hack to load the new songs (probably don't mess with this unless you know what you're doing)


class SndSceneMgr { 
	public:
		// we only need the fast check here
		u8 pad1[0x38];
		bool isFast;
		u8 pad2[0x1F];

		static SndSceneMgr *instance; // 0x8042A788
};

extern "C" {
	extern Song BrstmNormal[];
	extern Song BrstmFast[];
}

u32 getGameBgmID(void *self, u32 id) {
	// non-custom songs (0-28)
	if (id < 28) {
		if (SndSceneMgr::instance->isFast) {
			return BrstmFast[id].trackID;
		}
		return BrstmNormal[id].trackID;
	}
	// new stuff (100 and above)
	if (id >= 100) {
		int newId = id - 100;
		if (SndSceneMgr::instance->isFast) {
			return NewBrstmFast[newId].trackID;
		}
		return NewBrstmNormal[newId].trackID;
	}
	return SE_DEMO_OP_DUMMY_U;
}

u32 getGameControlBgmID(void *self, u32 id) {
	// non-custom songs (0-28)
	if (id < 28) {
		if (SndSceneMgr::instance->isFast) {
			return BrstmFast[id].controlTrackID;
		}
		return BrstmNormal[id].controlTrackID;
	}
	// new stuff (100 and above)
	if (id >= 100) {
		int newId = id - 100;
		if (SndSceneMgr::instance->isFast) {
			return NewBrstmFast[newId].controlTrackID;
		}
		return NewBrstmNormal[newId].controlTrackID;
	}
	return SE_DEMO_OP_DUMMY_U;
}