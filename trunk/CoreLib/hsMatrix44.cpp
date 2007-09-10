#include <stdio.h>
#include <math.h>
#include "hsMatrix44.h"

/*
hsMatrix44::hsMatrix44() { }
hsMatrix44::hsMatrix44(hsMatrix44& init) {
    memcpy(data, init.data, sizeof(data));
}

hsMatrix44::~hsMatrix44() { }
*/

hsMatrix44 hsMatrix44::IdentityMat() {
    static hsMatrix44 idMat;
    static bool idMatInitialized = false;
    if (!idMatInitialized) {
        idMat.Reset();
        idMatInitialized = true;
    }
    return idMat;
}

hsMatrix44 hsMatrix44::TranslateMat(hsVector3& translate) {
    hsMatrix44 tMat = IdentityMat();
    tMat.setTranslate(translate);
    return tMat;
}

hsMatrix44 hsMatrix44::RotateMat(int axis, float angle) {
    hsMatrix44 rMat = IdentityMat();
    rMat.setRotate(axis, angle);
    return rMat;
}

hsMatrix44 hsMatrix44::ScaleMat(hsVector3& scale) {
    hsMatrix44 sMat = IdentityMat();
    sMat.setScale(scale);
    return sMat;
}

void hsMatrix44::Reset() {
    memset(data, 0, sizeof(data));
    data[0][0] = 1.0f;
    data[1][1] = 1.0f;
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

bool hsMatrix44::IsIdentity() {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if ((x == y && data[y][x] != 1.0) ||
                (x != y && data[y][x] != 0.0))
                return false;
    return true;
}

float& hsMatrix44::operator()(int y, int x) {
    return data[y][x];
}

/*
hsMatrix44& hsMatrix44::operator=(const hsMatrix44& other) {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            data[y][x] = other.data[y][x];
    return (*this);
}*/

bool hsMatrix44::operator==(const hsMatrix44& other) {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if (data[y][x] != other.data[y][x])
                return false;
    return true;
}

hsMatrix44 hsMatrix44::operator*(const hsMatrix44& right) {
    hsMatrix44 result;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            result.data[y][x] = (data[y][0] * right.data[0][x]) +
                                (data[y][1] * right.data[1][x]) +
                                (data[y][2] * right.data[2][x]) +
                                (data[y][3] * right.data[3][x]);
    return result;
}

hsPoint3 hsMatrix44::operator*(const hsPoint3& pt) {
    hsPoint3 result;
    result.X = (data[0][0] * pt.X) + (data[0][1] * pt.Y) +
               (data[0][2] * pt.Z) + data[0][3];
    result.Y = (data[1][0] * pt.X) + (data[1][1] * pt.Y) +
               (data[1][2] * pt.Z) + data[1][3];
    result.Z = (data[2][0] * pt.X) + (data[2][1] * pt.Y) +
               (data[2][2] * pt.Z) + data[2][3];
    return result;
}

hsVector3 hsMatrix44::operator*(const hsVector3& vec) {
    hsVector3 result;
    result.X = (data[0][0] * vec.X) + (data[0][1] * vec.Y) +
               (data[0][2] * vec.Z) + data[0][3];
    result.Y = (data[1][0] * vec.X) + (data[1][1] * vec.Y) +
               (data[1][2] * vec.Z) + data[1][3];
    result.Z = (data[2][0] * vec.X) + (data[2][1] * vec.Y) +
               (data[2][2] * vec.Z) + data[2][3];
    return result;
}

hsMatrix44& hsMatrix44::translate(hsVector3& translate) {
    data[0][3] += translate.X;
    data[1][3] += translate.Y;
    data[2][3] += translate.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::rotate(int axis, float angle) {
    hsMatrix44 rMat = RotateMat(axis, angle);
    (*this) = rMat * (*this);
    return (*this);
}

hsMatrix44& hsMatrix44::scale(hsVector3& scale) {
    data[0][0] *= scale.X;
    data[0][1] *= scale.X;
    data[0][2] *= scale.X;
    data[0][3] *= scale.X;
    data[1][0] *= scale.Y;
    data[1][1] *= scale.Y;
    data[1][2] *= scale.Y;
    data[1][3] *= scale.Y;
    data[2][0] *= scale.Z;
    data[2][1] *= scale.Z;
    data[2][2] *= scale.Z;
    data[2][3] *= scale.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::setTranslate(hsVector3& translate) {
    data[0][3] = translate.X;
    data[1][3] = translate.Y;
    data[2][3] = translate.Z;
    return (*this);
}

hsMatrix44& hsMatrix44::setRotate(int axis, float angle) {
    // Note: This is only for rotation around the global axes.
    //   You should get Local-To-World coordinates first before using this
    //   function if you want a local axis rotation.
    int c1, c2;
    switch(axis) {
    case kRight:
        c1 = 1;
        c2 = 2;
        break;
    case kUp:
        c1 = 0;
        c2 = 2;
        break;
    case kView:
        c1 = 0;
        c2 = 1;
        break;
    default:
        // Give something invalid so it'll break:
        c1 = -1;
        c2 = -1;
    }
    data[c1][c1] = cos(angle);
    data[c2][c2] = cos(angle);
    data[c1][c2] = sin(angle);
    data[c2][c1] = -sin(angle);
    return (*this);
}

hsMatrix44& hsMatrix44::setScale(hsVector3& scale) {
    data[0][0] = scale.X;
    data[1][1] = scale.Y;
    data[2][2] = scale.Z;
    return (*this);
}

void hsMatrix44::read(hsStream* S) {
    bool hasData = true;
    if (S->getVer() == pvLive)
        hasData = S->readBool();

    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                data[y][x] = S->readFloat();
    } else {
        Reset();
    }
}

void hsMatrix44::write(hsStream* S) {
    bool hasData = true;
    if (S->getVer() == pvLive) {
        hasData = !IsIdentity();
        S->writeBool(hasData);
    }
    
    if (hasData) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                S->writeFloat(data[y][x]);
    }
}

void hsMatrix44::prcWrite(pfPrcHelper* prc) {
    if (IsIdentity()) {
        prc->startTag("hsMatrix44");
        prc->writeParam("identity", true);
        prc->endTag(true);
    } else {
        prc->writeTagNoBreak("hsMatrix44");
        char buf[1024];
        sprintf(buf, "[%f,%f,%f,%f ; %f,%f,%f,%f ; %f,%f,%f,%f ; %f,%f,%f,%f]",
            data[0][0], data[0][1], data[0][2], data[0][3],
            data[1][0], data[1][1], data[1][2], data[1][3],
            data[2][0], data[2][1], data[2][2], data[2][3],
            data[3][0], data[3][1], data[3][2], data[3][3]);
        prc->getStream()->writeStr(buf);
        prc->closeTagNoBreak();
    }
}

const char* hsMatrix44::toString() {
    static char s[1024];
    sprintf(s, "[ %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f ]",
        data[0][0], data[0][1], data[0][2], data[0][3],
        data[1][0], data[1][1], data[1][2], data[1][3],
        data[2][0], data[2][1], data[2][2], data[2][3],
        data[3][0], data[3][1], data[3][2], data[3][3]);
    return s;
}