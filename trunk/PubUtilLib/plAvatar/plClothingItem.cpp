#include "plClothingItem.h"
#include "../plResMgr/plResManager.h"

plClothingItem::plClothingItem() : Group(0), Type(0), Tileset(0), SortOrder(0) {
    DefaultTint1[0] = DefaultTint2[0] = 255;
    DefaultTint1[1] = DefaultTint2[1] = 255;
    DefaultTint1[2] = DefaultTint2[2] = 255;
}

plClothingItem::~plClothingItem() { }

IMPLEMENT_CREATABLE(plClothingItem, kClothingItem, hsKeyedObject)

void plClothingItem::read(hsStream* S) {
    hsKeyedObject::read(S);

    ItemName = S->readSafeStr();
    Group = S->readByte();
    Type = S->readByte();
    Tileset = S->readByte();
    SortOrder = S->readByte();
    Description = S->readSafeStr();
    CustomText = S->readSafeStr();

    if (S->readBool())
        Icon = plResManager::inst->readKey(S);

    int count = S->readInt();
    ElementNames.setSizeNull(count);
    Textures.setSizeNull(count);
	int i, j, count2;
    for (i=0; i<count; i++) {
        ElementNames[i] = S->readSafeStr();
        Textures[i] = new plKey[10];
        for (j=0; j<10; j++)
            Textures[i][j] = NULL;
        count2 = S->readByte();
        for (j=0; j<count2; j++) {
            int idx = S->readByte();
            plKey k = plResManager::inst->readKey(S);
            if (idx > 0 && idx < 10)
                Textures[i][idx] = k;
        }
    }

    for (i=0; i<3; i++) {
        if (S->readBool())
            Meshes[i] = plResManager::inst->readKey(S);
    }

    Accessory = plResManager::inst->readKey(S);

    for (i=0; i<3; i++) {
        DefaultTint1[i] = S->readByte();
        DefaultTint2[i] = S->readByte();
    }
}

void plClothingItem::write(hsStream* S) {
    hsKeyedObject::write(S);

    S->writeSafeStr(ItemName);
    S->writeByte(Group);
    S->writeByte(Type);
    S->writeByte(Tileset);
    S->writeByte(SortOrder);
    S->writeSafeStr(Description);
    S->writeSafeStr(CustomText);

    S->writeBool(Icon != NULL);
    if (Icon != NULL)
        plResManager::inst->writeKey(S, Icon);

    int i, j;
    int count = Textures.getSize();
    S->writeInt(count);
    for (i=0; i<count; i++) {
        S->writeSafeStr(ElementNames[i]);
        int count2 = 0;
        for (j=0; j<10; j++)
            if (Textures[i][j] != NULL) count2++;
        S->writeByte(count2);
        for (j=0; j<10; j++) {
            if (Textures[i][j] != NULL) {
                S->writeByte(j);
                plResManager::inst->writeKey(S, Textures[i][j]);
            }
        }
    }

    for (i=0; i<3; i++) {
        S->writeBool(Meshes[i] != NULL);
        if (Meshes[i] != NULL)
            plResManager::inst->writeKey(S, Meshes[i]);
    }

    plResManager::inst->writeKey(S, Accessory);

    for (i=0; i<3; i++) {
        S->writeByte(DefaultTint1[i]);
        S->writeByte(DefaultTint2[i]);
    }
}

void plClothingItem::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("ClothingName");
    prc->writeParam("value", ItemName);
    prc->endTag(true);
    
    prc->startTag("ClosetOptions");
    prc->writeParam("Group", Group);
    prc->writeParam("Type", Type);
    prc->writeParam("Tileset", Tileset);
    prc->writeParam("SortOrder", SortOrder);
    prc->endTag(true);

    prc->writeTagNoBreak("Description");
    prc->getStream()->writeStr(Description);
    prc->closeTagNoBreak();

    prc->startTag("CustomText");
    prc->writeParam("value", CustomText);
    prc->endTag(true);
}