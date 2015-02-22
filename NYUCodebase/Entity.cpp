//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>

void Entity::Draw(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(width, height, 1.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
}
//void Entity::Draw() {
//    
//    glMatrixMode(GL_MODELVIEW);
//    
//    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
//    glLoadIdentity();
//    glTranslatef(x, y, 0.0);
//    glScalef(width, height, 0.0);
//    glRotatef(rotation, 0.0, 0.0, 0.0);
//    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
//    GLfloat quadColor[] =  {1.0, 1.0, 1.0, 1.0,
//        1.0, 1.0, 1.0, 1.0,
//        1.0, 1.0, 1.0, 1.0,
//        1.0, 1.0, 1.0, 1.0};
//    glVertexPointer(2, GL_FLOAT, 0, quad);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glColorPointer(4, GL_FLOAT, 0, quadColor);
//    glEnableClientState(GL_COLOR_ARRAY);
//    glDrawArrays(GL_QUADS, 0, 4);
//}
