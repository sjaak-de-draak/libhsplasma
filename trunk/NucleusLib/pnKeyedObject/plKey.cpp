#include <stdlib.h>
#include <string.h>
#include "plKey.h"

plKeyData::plKeyData() : fUoid(), fObjPtr(NULL), fFileOff(0), fObjSize(0),
                         fRefCnt(1) { }
plKeyData::~plKeyData() { }

bool plKeyData::operator==(plKeyData& other) const {
    return (fUoid == other.fUoid);
}

plString plKeyData::toString() const {
    return fUoid.toString();
}

void plKeyData::read(hsStream* S) {
    fUoid.read(S);
    fFileOff = S->readInt();
    fObjSize = S->readInt();
}

void plKeyData::write(hsStream* S) {
    fUoid.write(S);
    S->writeInt(fFileOff);
    S->writeInt(fObjSize);
}

void plKeyData::readUoid(hsStream* S) {
    fUoid.read(S);
}

void plKeyData::writeUoid(hsStream* S) {
    fUoid.write(S);
}

void plKeyData::prcWrite(pfPrcHelper* prc) {
    fUoid.prcWrite(prc);
}

plUoid& plKeyData::getUoid() { return fUoid; }
class hsKeyedObject* plKeyData::getObj() { return fObjPtr; }
void plKeyData::setObj(class hsKeyedObject* obj) { fObjPtr = obj; }
short plKeyData::getType() const { return fUoid.getType(); }
const PageID& plKeyData::getPageID() const { return fUoid.getPageID(); }
const plString& plKeyData::getName() const { return fUoid.getName(); }
uint32 plKeyData::getID() const { return fUoid.getID(); }
void plKeyData::setID(uint32 id) { fUoid.setID(id); }
uint32 plKeyData::getFileOff() const { return fFileOff; }
void plKeyData::setFileOff(uint32 off) { fFileOff = off; }
uint32 plKeyData::getObjSize() const { return fObjSize; }
void plKeyData::setObjSize(uint32 size) { fObjSize = size; }

uint32 plKeyData::RefCnt() const { return fRefCnt; }
uint32 plKeyData::Ref() { return ++fRefCnt; }
void plKeyData::UnRef() {
    if (--fRefCnt == 0)
        delete this;
}

// plKey //
plKey::plKey() : fKeyData(NULL) { }

plKey::plKey(const plKey& init) {
    fKeyData = init.fKeyData;
    if (fKeyData) fKeyData->Ref();
}

plKey::plKey(plKeyData* init) {
    fKeyData = init;
    if (fKeyData) fKeyData->Ref();
}

plKey::~plKey() {
    if (fKeyData) fKeyData->UnRef();
}

plKeyData& plKey::operator*() const { return *fKeyData; }
plKeyData* plKey::operator->() const { return fKeyData; }
plKey::operator plKeyData*() const { return fKeyData; }

plKey& plKey::operator=(const plKey& other) {
    if (fKeyData != other.fKeyData) {
        if (other.fKeyData) other.fKeyData->Ref();
        if (fKeyData) fKeyData->UnRef();
        fKeyData = other.fKeyData;
    }
    return *this;
}

plKey& plKey::operator=(plKeyData* other) {
    if (fKeyData != other) {
        if (other) other->Ref();
        if (fKeyData) fKeyData->UnRef();
        fKeyData = other;
    }
    return *this;
}

bool plKey::operator==(const plKey& other) const {
    return fKeyData == other.fKeyData;
}

bool plKey::operator==(const plKeyData* other) const {
    return fKeyData == other;
}

bool plKey::operator!=(const plKey& other) const {
    return fKeyData != other.fKeyData;
}

bool plKey::operator!=(const plKeyData* other) const {
    return fKeyData != other;
}

bool plKey::operator<(const plKey& other) const {
    return fKeyData->getUoid() < other->getUoid();
}

bool plKey::Exists() const { return (fKeyData != NULL); }