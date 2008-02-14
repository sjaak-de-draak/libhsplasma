#ifndef _PLEXCLUDEREGIONMSG_H
#define _PLEXCLUDEREGIONMSG_H

#include "NucleusLib/pnMessage/plMessage.h"

DllClass plExcludeRegionMsg : public plMessage {
public:
    enum CmdType { kClear, kRelease };

protected:
    unsigned char fCmd;
    unsigned int fSynchFlags;

public:
    plExcludeRegionMsg();
    virtual ~plExcludeRegionMsg();

    DECLARE_CREATABLE(plExcludeRegionMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif