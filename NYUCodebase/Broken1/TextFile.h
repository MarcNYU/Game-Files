//
//  TextFile.h
//  NYUCodebase
//
//  Created by Marcus Williams on 5/10/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__TextFile__
#define __NYUCodebase__TextFile__

#include <stdio.h>

class Text {
public:
    void Draw(std::string text, float x, float y);
    
    int font;
    float size;
    float spacing;
    float r;
    float g;
    float b;
    float a;
};

#endif /* defined(__NYUCodebase__TextFile__) */
