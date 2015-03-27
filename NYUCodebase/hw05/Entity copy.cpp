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
#include "Entity copy.h"

// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
float timeLeftOver = 0.0f;

void Entity::Render() {
//    const Uint8 *keys = SDL_GetKeyboardState(NULL);
//    if (keys[SDL_SCANCODE_SPACE]) {
//        if(keys[SDL_SCANCODE_RIGHT]) {
//            if (collidedBottom) {
//                //Rigth Running Animation
//            }
//        } else if(keys[SDL_SCANCODE_LEFT]) {
//            if (collidedBottom) {
//                //Left Running Animation
//            }
//        } else if(keys[SDL_SCANCODE_UP]) {
//            if (direction_x < 0.0) {
//                //Left Jump
//            } else
//                //Right Jump
//        }
//        else {
//            if (collidedBottom) {
//                if (direction_x < 0.0) {
//                    //Left Idel
//                } else
//                    //Right Idel
//            } else {
//                if (direction_x < 0.0) {
//                    //Left Fall
//                } else
//                    //Right Fall
//            }
//        }
//        if (!collidedBottom) {
//            if (direction_x < 0.0) {
//                //Left Fall
//            } else
//                //Right Fall
//        }
//
//    } else {
//        if(keys[SDL_SCANCODE_RIGHT]) {
//            if (collidedBottom) {
//                //Rigth Running Animation
//            }
//        } else if(keys[SDL_SCANCODE_LEFT]) {
//            if (collidedBottom) {
//                //Left Running Animation
//            }
//        } else if(keys[SDL_SCANCODE_UP]) {
//            if (direction_x < 0.0) {
//                //Left Jump
//            } else
//                //Right Jump
//        } else {
//            if (collidedBottom) {
//                if (direction_x < 0.0) {
//                    //Left Idel
//                } else
//                    //Right Idel
//            } else {
//                if (direction_x < 0.0) {
//                    //Left Fall
//                } else
//                    //Right Fall
//            }
//        }
//        if (!collidedBottom) {
//            if (direction_x < 0.0) {
//                //Left Fall
//            } else
//                //Right Fall
//        }
//    }
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
    //Right Collison
    //Left Collison
    //Top Collison
    return false;
}


void Bullet::Update(float elapsed) {
    x += elapsed;
}

