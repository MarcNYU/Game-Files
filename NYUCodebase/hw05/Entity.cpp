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
    if (numFrames == 16) {
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
        DrawSprite(LoadTexture("idel.png"), 0, 1.0, 1.0);
//        if (keys[SDL_SCANCODE_SPACE]) {
//            if(keys[SDL_SCANCODE_RIGHT]) {
//                if (collidedBottom) {
//                    //Rigth Running Animation
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                }
//            } else if(keys[SDL_SCANCODE_LEFT]) {
//                if (collidedBottom) {
//                    //Left Running Animation
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                }
//            } else if(keys[SDL_SCANCODE_UP]) {
//                if (direction_x < 0.0) {
//                    //Left Jump
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                } else
//                    //Right Jump
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//            }
//            else {
//                if (collidedBottom) {
//                    if (direction_x < 0.0) {
//                        //Left Idel
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                    } else
//                        //Right Idel
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                } else {
//                    if (direction_x < 0.0) {
//                        //Left Fall
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                    } else
//                        //Right Fall
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                }
//            }
//            if (!collidedBottom) {
//                if (direction_x < 0.0) {
//                    //Left Fall
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                } else
//                    //Right Fall
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//            }
//
//        } else {
//            if(keys[SDL_SCANCODE_RIGHT]) {
//                if (collidedBottom) {
//                    //Rigth Running Animation
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                }
//            } else if(keys[SDL_SCANCODE_LEFT]) {
//                if (collidedBottom) {
//                    //Left Running Animation
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                }
//            } else if(keys[SDL_SCANCODE_UP]) {
//                if (direction_x < 0.0) {
//                    //Left Jump
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                } else
//                    //Right Jump
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//            } else {
//                if (collidedBottom) {
//                    if (direction_x < 0.0) {
//                        //Left Idel
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                    } else
//                        //Right Idel
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                } else {
//                    if (direction_x < 0.0) {
//                        //Left Fall
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                    } else
//                        //Right Fall
//                        DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                }
//            }
//            if (true) {
//                if (direction_x < 0.0) {
//                    //Left Fall
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//                } else
//                    //Right Fall
//                    DrawSprite(LoadTexture("game_sprites.png"), 0, 1.0, 1.0);
//            }
//        }
//        
//    }
//        
//        
//    
//    else {
//        if (width > height) {
//            DrawSprite(0, 0, 1.0, 1.0);
//        }
//        else if (width < height) {
//            DrawSprite(0, 0, 1.0, 1.0);
//        }
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
    //Bottom Collison
    //Right Collison
    //Left Collison
    //Top Collison
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