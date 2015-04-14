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
#include <vector>
#include "Entity.h"

// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
float timeLeftOver = 0.0f;

void Entity::Render(float elapsed) {
    //    sprite.u = 0.1;//increment .1
    //    sprite.v = 0.0;//0
    //    sprite.v = 0.23;//1
    //    sprite.v = 0.45;//2
    //    sprite.v = 0.7;//3
    if (name == "player") {
        sprite.width = 0.104;
        sprite.height = 0.22;
        sprite.Draw(scale);
        std::vector<float> idel_r_s = {0.0, 0.1};
        std::vector<float> idel_r = {0.1, 0.1, 0.1, 0.1, 0.3};
        std::vector<float> run_r_s = {0.1, 0.2, 0.1, 0.0};
        std::vector<float> run_r = {0.1, 0.2, 0.1, 0.0};
        std::vector<float> jump_r_s = {0.3, 0.4};
        std::vector<float> jump_r = {0.3, 0.4};
        std::vector<float> idel_l_s = {0.9, 0.8};
        std::vector<float> idel_l = {0.8, 0.8, 0.8, 0.8, 0.6};
        std::vector<float> run_l_s = {0.8, 0.7, 0.8, 0.9};
        std::vector<float> run_l = {0.8, 0.7, 0.8, 0.9};
        std::vector<float> jump_l_s = {0.6, 0.5};
        std::vector<float> jump_l = {0.6, 0.5};
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            animationElapsed = 0.0;
        }
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_SPACE]) {
            if(keys[SDL_SCANCODE_RIGHT]) {
                if (collidedBottom) {
                    //Rigth Running Animation
                    sprite.v = 0.45;
                    for (currentIndex; currentIndex < run_r_s.size(); currentIndex++) {
                        sprite.u = run_r_s[currentIndex];
                    }
                    if(currentIndex > run_r_s.size()) {
                        currentIndex = 0;
                    }
                }
            } else if(keys[SDL_SCANCODE_LEFT]) {
                if (collidedBottom) {
                    //Left Running Animation
                    sprite.v = 0.45;
                    for (currentIndex; currentIndex < run_l_s.size(); currentIndex++) {
                        sprite.u = run_l_s[currentIndex];
                    }
                }
            } else if(keys[SDL_SCANCODE_UP]) {
                if (direction_x < 0.0) {
                    //Left Jump
                    sprite.v = 0.45;
                    for (currentIndex; currentIndex < jump_l_s.size(); currentIndex++) {
                        sprite.u = jump_l_s[currentIndex];
                    }
                } else
                    //Right Jump
                    sprite.v = 0.45;
                for (currentIndex; currentIndex < jump_r_s.size(); currentIndex++) {
                    sprite.u = jump_r_s[currentIndex];
                }
            }
            else {
                if (collidedBottom) {
                    if (direction_x < 0.0) {
                        //Left Idel
                        sprite.v = 0.0;
                        for (currentIndex; currentIndex < idel_l_s.size(); currentIndex++) {
                            sprite.u = idel_l_s[currentIndex];
                        }
                    } else
                        //Right Idel
                        sprite.v = 0.0;
                    for (currentIndex; currentIndex < idel_r_s.size(); currentIndex++) {
                        sprite.u = idel_r_s[currentIndex];
                    }
                } else {
                    if (direction_x < 0.0) {
                        //Left Fall
                        sprite.v = 0.0;
                        sprite.u = 0.7;
                    } else
                        //Right Fall
                        sprite.v = 0.0;
                    sprite.u = 0.2;
                }
            }
            if (!collidedBottom) {
                if (direction_x < 0.0) {
                    //Left Fall
                    sprite.v = 0.0;
                    sprite.u = 0.7;
                } else
                    //Right Fall
                    sprite.v = 0.0;
                sprite.u = 0.2;
            }
            
        } else {
            if(keys[SDL_SCANCODE_RIGHT]) {
                if (collidedBottom) {
                    //Rigth Running Animation
                    sprite.v = 0.45;
                    for (currentIndex; currentIndex < run_r.size(); currentIndex++) {
                        sprite.u = run_r[currentIndex];
                    }
                }
            } else if(keys[SDL_SCANCODE_LEFT]) {
                if (collidedBottom) {
                    //Left Running Animation
                    sprite.v = 0.45;
                    for (currentIndex; currentIndex < run_l.size(); currentIndex++) {
                        sprite.u = run_l[currentIndex];
                    }
                }
            } else if(keys[SDL_SCANCODE_UP]) {
                if (direction_x < 0.0) {
                    //Left Jump
                    sprite.v = 0.45;
                    for (currentIndex; currentIndex < jump_l.size(); currentIndex++) {
                        sprite.u = jump_l[currentIndex];
                    }
                } else
                    //Right Jump
                    sprite.v = 0.45;
                for (currentIndex; currentIndex < jump_r.size(); currentIndex++) {
                    sprite.u = jump_r[currentIndex];
                }
            }
            else {
                if (collidedBottom) {
                    if (direction_x < 0.0) {
                        //Left Idel
                        sprite.v = 0.0;
                        for (currentIndex; currentIndex < idel_l.size(); currentIndex++) {
                            sprite.u = idel_l[currentIndex];
                        }
                    } else
                        //Right Idel
                        sprite.v = 0.0;
                    for (currentIndex; currentIndex < idel_r.size(); currentIndex++) {
                        sprite.u = idel_r[currentIndex];
                    }
                } else {
                    if (direction_x < 0.0) {
                        //Left Fall
                        sprite.v = 0.0;
                        sprite.u = 0.7;
                    } else
                        //Right Fall
                        sprite.v = 0.0;
                    sprite.u = 0.2;
                }
            }
            if (!collidedBottom) {
                if (direction_x < 0.0) {
                    //Left Fall
                    sprite.v = 0.0;
                    sprite.u = 0.7;
                } else
                    //Right Fall
                    sprite.v = 0.0;
                sprite.u = 0.2;
            }
        }
        
    }
    else if (name == "robot") {
        
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


void Bullet::Update(float elapsed) {
    x += elapsed;
}

void animatePlayer (SheetSprite sprite) {
    
}
