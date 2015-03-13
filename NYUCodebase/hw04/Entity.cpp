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


void Entity::Render(float elapsed) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (numFrames == 4) {
        const int runLeft[] = {18, 17, 18, 19, 16};
        const int runRight[] = {3, 2, 3, 4, 1};
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            animationElapsed = 0.0;
            if(currentIndex > numFrames-1) {
                currentIndex = 0;
            }
        }
        if(keys[SDL_SCANCODE_RIGHT]) {
            DrawSprite(LoadTexture("beck.png"), runRight[currentIndex], 28.0, 1.0);
        } else if(keys[SDL_SCANCODE_LEFT]) {
            DrawSprite(LoadTexture("beck.png"), runLeft[currentIndex], 28.0, 1.0);
        } else if(keys[SDL_SCANCODE_UP]) {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
            } else
                DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
        } else {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture("beck.png"), 15, 28.0, 1.0);
            } else
                DrawSprite(LoadTexture("beck.png"), 0, 28.0, 1.0);
        }
    }
    if (numFrames == 8) {
        const int runLeft[] = {1, 2, 3, 4, 5, 6, 7, 8};
        const int runRight[] = {10, 11, 12, 13, 14, 15, 16, 17};
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            animationElapsed = 0.0;
            if(currentIndex > numFrames-1) {
                currentIndex = 0;
            }
        }
        if (acceleration_x > 0.0) {
            DrawSprite(LoadTexture("enemy.png"), runRight[currentIndex + 8], 18.0, 1.0);
        } else if (acceleration_x < 0.0) {
            this->DrawSprite(LoadTexture("enemy.png"), runLeft[currentIndex + 8], 18.0, 1.0);
        } else {
            if (direction_x > 0.0) {
                DrawSprite(LoadTexture("enemy.png"), 0, 18.0, 1.0);
            } else if (direction_x < 0.0) {
                DrawSprite(LoadTexture("beck.png"), 9, 18.0, 1.0);
            }
        }
    }
    else {
        if (width > height) {
            DrawSprite(0, 0, 1.0, 1.0);
        }
        else if (width < height) {
            DrawSprite(0, 0, 1.0, 1.0);
        }
    }
}
void Entity::Update(float elapsed) {
    if (numFrames == 4) {
        if (direction_x > 0.0) {
            acceleration_x = 1.0;
        } else if (direction_x < 0.0) {
            acceleration_x = -1.0;
        }
    }
}
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
//    if ((entity->x-entity->width/2) <= (x) < (entity->x+entity->width/2)) {
//        offset = fabsf(x+width/2 - entity->x-entity->width/2);
//        collidedRight = true;
//        return collidedRight;
//    }
//    if ((entity->x-entity->width/2) < (x-width/2) <= (entity->x-entity->width/2)) {
//        offset = fabsf(x+width/2 - entity->x-entity->width/2);
//        collidedLeft = true;
//        return collidedLeft;
//    }
//    if ((entity->y-entity->height/2) <= (y+height/2) < (entity->y+entity->height/2)) {
//        offset = fabsf(y+height/2 - entity->y-entity->height/2);
//        collidedTop = true;
//        return collidedTop;
//    }
//    if ((entity->y+entity->height/2) < (y-height/2) <= (entity->y-entity->height/2)) {
//        offset = fabsf(y+height/2 - entity->y-entity->height/2);
//        collidedBottom = true;
//        return collidedBottom;
//    }
    if ((y-height/2) < (-.8+.125/2)) {
        offset = fabsf(y+height/2 - entity->y-entity->height/2);
        collidedBottom = true;
        return collidedBottom;
    }
    return false;
}


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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(surface);
    return textureID;
}