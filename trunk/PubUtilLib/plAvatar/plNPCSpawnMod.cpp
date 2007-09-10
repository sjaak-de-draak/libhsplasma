#include "plNPCSpawnMod.h"
#include "../plResMgr/plResManager.h"

plNPCSpawnMod::plNPCSpawnMod() : fAutoSpawn(false), fNotify(NULL) { }

plNPCSpawnMod::~plNPCSpawnMod() {
    if (fNotify) delete fNotify;
}

IMPLEMENT_CREATABLE(plNPCSpawnMod, kNPCSpawnMod, plSingleModifier)

void plNPCSpawnMod::read(hsStream* S) {
    plSingleModifier::read(S);

    fModelName = S->readSafeStr();
    fAccountName = S->readSafeStr();
    fAutoSpawn = S->readBool();

    if (S->readBool())
        fNotify = plNotifyMsg::Convert(plResManager::inst->ReadCreatable(S));
}

void plNPCSpawnMod::write(hsStream* S) {
    plSingleModifier::write(S);

    S->writeSafeStr(fModelName);
    S->writeSafeStr(fAccountName);
    S->writeBool(fAutoSpawn);

    S->writeBool(fNotify != NULL);
    if (fNotify != NULL)
        plResManager::inst->WriteCreatable(S, fNotify);
}

void plNPCSpawnMod::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("ModelName");
    prc->writeParam("value", fModelName);
    prc->endTag(true);
    prc->startTag("AccountName");
    prc->writeParam("value", fAccountName);
    prc->endTag(true);

    prc->writeComment("Unfinished");
}