//
//  pong2.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/17/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>

SDL_Window* displayWindow;


class Entity {
public:
    Entity (float xCord, float yCord, float w, float h, float red = 1.0, float green = 1.0, float blue = 1.0) : x(xCord), y(yCord), rotation(0.0), textureID(NULL), width(w), height(h), r(red), g(green), b(blue){}
    void Draw();
    void Move();
    float x;
    float y;
    float rotation;
    int textureID;
    float width;
    float height;
    float speed;
    float direction_x;
    float direction_y;
    float r;
    float g;
    float b;
};

void Setup();
void update(Entity& ball, Entity& p1, Entity& p2, Entity& ceiling, Entity& floor, Entity& net);
void Cleanup();


int main() {
    Setup();
    
    bool done = false;
    SDL_Event event;
    
    
    Entity p1(0.9, 0.0, 0.1, 0.5);
    Entity p2(-0.9, 0.0, 0.1, 0.5);
    
    Entity ceiling (0.0, 0.9, 2.0, 0.0625);
    Entity floor (0.0, -0.9, 2.0, 0.0625);
    
    Entity net (0.0, 0.0, 0.0435, 1.74, 0.7, 0.7, 0.7);
    
    Entity ball(0.0, 0.0, 0.0435, 0.0625);
    ball.direction_x = -1.0f;
    ball.direction_y = 0.0f;
    ball.speed = 2;
    
    
    
    p1.Draw();
    p2.Draw();
    ceiling.Draw();
    floor.Draw();
    net.Draw();
    ball.Draw();
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float lastFrameTicks = 0.0f;
    
    // game loop
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
            
            /*----------------------------------PLAYER-------------------------------------*/
            if(keys[SDL_SCANCODE_UP]) {
                //                std::cout<<"UP"<<std::endl;
                if ((ceiling.y - (ceiling.height/2)) >= (p1.y + (p1.height/2))) {
                    float y_position = 0.02;
                    p1.y += y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p1.Draw();
                    p2.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                
                
            } else if(keys[SDL_SCANCODE_DOWN]) {
                //                std::cout<<"DOWN"<<std::endl;
                if ((floor.y + (floor.height/2)) <= (p1.y - (p1.height/2))) {
                    float y_position = 0.02;
                    p1.y -= y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p1.Draw();
                    p2.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                
            }
            if(keys[SDL_SCANCODE_W]) {
                //                std::cout<<"W"<<std::endl;
                if ((ceiling.y - (ceiling.height/2)) >= (p2.y + (p2.height/2))) {
                    float y_position = 0.02;
                    p2.y += y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p1.Draw();
                    p2.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                
            } else if(keys[SDL_SCANCODE_S]) {
                //                std::cout<<"S"<<std::endl;
                if ((floor.y + (floor.height/2)) <= (p2.y - (p2.height/2))) {
                    float y_position = 0.02;
                    p2.y -= y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p1.Draw();
                    p2.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
            }
            
            else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    ball.x = 0.0;
                    ball.y = 0.0;
                    p1.y = 0.0;
                    p1.g = 1.0;
                    p1.b = 1.0;
                    p2.y = 0.0;
                    p2.g = 1.0;
                    p2.b = 1.0;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p1.Draw();
                    p2.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
            }
            
            //FIX COLISIONS
            
            /*----------------------------------BALL-------------------------------------*/
            
            // move stuff and check for collisions
            float ticks = (float)SDL_GetTicks()/3000.0f;
            float elapsed = ticks - lastFrameTicks;
            lastFrameTicks = ticks;
            
            float position;
            
            position = elapsed;
            
            //Ball Motion
            // fly a bit
            ball.x += ball.direction_x * ball.speed;
            ball.y += ball.direction_y * ball.speed;
            
            // hit by left racket?
            if (ball.x < p2.x + p2.width &&
                ball.x > p2.x &&
                ball.y < p2.y + p2.height &&
                ball.y > p2.y) {
                // set fly direction depending on where it hit the racket
                // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
                float t = ((ball.y - p2.y) / p2.height) - 0.5f;
                ball.direction_x = fabs(ball.direction_x); // force it to be positive
                ball.direction_y = t;
            }
            
            // hit by right racket?
            if (ball.x > p1.x &&
                ball.x < p1.x + p1.width &&
                ball.y < p1.y + p1.height &&
                ball.y > p1.y) {
                // set fly direction depending on where it hit the racket
                // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
                float t = ((ball.y - p1.y) / p1.height) - 0.5f;
                ball.direction_x = -fabs(ball.direction_x); // force it to be negative
                ball.direction_y = t;
            }
            
            // hit left wall?
            if (ball.x < 0) {
                //        ++score_right;
                ball.x = 800 / 2;
                ball.y = 600 / 2;
                ball.direction_x = fabs(ball.direction_x); // force it to be positive
                ball.direction_y = 0;
            }
            
            // hit right wall?
            if (ball.x > ball.width) {
                //        ++score_left;
                ball.x = 800 / 2;
                ball.y = 600 / 2;
                ball.direction_x = -fabs(ball.direction_x); // force it to be negative
                ball.direction_y = 0;
            }
            
            // hit top wall?
            if (ball.y > 600) {
                ball.direction_y = -fabs(ball.direction_y); // force it to be negative
            }
            
            // hit bottom wall?
            if (ball.y < 0) {
                ball.direction_y = fabs(ball.direction_y); // force it to be positive
            }
            
            // make sure that length of dir stays at 1
            float length = sqrt((ball.direction_x * ball.direction_x) + (ball.direction_y * ball.direction_y));
            if (length != 0.0f) {
                length = 1.0f / length;
                ball.direction_x *= length;
                ball.direction_y *= length;
                
            }
            //            update(ball, p1, p2, ceiling, floor, net);
        }

        SDL_GL_SwapWindow(displayWindow);
    }
    Cleanup();
    SDL_Quit();
    return 0;
}

void Entity::Draw() {
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(width, height, 0.0);
    glRotatef(rotation, 0.0, 0.0, 0.0);
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    GLfloat quadColor[] =  {r, g, b, 1.0,
        r, g, b, 1.0,
        r, g, b, 1.0,
        r, g, b, 1.0};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, quadColor);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
}

void Setup() {
    // setup SDL
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    
    // setup OpenGL
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    // Set our projection matrix
    glClearColor(0.33f, 1.0f, 0.33f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
}


void update(Entity& ball, Entity& p1, Entity& p2, Entity& ceiling, Entity& floor, Entity& net) {
        // update ball
    /*----------------------------------BALL-------------------------------------*/
    // fly a bit
    ball.x += ball.direction_x * ball.speed;
    ball.y += ball.direction_y * ball.speed;
    
    // hit by left racket?
    if (ball.x < p2.x + p2.width &&
        ball.x > p2.x &&
        ball.y < p2.y + p2.height &&
        ball.y > p2.y) {
        // set fly direction depending on where it hit the racket
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball.y - p2.y) / p2.height) - 0.5f;
        ball.direction_x = fabs(ball.direction_x); // force it to be positive
        ball.direction_y = t;
    }
    
    // hit by right racket?
    if (ball.x > p1.x &&
        ball.x < p1.x + p1.width &&
        ball.y < p1.y + p1.height &&
        ball.y > p1.y) {
        // set fly direction depending on where it hit the racket
        // (t is 0.5 if hit at top, 0 at center, -0.5 at bottom)
        float t = ((ball.y - p1.y) / p1.height) - 0.5f;
        ball.direction_x = -fabs(ball.direction_x); // force it to be negative
        ball.direction_y = t;
    }
    
    // hit left wall?
    if (ball.x < 0) {
//        ++score_right;
        ball.x = 800 / 2;
        ball.y = 600 / 2;
        ball.direction_x = fabs(ball.direction_x); // force it to be positive
        ball.direction_y = 0;
    }
    
    // hit right wall?
    if (ball.x > ball.width) {
//        ++score_left;
        ball.x = 800 / 2;
        ball.y = 600 / 2;
        ball.direction_x = -fabs(ball.direction_x); // force it to be negative
        ball.direction_y = 0;
    }
    
    // hit top wall?
    if (ball.y > 600) {
        ball.direction_y = -fabs(ball.direction_y); // force it to be negative
    }
    
    // hit bottom wall?
    if (ball.y < 0) {
        ball.direction_y = fabs(ball.direction_y); // force it to be positive
    }
    
    // make sure that length of dir stays at 1
    float length = sqrt((ball.direction_x * ball.direction_x) + (ball.direction_y * ball.direction_y));
    if (length != 0.0f) {
        length = 1.0f / length;
        ball.direction_x *= length;
        ball.direction_y *= length;
    }
    
    // Redisplay frame
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    p1.Draw();
    p2.Draw();
    ceiling.Draw();
    floor.Draw();
    net.Draw();
    ball.Draw();
}


void Cleanup() {
    // cleanup joysticks, textures, etc.
    glClear(GL_COLOR_BUFFER_BIT);
}
