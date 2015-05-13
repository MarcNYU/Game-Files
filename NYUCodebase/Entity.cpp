//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 5/11/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define FIXED_TIMESTEP 0.0166666f

GLuint LoadTexture2(const char *image_path) {
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

Entity::Entity () : x(0.0), y(0.0), width(0.0), height(0.0), rotation(0.0), velocity_x (0.0), velocity_y(0.0), acceleration_x(0.0), acceleration_y(0.0), friction_x(0.0), friction_y(0.0), mass(1.0), direction_x(0.0), direction_y(0.0), framesPerSecond(0.0), gravity_y(0.0), sprite(0, x, y, 0.0, 0.0, width, height), collidedTop(false), collidedBottom(false), collidedLeft(false), collidedRight(false), isStatic(true), isVisible(false), isCollisionBool(false), enableCollisions(true) {}
void Entity::Update(float elapsed) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (type == "Player") {
        if (!keys[SDL_SCANCODE_RIGHT])
            movingRight = false;
        if (!keys[SDL_SCANCODE_LEFT])
            movingLeft = false;
        
        if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_LEFT])
        {
            if (keys[SDL_SCANCODE_RIGHT]) {
                direction_x = 1.0;
                if (!collidedRight)
                    acceleration_x = 5.0f;
                movingRight = true;
                if (collidedRight && velocity_y < 0) {
                    velocity_y = -0.35f;
                    acceleration_y = 0.0f;
                }
            }
            else
                movingRight = false;
            
            if (keys[SDL_SCANCODE_LEFT]) {
                direction_x = -1.0;
                if (!collidedLeft)
                    acceleration_x = -5.0f;
                movingLeft = true;
                if (collidedLeft && velocity_y < 0) {
                    velocity_y = -0.35f;
                    acceleration_y = 0.0f;
                }
            }
            else
                movingLeft = false;
        }
        else {
            acceleration_x = 0.0f;
            movingRight = false;
            movingLeft = false;
        }
    }
    if ((type == "Saw1") || (type == "Saw2") || (type == "Saw3") || (type == "Saw4")) {
        if (collidedLeft) {
            acceleration_x = 3.0f;
        }
        if (collidedRight) {
            acceleration_x = -3.0f;
        }
    }
}
void Entity::Jump() {
    if (collidedBottom) {
        if (velocity_y > 0)
            y += 0.05;
        velocity_y = 1.2f;
        acceleration_y = 0.0f;
    }
    else
        acceleration_y = -4.0f;
    if (collidedRight && movingRight && velocity_y != 0.0f) {
        velocity_x = -2.0f;
        acceleration_x = 0.0f;
        velocity_y = 1.2f;
        collidedRight = false;
    }
    if (collidedLeft && movingLeft && velocity_y != 0.0f) {
        velocity_x = 2.0f;
        acceleration_x = 0.0f;
        velocity_y = 1.2f;
        collidedLeft = false;
    }
    collidedBottom = false;
}
bool Entity::collidesWith(Entity other) {
    if ((bottomEdge < other.topEdge) && (rightEdge > other.leftEdge) && (leftEdge < other.rightEdge) && (topEdge > other.bottomEdge)) {
        if (y > other.y) {
            if (other.velocity_y < 0) {
                y = other.y + height;
                velocity_y = other.velocity_y;
                acceleration_y = 0.0f;
                collidedBottom = true;
            }
            else if (other.velocity_y > 0) {
                y = other.y + height;
                velocity_y = other.velocity_y;
                acceleration_y = 0.0f;
                collidedBottom = true;
            }
        }
        else {
            collidedBottom = false;
            acceleration_y = -4.0f;
        }
    }
    return false;
}
void Entity::FixedUpdateX() {
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
    velocity_x += FIXED_TIMESTEP * acceleration_x;
    x += FIXED_TIMESTEP * velocity_x;
}

void Entity::FixedUpdateY() {
    if (!collidedBottom) {acceleration_y = -4.0f;}
    velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
    velocity_y += FIXED_TIMESTEP * acceleration_y;
    if (velocity_y < -2.0) {velocity_y = -2.0;}
    y += FIXED_TIMESTEP * velocity_y;
}
void Entity::Render(float elapsed) {
    if (type == "Player") {
        // HACK NOTE
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        const int runRight[] = {8, 9, 7, 9};
        const int runLeft[] = {6, 4, 5, 4};
        const int hitGroundLeft[] = {1, 2, 3, 2, 3, 2, 3, 2};
        const int hitGroundRight[] = {12, 11, 10, 11, 10, 11, 10, 11};
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            idx++;
            animationElapsed = 0.0;
            if(currentIndex > numFrames-1) {
                currentIndex = 0;
            }
            if (idx > fixedFrames-1) {
                idx = 0;
            }
        }
        
        if(keys[SDL_SCANCODE_RIGHT]) {
            if (collidedBottom) {
                DrawSprite(LoadTexture2("beavor_sprites.png"), runRight[currentIndex], 14.0, 1.0);
            }
        } else if(keys[SDL_SCANCODE_LEFT]) {
            if (collidedBottom) {
                DrawSprite(LoadTexture2("beavor_sprites.png"), runLeft[currentIndex], 14.0, 1.0);
            }
        } else if(keys[SDL_SCANCODE_UP]) {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture2("beavor_sprites.png"), 6, 14.0, 1.0);
            } else
                DrawSprite(LoadTexture2("beavor_sprites.png"), 7, 14.0, 1.0);
        }else if(keys[SDL_SCANCODE_SPACE]) {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture2("beavor_sprites.png"), hitGroundLeft[idx], 14.0, 1.0);
            } else
                DrawSprite(LoadTexture2("beavor_sprites.png"), hitGroundRight[idx], 14.0, 1.0);
        } else {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture2("beavor_sprites.png"), 0, 14.0, 1.0);
            } else
                DrawSprite(LoadTexture2("beavor_sprites.png"), 13, 14.0, 1.0);
            
        }
    }
    if (type == "Crate" && x != 0 && y != 0) {
        DrawSprite(LoadTexture2("crate.png"), 0, 1.0, 1.0);
    }
    if (type == "Goal") {
        DrawSprite(LoadTexture2("waffle.png"), 0, 1.0, 1.0);
    }
    if (type == "Button"&& x != 0 && y != 0) {
        if (collidedTop) {
            DrawSprite(LoadTexture2("button.png"), 1, 2.0, 1.0);
        }
        DrawSprite(LoadTexture2("button.png"), 0, 1.0, 1.0);
    }
    if ((type == "Wall1"&& x != 0 && y != 0) || (type == "Wall2"&& x != 0 && y != 0)) {
        DrawSprite(LoadTexture2("log.png"), 0, 1.0, 1.0);
    }
    if ((type == "Saw1"&& x != 0 && y != 0) || (type == "Saw2"&& x != 0 && y != 0) || (type == "Saw3"&& x != 0 && y != 0) || (type == "Saw3"&& x != 0 && y != 0) ||
        (type == "Saw4"&& x != 0 && y != 0)) {
        DrawSprite(LoadTexture2("saw.png"), 0, 1.0, 1.0);
    }
}

void Entity::DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY) {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    //HACK NOTE
    //HARDCODED X and Y OFFSET
    if ((type == "Saw1") || (type == "Saw2") || (type == "Saw3") || (type == "Saw4")) {
        glTranslatef(x-0.475, y+0.535, 0.0);
    } else {
        glTranslatef(x-0.475, y+0.525, 0.0);
        
    }
    glScalef(width, height, 1.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    //    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    GLfloat quad[] = { width * 0.5f, height * 0.5f, width * 0.5f, height * -0.5f, width * -0.5f, height * -0.5f, width * -0.5f, height * 0.5f };
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
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
}
float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}