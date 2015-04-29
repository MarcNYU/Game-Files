//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 4/14/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "Entity.h"

// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
float timeLeftOver = 0.0f;

void Bullet::Update(float elapsed) {
    x += elapsed;
}
float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

void Entity::Render(std::string shape) {
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(width, height, 0.0);
    glRotatef(rotation, 0.0, 0.0, 0.0);
    
    if (shape == "tr") {
        GLfloat triangle[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
        GLfloat triangleColor[] = {1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0};
        glVertexPointer(2, GL_FLOAT, 0, triangle);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, triangleColor);
        glEnableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
    }
    if (shape == "qu") {
        GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
        GLfloat quadColor[] =  {1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0};
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, quadColor);
        glEnableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_QUADS, 0, 4);
    }
    if (shape == "py") {
        GLfloat polygon[] = {0.0f, 0.5f,
            -0.5f, 0.0f,
            -0.25f, -0.5f,
            0.25f, -0.5f,
            0.5f, 0.0f,};
        GLfloat polygonColor[] = {1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0};
        glVertexPointer(2, GL_FLOAT, 0, polygon);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(5, GL_FLOAT, 0, polygonColor);
        glEnableClientState(GL_COLOR_ARRAY);
        glDrawArrays(GL_POLYGON, 0, 5);
        
    }
}
void Entity::FixedUpdate() {
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
    velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
    velocity_x += acceleration_x * FIXED_TIMESTEP;
    velocity_y += acceleration_y * FIXED_TIMESTEP;
    x += velocity_x * FIXED_TIMESTEP;
    y += velocity_y * FIXED_TIMESTEP;
}


