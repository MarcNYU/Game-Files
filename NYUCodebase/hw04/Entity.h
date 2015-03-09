//
//  Entity.h
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_Entity_h
#define NYUCodebase_Entity_h

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>


class Entity {
public:
    Entity (float x, float y, float w, float h) : x(x), y(y), width(w), height(h), velocity_x (0.0), velocity_y(0.0), acceleration_x(0.0), acceleration_y(0.0), friction_x(0.0), friction_y(0.0), mass(1.0){}
    
    void Update(float elapsed);
    void Render();
    void DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);
    bool collidesWith(Entity *entity);
    
    void FixedUpdate();
    
    float x;
    float y;
    
    float width;
    float height;
    
    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float mass;
    bool isStatic;
    
    bool enableCollisions;
    
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
    
};


class Bullet {
public:
    void Update(float elapsed);
    float x;
    float y;
    bool visible;
    float angle;
};

GLuint LoadTexture(const char *image_path);

#endif
