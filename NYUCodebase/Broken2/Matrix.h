//
//  Matrix.h
//  NYUCodebase
//
//  Created by Marcus Williams on 5/10/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Matrix__
#define __NYUCodebase__Matrix__

#include <stdio.h>

class Vector {
public:
    Vector();
    Vector(float x, float y, float z);
    float length();
    void normalize();
    float x;
    float y;
    float z;
};

class Matrix {
public:
    Matrix();
    union {
        float m[4][4];
        float ml[16];
    };
    void identity();
    Matrix inverse();
    Matrix operator * (const Matrix &m2);
    Vector operator * (const Vector &v);
};

#endif /* defined(__NYUCodebase__Matrix__) */
