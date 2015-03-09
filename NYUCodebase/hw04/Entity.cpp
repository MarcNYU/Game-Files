//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//


#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Entity.h"


void Entity::Render() {}
void Entity::Update(float elapsed) {}
void Entity::DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY) {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(width, height, 1.0);
    
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    // our regular sprite drawing
    float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
    float spriteWidth = 1.0/(float)spriteCountX;
    float spriteHeight = 1.0/(float)spriteCountY;
    GLfloat quadUVs[] = { u, v,
        u, v+spriteHeight,
        u+spriteWidth, v+spriteHeight,
        u+spriteWidth, v};
    // our regular sprite drawing
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
}
bool Entity::collidesWith(Entity *entity) {
    if (x+width/2 > entity->x-entity->width/2) {
        collidedRight = true;
        return collidedRight;
    }
    if (x-width/2 < entity->x+entity->width/2) {
        collidedLeft = true;
        return collidedLeft;
    }
    if (y+height/2 > entity->y-entity->height/2) {
        collidedTop = true;
        return collidedTop;
    }
    if (y-height/2 < entity->y+entity->height/2) {
        collidedBottom = true;
        return collidedBottom;
    }
    return false;
}
void FixedUpdate() {}

void Bullet::Update(float elapsed) {
    x += elapsed;
}

GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}