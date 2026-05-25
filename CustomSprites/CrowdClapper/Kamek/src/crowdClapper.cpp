#include <common.h>
#include <game.h>
#include <profile.h>
#include <sfx.h>

class daEventClap_c : public dEn_c {
    public:
        int onCreate();
        int onExecute();

        u64 triggeringEvent;

        static dActor_c *build();
};

const SpriteData EventClapSpriteData = {ProfileId::AC_EVENT_CLAP, 8, 0xFFFFFFF0, 0, 0x10, 8, 0x10, 0, 0, 0, 0, 2};
Profile EventClapProfile(&daEventClap_c::build, SpriteId::AC_EVENT_CLAP, &EventClapSpriteData, ProfileId::AC_EVENT_CLAP, ProfileId::AC_EVENT_CLAP, "AC_EVENT_CLAP");

dActor_c* daEventClap_c::build() {
    void* buffer = AllocFromGameHeap1(sizeof(daEventClap_c));
    return new(buffer) daEventClap_c;
}

int daEventClap_c::onCreate() {
	char eventNum = (this->settings >> 24) & 0xFF;
	this->triggeringEvent = (u64)1 << (eventNum - 1);

    triggeredYet = false;

	this->onExecute();
	return true;
}

int daEventClap_c::onExecute() {
	if (dFlagMgr_c::instance->flags & this->triggeringEvent) {
        MapSoundPlayer(SoundRelatedClass, SE_SYS_NICE_S, 1);
        this->Delete(1);
	}
    return true;
}