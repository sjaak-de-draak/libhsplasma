#ifndef _PFGUIVALUECTRL_H
#define _PFGUIVALUECTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIValueCtrl : public pfGUIControlMod {
protected:
    float fMin, fMax, fStep;

public:
    pfGUIValueCtrl();
    virtual ~pfGUIValueCtrl();

    DECLARE_CREATABLE(pfGUIValueCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getMin() const;
    float getMax() const;
    float getStep() const;

    void setMin(float min);
    void setMax(float max);
    void setStep(float step);
    void setRange(float min, float max);
};

#endif
