//
//  Entity.h
//  NYUCodebase
//
//  Created by Marcus Williams on 4/14/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_Entity_h
#define NYUCodebase_Entity_h

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>


class Entity {
public:
    Entity (float x, float y, float w, float h) : x(x), y(y), width(w), height(h), rotation(0.0), velocity_x (0.0), velocity_y(0.0), acceleration_x(0.0), acceleration_y(0.0), friction_x(0.0), friction_y(0.0), mass(1.0), direction_x(0.0), direction_y(0.0), numFrames(0), framesPerSecond(0.0), gravity_x(0.0), gravity_y(0.0) {}
    
    void Update(float elapsed);
    void Render();
    
    bool collidesWith(Entity *entity);
    
    void FixedUpdate();
    
    float x;
    float y;
    
    float width;
    float height;
    float rotation;
    
    float direction_x;
    float direction_y;
    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float gravity_x;
    float gravity_y;
    float mass;
    bool isStatic;
    
    bool enableCollisions;
    
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    
    int numFrames;
    float animationElapsed = 0.0f;
    float framesPerSecond;
    int currentIndex = 0;
    float offset;
    float penetration;
    
};


GLuint LoadTexture(const char *image_path);
float lerp(float v0, float v1, float t);

#endif
