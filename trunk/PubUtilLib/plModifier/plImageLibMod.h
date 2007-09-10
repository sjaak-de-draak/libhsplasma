#ifndef _PLIMAGELIBMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"

class plImageLibMod : public plSingleModifier {
protected:
    hsTArray<plKey> fImages;

public:
    plImageLibMod();
    virtual ~plImageLibMod();
    
    DECLARE_CREATABLE(plImageLibMod)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif