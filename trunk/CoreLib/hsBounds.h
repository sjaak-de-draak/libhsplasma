#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "hsStream.h"
#include "hsGeometry3.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

class hsBounds {
protected:
    int fType;

public:
    hsBounds();
    virtual ~hsBounds();
    
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);

    void setType(int type);
};

class hsBounds3 : public hsBounds {
public:
    enum {
        kCenterValid = 0x1,
        kIsSphere = 0x2
    };

protected:
    int fBounds3Flags;
    hsPoint3 fMins, fMaxs, fCenter;

public:
    hsBounds3();
    virtual ~hsBounds3();

    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

class hsBounds3Ext : public hsBounds3 {
public:
    enum {
        kAxisAligned = 0x1,
        kSphereSet = 0x2,
        kDistsSet = 0x4,
        kAxisZeroZero = 0x100000,
        kAxisOneZero = 0x200000,
        kAxisTwoZero = 0x400000
    };

protected:
    unsigned int fExtFlags;
    hsPoint3 fCorner;
    hsVector3 fAxes[3];
    hsFloatPoint2 fDists[3];
    float fRadius;

public:
    hsBounds3Ext();
    hsBounds3Ext(const hsBounds3Ext&);
    hsBounds3Ext(const hsBounds3&);
    virtual ~hsBounds3Ext();

    virtual const char* ClassName();
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

class hsBoundsOriented : public hsBounds {
protected:
    unsigned int fCenterValid;
    hsPoint3 fCenter;
    hsPlane3* fPlanes;
    unsigned int fNumPlanes;

public:
    hsBoundsOriented();
    ~hsBoundsOriented();
    
    virtual const char* ClassName();

    void read(hsStream* S);
    void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
