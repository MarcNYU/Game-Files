//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 4/28/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include "Entity.h"
#include <iostream>

// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
float timeLeftOver = 0.0f;

void Entity::Render() {
    if (type == "Player") {
        std::cout << sprite.x << " : " << sprite.y << std::endl;
//        sprite.width = 0.125;
//        sprite.height = 0.125;
//        sprite.u = 0.0;
//        sprite.v = 0.0;
//        sprite.Draw(scale);
        // HACK NOTE
         DrawSprite(LoadTexture("8-bit.png"), 0, 1.0, 1.0);
    }
    if (type == "Crate") {
        DrawSprite(LoadTexture("crate.png"), 0, 1.0, 1.0);
    }
    if (type == "Goal") {
        DrawSprite(LoadTexture("waffle.png"), 0, 1.0, 1.0);
    }
}
void Entity::Update(float elapsed) {
    float fixedElapsed = elapsed + timeLeftOver;
    if(fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
        fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
    }
    while (fixedElapsed >= FIXED_TIMESTEP ) {
        fixedElapsed -= FIXED_TIMESTEP;
        FixedUpdate();
    }
    
    timeLeftOver = fixedElapsed;
    if (direction_x > 0.0) {
        acceleration_x = 1.0;
    } else if (direction_x < 0.0) {
        acceleration_x = -1.0;
    }
    if (direction_y < 0.0) {
        velocity_y = -1.0;
    } else if (direction_y > 0.0) {
        velocity_y = 1.0;
    }
}
float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

void Entity::FixedUpdate() {
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
    velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
    velocity_x += acceleration_x * FIXED_TIMESTEP;
    velocity_y += acceleration_y * FIXED_TIMESTEP;
    x += velocity_x * FIXED_TIMESTEP;
    y += velocity_y * FIXED_TIMESTEP;
}
bool Entity::collidesWith(Entity *entity) {
    //Bottom Collison
    if (y-height/2 < entity->height) {
        collidedBottom = true;
        return true;
    }
    //Right Collison
    if (x+width/2 > entity->width) {
        collidedRight = true;
        return true;
    }
    //Left Collison
    if (x-width/2 < entity->width) {
        collidedLeft = true;
        return true;
    }
    //Top Collison
    if (y+height/2 > entity->height) {
        collidedTop = true;
        return true;
    }
    return false;
}
bool collision(Entity sprite_1, Entity sprite_2){
    //If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
    if( (sprite_1.x >= sprite_2.x && sprite_1.x <= (sprite_2.x + sprite_2.width)) ||
       ((sprite_1.x + sprite_1.width) >= sprite_2.x && (sprite_1.x + sprite_1.width) <= (sprite_2.x + sprite_2.width)) ){
        //Now we look at the y axis:
        if( (sprite_1.y >= sprite_2.y && sprite_1.y <= (sprite_2.y + sprite_2.height)) ||
           ((sprite_1.y + sprite_1.height) >= sprite_2.y && (sprite_1.y + sprite_1.height) <= (sprite_2.y + sprite_2.height)) ){
            //The sprites appear to overlap.
            return true;
        }
    }
    //The sprites do not overlap:
    return false;
}
// HACK NOTE
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


