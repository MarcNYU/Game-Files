//
//  SpriteSheet.h
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_SpriteSheet_h
#define NYUCodebase_SpriteSheet_h

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SheetSprite {
public:
    SheetSprite(unsigned int textureID, float x, float y, float u, float v, float width, float height);
    
    void Draw(float scale);
    
    float scale;
    unsigned int textureID;
    float x;
    float y;
    float u;
    float v;
    float width;
    float height;
};

#endif
