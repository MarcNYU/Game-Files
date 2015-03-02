//
//  Entity.h
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_Entity_h
#define NYUCodebase_Entity_h

#include "SpriteSheet.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

//class Entity {
//public:
//    Entity (int texture, float xCord, float yCord, float w, float h, float spd) : x(xCord), y(yCord), rotation(0.0), textureID(texture), width(w), height(h), speed(spd), direction_x(0.0), direction_y(0.0){}
//    void Draw();
//    float x;
//    float y;
//    float rotation;
//    int textureID;
//    float width;
//    float height;
//    float speed;
//    float direction_x;
//    float direction_y;
//};

class Entity {
public:
    
    Entity();
    void Update(float elapsed);
    void Render();
    
    bool collidesWith(Entity *entity);
    
    void FixedUpdate();
    
    SheetSprite sprite;
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
