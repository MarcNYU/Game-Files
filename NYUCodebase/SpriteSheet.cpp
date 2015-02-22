//
//  SpriteSheet.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/21/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "SpriteSheet.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

void SheetSprite::Draw(float scale) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    GLfloat quad[] = {-width * scale , height * scale, -width * scale, -height * scale,
        width * scale, -height * scale, width * scale, height * scale};
    GLfloat quadUVs[] = {u, v, u, v+height, u+width, v+height, u+width, v};
    // draw arrays
}