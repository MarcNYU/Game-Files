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
#include <sstream>

// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
float timeLeftOver = 0.0f;
std::vector<std::string> ids;

void entID() {
    //    std::vector<std::string> ids;
    for (int i = 0; i < 41; i++) {
        std::string str = std::to_string(i+1);
        ids.push_back("Ice"+str);
    }
}

void Entity::Render(float elapsed) {
    if (type == "Player") {
        //        std::cout << "P: " << sprite.x << " : " << sprite.y << std::endl;
        // HACK NOTE
        //        DrawSprite(LoadTexture("8-bit.png"), 0, 1.0, 1.0);
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
            if (idx > fixed-1) {
                idx = 0;
            }
        }
        
        if(keys[SDL_SCANCODE_RIGHT]) {
            DrawSprite(LoadTexture("beavor_sprites.png"), runRight[currentIndex], 14.0, 1.0);
        } else if(keys[SDL_SCANCODE_LEFT]) {
            DrawSprite(LoadTexture("beavor_sprites.png"), runLeft[currentIndex], 14.0, 1.0);
        } else if(keys[SDL_SCANCODE_UP]) {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture("beavor_sprites.png"), 6, 14.0, 1.0);
            } else
                DrawSprite(LoadTexture("beavor_sprites.png"), 7, 14.0, 1.0);
        }else if(keys[SDL_SCANCODE_SPACE]) {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture("beavor_sprites.png"), hitGroundLeft[idx], 14.0, 1.0);
            } else
                DrawSprite(LoadTexture("beavor_sprites.png"), hitGroundRight[idx], 14.0, 1.0);
        } else {
            if (direction_x < 0.0) {
                DrawSprite(LoadTexture("beavor_sprites.png"), 0, 14.0, 1.0);
            } else
                DrawSprite(LoadTexture("beavor_sprites.png"), 13, 14.0, 1.0);
            
        }
        //        else {
        //            if (collidedBottom) {
        //                if (direction_x < 0.0) {
        //                    DrawSprite(LoadTexture("beavor_sprites.png"), 15, 28.0, 1.0);
        //                } else
        //                    DrawSprite(LoadTexture("beavor_sprites.png"), 0, 28.0, 1.0);
        //            }
        //            else {
        //                if (direction_x < 0.0) {
        //                    DrawSprite(LoadTexture("beavor_sprites.png"), 24, 28.0, 1.0);
        //                } else
        //                    DrawSprite(LoadTexture("beavor_sprites.png"), 11, 28.0, 1.0);
        //            }
        //        }
        //        if (!collidedBottom) {
        //            if (direction_x < 0.0) {
        //                DrawSprite(LoadTexture("beavor_sprites.png"), 6, 14.0, 1.0);
        //            } else
        //                DrawSprite(LoadTexture("beavor_sprites.png"), 7, 14.0, 1.0);
        //        }
    }
    if (type == "Crate" && x != 0 && y != 0) {
        //        std::cout << "C: " << sprite.x << " : " << sprite.y << std::endl;
        DrawSprite(LoadTexture("crate.png"), 0, 1.0, 1.0);
    }
    if (type == "Goal") {
        //        std::cout << "G: " << sprite.x << " : " << sprite.y << std::endl;
        DrawSprite(LoadTexture("waffle.png"), 0, 1.0, 1.0);
    }
    if (type == "Button"&& x != 0 && y != 0) {
        //        std::cout << "B: " << sprite.x << " : " << sprite.y << std::endl;
        DrawSprite(LoadTexture("button0.png"), 0, 1.0, 1.0);
    }
    //    if (type == "Ice"&& x != 0 && y != 0) {
    //        std::cout << "I: " << sprite.x << " : " << sprite.y << std::endl;
    //        DrawSprite(LoadTexture("ice.png"), 0, 1.0, 1.0);
    //    }
    if ((type == "Wall1"&& x != 0 && y != 0) || (type == "Wall2"&& x != 0 && y != 0)) {
        //        std::cout << "W1: " << sprite.x << " : " << sprite.y << std::endl;
        DrawSprite(LoadTexture("log.png"), 0, 1.0, 1.0);
    }
    if ((type == "Saw1"&& x != 0 && y != 0) || (type == "Saw2"&& x != 0 && y != 0) || (type == "Saw3"&& x != 0 && y != 0) || (type == "Saw3"&& x != 0 && y != 0) ||
        (type == "Saw4"&& x != 0 && y != 0)) {
        //        std::cout << "S: " << sprite.x << " : " << sprite.y << std::endl;
        DrawSprite(LoadTexture("saw.png"), 0, 1.0, 1.0);
    }
    //    for (int i = 0; i < ids.size(); i++) {
    //        if (type == ids[i] && x != 0 && y != 0) {
    //            std::cout << "I: " << sprite.x << " : " << sprite.y << std::endl;
    //            DrawSprite(LoadTexture("ice.png"), 0, 1.0, 1.0);
    //        }
    //    }
    if (type == "HitBox") {
        //        DrawSprite(LoadTexture("blank.png"), 0, 1.0, 1.0);
        //        DrawSprite(0, 0, 1.0, 1.0);
        
    }
    
}
//void Entity::Update(float elapsed) {
//    if (type == "Player") {
//        if (direction_x > 0.0) {
//            acceleration_x = 1.0;
//        } else if (direction_x < 0.0) {
//            acceleration_x = -1.0;
//        }
//    }
//}
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
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (type == "Player") {
        //        velocity_x += gravity_x * elapsed;
        //        velocity_y += gravity_y * elapsed;
        if (!keys[SDL_SCANCODE_SPACE]) {
            //            if (direction_x > 0.0) {
            //                acceleration_x = 1.0;
            //            } else if (direction_x < 0.0) {
            //                acceleration_x = -1.0;
            //            }
            //            if (direction_y > 0.0) {
            //                gravity_y = 1.0;
            //            } else if (direction_y < 0.0)  {
            //                gravity_y = -1.0;
            //            }
        } else if (keys[SDL_SCANCODE_SPACE]) {
            acceleration_x = 0.0;
        }
    }
    //    if (direction_x > 0.0) {
    //        acceleration_x = 1.0;
    //    } else if (direction_x < 0.0) {
    //        acceleration_x = -1.0;
    //    }
    //
    //    if (direction_y > 0.0) {
    //        velocity_x -= gravity_x * elapsed;
    //        velocity_y -= gravity_y * elapsed;
    //        gravity_y = 3.0;
    //    }
    //    else if (direction_y > 0.0) {
    //        velocity_y = 1.0;
    //    }
    //    else if (direction_y == 0.0) {
    //        velocity_y = 0.0;
    //    }
    if (type == "Goal") {
        
    }
    if ((type == "Saw1") || (type == "Saw3")) {
        //0.250001
        //        if (x <= 0.269) {
        //            velocity_x = 0.0;
        //        } else {velocity_x = -1.0;}
        
        if (x <= 0.26) {
            velocity_x = 0.125;
        }
        if (x >= 0.45) {
            velocity_x = -0.125;
        }
        
        //        std::cout << "Stop: " << x << std::endl;
    }
    if ((type == "Saw2")) {
        //0.250001
        //        if (x <= 0.269) {
        //            velocity_x = 0.0;
        //        } else {velocity_x = -1.0;}
        
        if (x <= 0.269) {
            velocity_x = 0.125;
        }
        if (x >= 0.45) {
            velocity_x = -0.125;
        }
        
        //        std::cout << "Stop: " << x << std::endl;
    }
    if ((type == "Saw4")) {
        //0.250001
        //        if (x <= 0.269) {
        //            velocity_x = 0.0;
        //        } else {velocity_x = -1.0;}
        
        if (x <= 0.7) {
            velocity_x = 0.125;
        }
        if (x >= 0.8) {
            velocity_x = -0.125;
        }
        
        //        std::cout << "Stop: " << x << std::endl;
    }
    
}
float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}
float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
    float retVal = dstMin + ((value - srcMin)/(srcMax-srcMin) * (dstMax-dstMin));
    if(retVal < dstMin) {
        retVal = dstMin;
    }
    if(retVal > dstMax) {
        retVal = dstMax;
    }
    return retVal;
}
float easeOut(float from, float to, float time) {
    float oneMinusT = 1.0f-time;
    float tVal = 1.0f - (oneMinusT * oneMinusT * oneMinusT *
                         oneMinusT * oneMinusT);
    return (1.0f-tVal)*from + tVal*to;
}

void Entity::FixedUpdate() {
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
    velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
    velocity_x += acceleration_x * FIXED_TIMESTEP;
    velocity_y += acceleration_y * FIXED_TIMESTEP;
    x += velocity_x * FIXED_TIMESTEP;
    y += velocity_y * FIXED_TIMESTEP;
    
    if ((type == "Saw1") || (type == "Saw2") || (type == "Saw3") || (type == "Saw4")) {
        rotation += FIXED_TIMESTEP;
    }
}
bool Entity::collidesWith(Entity entity) {
    if ((x + width/2) >= (entity.x - entity.width/2) || (x - width/2) <= (entity.x + entity.width/2) || (y + height/2) >= (entity.y - entity.height/2) || (y - height/2) <= (entity.y + entity.height/2))
    {
        //(x1 + radi_x1 >= x2 - radi_x2)
        if ((x + width/2) >= (entity.x - entity.width/2) && ((y >= entity.y-entity.height/2) && (y <= entity.y+entity.height/2)))
        {
            penetration = fabs((sqrtf(powf((x-entity.x), 2) + powf((y-entity.y), 2))) - x+width/2 - entity.x+width/2);
            collidedRight = true;
        }
        if ((x - width/2) <= (entity.x + entity.width/2) && ((y >= entity.y-entity.height/2) && (y <= entity.y+entity.height/2)))
        {
            penetration = fabs((sqrtf(powf((x-entity.x), 2) + powf((y-entity.y), 2))) - x+width/2 - entity.x+width/2);
            collidedLeft = true;
        }
        if ((y + height/2) >= (entity.y - entity.height/2) && (y < entity.y) && ((x >= entity.x-entity.width/2) && (x <= entity.x+entity.width/2)))
        {
            penetration = fabs((sqrtf(powf((x-entity.x), 2) + powf((y-entity.y), 2))) - y+height/2 - entity.y+height/2);
            collidedTop = true;
        }
        if ((y - height/2) <= (entity.y + entity.height/2) && (y > entity.y) && ((x >= entity.x-entity.width/2) && (x <= entity.x+entity.width/2)))
        {
            penetration = fabs((sqrtf(powf((x-entity.x), 2) + powf((y-entity.y), 2))) - y+height/2 - entity.y+height/2);
            collidedBottom = true;
        }
        return true;
    }
    return false;
}


// HACK NOTE
void Entity::DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY) {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    
    glMatrixMode(GL_MODELVIEW);
    
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
void Entity::Jump() {
    if (collidedBottom) {
        if (velocity_y > 0)
            y += 0.05;
        velocity_y = 1.2f;
        acceleration_y = 0.0f;
    }
    else
        acceleration_y = -4.0f;
    if (collidedRight && direction_x>0.0 && velocity_y != 0.0f) {
        velocity_x = -2.0f;
        acceleration_x = 0.0f;
        velocity_y = 1.2f;
        collidedRight = false;
    }
    if (collidedLeft && direction_x<0.0 && velocity_y != 0.0f) {
        velocity_x = 2.0f;
        acceleration_x = 0.0f;
        velocity_y = 1.2f;
        collidedLeft = false;
    }
    collidedBottom = false;
}


