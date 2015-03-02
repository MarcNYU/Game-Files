//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Entity.h"
#include "SpriteSheet.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>

//void Entity::Draw(){
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    
//    glMatrixMode(GL_MODELVIEW);
//    
//    glLoadIdentity();
//    glTranslatef(x, y, 0.0);
//    glScalef(width, height, 1.0);
//    glRotatef(rotation, 0.0, 0.0, 1.0);
//    
//    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
//    glVertexPointer(2, GL_FLOAT, 0, quad);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    
//    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
//    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//    
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    
//    glDrawArrays(GL_QUADS, 0, 4);
//    glDisable(GL_TEXTURE_2D);
//    
//}

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


void Entity::Render() {
    int spriteSheetTexture = LoadTexture("65483.png");
    sprite = SheetSprite(spriteSheetTexture, 425.0f/1024.0f, 468.0f/1024.0f, 93.0f/
                           1024.0f, 84.0f/1024.0f);
    sprite.Draw(1.0);
}
void Entity::Update(float elapsed) {
    
}

void Bullet::Update(float elapsed) {
    y += elapsed;
}
