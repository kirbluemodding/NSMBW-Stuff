#include <game.h>
#include <sfx.h>

struct Song {
	u32 trackID;
	u32 controlTrackID; // handles bahp/dance/whatever points in a song
};


// custom lists (edit these)


const Song NewBrstmNormal [] = {
	{ /* song name defined in sfx.h, or your song ID */, /* control track name/ID for the song */ }, 	// 100
};

const Song NewBrstmFast [] = {
	{ /* fast song name defined in sfx.h, or its ID */, /* fast control track name/ID for it */ }, 		// 100
};


// hack to load the new songs (probably don't mess with this unless you know what you're doing)


class SndSceneMgr { 
	public:
		// we only need the variable for whether or not the song is fast here
		u8 pad1[0x38];
		bool isFast;
		u8 pad2[0x1F];

		static SndSceneMgr *instance; // 0x8042A788
};

extern "C" {
	extern u32 BrstmNormal[];
	extern u32 BrstmFast[];

	extern u32 BgmControlTrackNormal[];
	extern u32 BgmControlTrackFast[];
}

u32 getGameBgmID(void *self, u32 id) {
	// non-custom songs (0-28)
	if (id < 28) {
		if (SndSceneMgr::instance->isFast) {
			return BrstmFast[id * 2];
		}
		return BrstmNormal[id * 2];
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
			return BgmControlTrackFast[id * 2];
		}
		return BgmControlTrackNormal[id * 2];
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