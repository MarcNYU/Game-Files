//
//  SpriteSheet.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 5/11/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "SpriteSheet.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>


void SheetSprite::Draw(float scale) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    std::cout << "x, y = " << x << ", " << y << std::endl;
    glTranslatef(x, y, 0.0);
    
    std::cout << "u, v = " << u << ", " << v << std::endl;
    GLfloat quad[] = {-width * scale , height * scale, -width * scale, -height * scale,
        width * scale, -height * scale, width * scale, height * scale};
    GLfloat quadUVs[] = {u, v, u, v+height, u+width, v+height, u+width, v};
    
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}
SheetSprite::SheetSprite(unsigned int textureID, float x, float y, float u, float v, float width, float height) : textureID(textureID), x(x), y(y), u(u), v(v), width(width), height(height){}