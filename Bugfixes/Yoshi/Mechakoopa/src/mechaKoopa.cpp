#include <game.h>

class daEnMechaKoopa_c : public dEn_c {
    public:
        u8 pad[0xDC]; // get our size to 0x600

        int onCreate();
        int onDelete();
        int onExecute();
        int onDraw();

        ~daEnMechaKoopa_c();

        void kill();
        int _vf74();
	    void itemPickedUp();
        void _vf5C();

        void spriteCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	    void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther); 

        bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther);
        bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
        bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
        bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
        bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);

        bool CreateIceActors();
	    void _vf230();

        void dieFall_Begin();
	    void dieFall_Execute();
	    void dieFall_End();

        virtual void initializeState_Carry();
        virtual void executeState_Carry();
        virtual void finalizeState_Carry();
};

void MechaKoopaNewYoshiCollision(daEnMechaKoopa_c *self, ActivePhysics *apThis, ActivePhysics *apOther) { return self->playerCollision(apThis, apOther); }
bool MechaKoopaNewYoshiGroundPound(daEnMechaKoopa_c *self, ActivePhysics *apThis, ActivePhysics *apOther) { return self->collisionCat7_GroundPound(apThis, apOther); }