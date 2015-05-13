//
//  Entity.h
//  NYUCodebase
//
//  Created by Marcus Williams on 5/10/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__Entity__
#define __NYUCodebase__Entity__

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "NewSpriteSheet.h"
#include <string>
#include <vector>


class Entity {
public:
    Entity();
    
    void Update(float elapsed);
    void Render(float elapsed);
    
    void DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);
    bool collidesWith(Entity entity);
    
    void FixedUpdateX();
    void FixedUpdateY();
    SheetSprite sprite;
    
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
    
    float gravity_y;
    
    float mass;
    bool isStatic;
    
    bool movingRight;
    bool movingLeft;
    
    std::string index;
    std::string type;
    
    bool enableCollisions;
    bool isVisible;
    
    void Jump();
    
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    bool collidedTop;
    bool isCollisionBool;
    
    float rightEdge = x + width / 2;
    float leftEdge = x - width / 2;
    float topEdge = y + height / 2;
    float bottomEdge = y - height / 2;
    
    GLfloat quad[8];
    GLfloat quadUVs[8];
    
    int numFrames;
    int spriteNum;
    float animationElapsed = 0.0f;
    float framesPerSecond;
    int currentIndex = 0;
    int idx = 0;
    int fixedFrames = 8;
    
};

//GLuint LoadTexture(const char *image_path);
float lerp(float v0, float v1, float t);

#endif /* defined(__NYUCodebase__Entity__) */
