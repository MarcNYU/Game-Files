//
//  pong.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/13/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

//#include "pong.h"
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
void ProcessEvents();
bool collisonCheck(Entity& obj1, Entity& obj2);
void Update(Entity& obj, float lastFrameTicks);
void Render();
void Cleanup();



int main() {
    Setup();
    
    bool done = false;
    SDL_Event event;
    
    Entity p1(-0.9, 0.0, 0.07, 0.333);
    Entity p2(0.9, 0.0, 0.07, 0.333);
    
    Entity ceiling (0.0, 1.0, 2.0, 0.0625);
    Entity floor (0.0, -1.0, 2.0, 0.0625);
    
    Entity net (0.0, 0.0, 0.0435, 1.9, 0.7, 0.7, 0.7);
    
    Entity ball(0.0, 0.0, 0.0435, 0.0625);
    ball.direction_x = -1.0f;
    ball.direction_y = 0.0f;
    ball.speed = 2;
    
    
    
    p2.Draw();
    p1.Draw();
    ceiling.Draw();
    floor.Draw();
    net.Draw();
    ball.Draw();
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float lastFrameTicks = 0.0f;
    
    // game loop
    
//    bool top_collison = false;
//    bool bottom_collison = false;
//    bool right_collison = false;
//    bool left_collison = false;
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
            
            
            //FIX COLISIONS
            
            /*----------------------------------BALL-------------------------------------*/
            
            // move stuff and check for collisions
            float ticks = (float)SDL_GetTicks()/3000.0f;
            float elapsed = ticks - lastFrameTicks;
            lastFrameTicks = ticks;
            
            float position;
            
            position = elapsed;
            
            
            float length = sqrt((ball.direction_x * ball.direction_x) + (ball.direction_y * ball.direction_y));
            if (length != 0.0f) {
                length = 1.0f / length;
                ball.direction_x *= length;
                ball.direction_y *= length;
                
            }
            //Upper Bound
            if ((ball.y + (ball.height/2)) > (ceiling.y - (ceiling.height/2))) {
//            if (ball.y > 600 - (ceiling.height/2)) {
//            if (!(ball.y < 1.9)) {
//                top_collison = true;
                ball.y -= position;
                ball.direction_y = -fabs(ball.direction_y); // negative
                
                glClear(GL_COLOR_BUFFER_BIT);
                p2.Draw();
                p1.Draw();
                ceiling.Draw();
                floor.Draw();
                net.Draw();
                ball.Draw();
            }
            //Player 1 wasd
//            else if (!((ball.x - (ball.width/2)) > (p2.x + (p2.width/2)))){
            else if (ball.x <= p1.x + p1.width &&
                     ball.x >= p1.x &&
                     ball.y <= p1.y + p1.height &&
                     ball.y >= p1.y){
//                left_collison = true;
                ball.x += position;
                float t = ((ball.y - p1.y) / p1.height) - 0.5f;
                ball.direction_x = fabs(ball.direction_x); // positive
                ball.direction_y = t;
                
                glClear(GL_COLOR_BUFFER_BIT);
                p2.Draw();
                p1.Draw();
                ceiling.Draw();
                floor.Draw();
                net.Draw();
                ball.Draw();
            }
            //Player 2 arrows
//            else if (!((ball.x + (ball.width/2)) < (p1.x - (p1.width/2)))){
            else if (ball.x >= p2.x &&
                     ball.x <= p2.x + p2.width &&
                     ball.y <= p2.y + p2.height &&
                     ball.y >= p2.y){
//                right_collison = true;
                ball.x -= position;
                float t = ((ball.y - p2.y) / p2.height) - 0.5f;
                ball.direction_x = -fabs(ball.direction_x); // negative
                ball.direction_y = t;
                
                glClear(GL_COLOR_BUFFER_BIT);
                p2.Draw();
                p1.Draw();
                ceiling.Draw();
                floor.Draw();
                net.Draw();
                ball.Draw();
            }
            //Lower Bound
            else if (!((ball.y - (ball.height/2)) > (floor.y + (floor.height/2)))){
//            else if (ball.y < -600 + (ceiling.height/2)){
//            else if (!(ball.y > -600)){
//                bottom_collison = true;
                ball.y += position;
                ball.direction_y = fabs(ball.direction_y); // positive
                
                glClear(GL_COLOR_BUFFER_BIT);
                p2.Draw();
                p1.Draw();
                ceiling.Draw();
                floor.Draw();
                net.Draw();
                ball.Draw();
            }
            // hit left wall
            else if (ball.x < -1.0) {
                //score_right;
                p2.g = 0.0;
                p2.b = 0.0;
                
                glClear(GL_COLOR_BUFFER_BIT);
                p2.Draw();
                p1.Draw();
                ceiling.Draw();
                floor.Draw();
                net.Draw();
                ball.Draw();

            }
            // hit right wall
            else if (ball.x > 1.0) {
                //score_left;
                p1.g = 0.0;
                p1.b = 0.0;
                
                glClear(GL_COLOR_BUFFER_BIT);
                p2.Draw();
                p1.Draw();
                ceiling.Draw();
                floor.Draw();
                net.Draw();
                ball.Draw();
                
            }else{
//                ball.x += ball.direction_x * ball.speed;
//                ball.y += ball.direction_y * ball.speed;
                if (ball.direction_x < 0.0) {
                    ball.x -= position;
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }else if (ball.direction_x > 0.0){
                    ball.x += position;
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                if (ball.direction_y < 0.0) {
                    ball.y -= position;
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }else if (ball.direction_y > 0.0){
                    ball.y += position;
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                
                
                
//                if ((top_collison == false) && (bottom_collison == false) && (right_collison == false) && (left_collison == false)) {
//                    ball.x -= positionX;
////                    ball.y += positionY;
//                    glClear(GL_COLOR_BUFFER_BIT);
//                    p1.Draw();
//                    p2.Draw();
//                    ceiling.Draw();
//                    floor.Draw();
//                    net.Draw();
//                    ball.Draw();
//                }
//                else if(top_collison == true){
//                    ball.y -= positionY;
//                    glClear(GL_COLOR_BUFFER_BIT);
//                    p1.Draw();
//                    p2.Draw();
//                    ceiling.Draw();
//                    floor.Draw();
//                    net.Draw();
//                    ball.Draw();
//                }
//                else if(right_collison == true){
//                    ball.x -= positionX;
//                    glClear(GL_COLOR_BUFFER_BIT);
//                    p1.Draw();
//                    p2.Draw();
//                    ceiling.Draw();
//                    floor.Draw();
//                    net.Draw();
//                    ball.Draw();
//                }
//                else if(bottom_collison == true){
//                    ball.y += positionY;
//                    glClear(GL_COLOR_BUFFER_BIT);
//                    p1.Draw();
//                    p2.Draw();
//                    ceiling.Draw();
//                    floor.Draw();
//                    net.Draw();
//                    ball.Draw();
//                }
//                else if(left_collison == true){
//                    ball.x += positionX;
//                    glClear(GL_COLOR_BUFFER_BIT);
//                    p1.Draw();
//                    p2.Draw();
//                    ceiling.Draw();
//                    floor.Draw();
//                    net.Draw();
//                    ball.Draw();
//                }
            }
            
            
            
            /*----------------------------------PLAYER-------------------------------------*/
            if(keys[SDL_SCANCODE_UP]) {
//                std::cout<<"UP"<<std::endl;
                if ((ceiling.y - (ceiling.height/2)) >= (p2.y + (p2.height/2))) {
                    float y_position = 0.02;
                    p2.y += y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                
                
            } else if(keys[SDL_SCANCODE_DOWN]) {
//                std::cout<<"DOWN"<<std::endl;
                if ((floor.y + (floor.height/2)) <= (p2.y - (p2.height/2))) {
                    float y_position = 0.02;
                    p2.y -= y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                

            }
            if(keys[SDL_SCANCODE_W]) {
//                std::cout<<"W"<<std::endl;
                if ((ceiling.y - (ceiling.height/2)) >= (p1.y + (p1.height/2))) {
                    float y_position = 0.02;
                    p1.y += y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
                
                
            } else if(keys[SDL_SCANCODE_S]) {
//                std::cout<<"S"<<std::endl;
                if ((floor.y + (floor.height/2)) <= (p1.y - (p1.height/2))) {
                    float y_position = 0.02;
                    p1.y -= y_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
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
                    p2.y = 0.0;
                    p2.g = 1.0;
                    p2.b = 1.0;
                    p1.y = 0.0;
                    p1.g = 1.0;
                    p1.b = 1.0;
                    glClear(GL_COLOR_BUFFER_BIT);
                    p2.Draw();
                    p1.Draw();
                    ceiling.Draw();
                    floor.Draw();
                    net.Draw();
                    ball.Draw();
                }
            }
        }
        SDL_GL_SwapWindow(displayWindow);
        
        Render();
        
        
    }
    Cleanup();
    SDL_Quit();
    return 0;
}

void Entity::Draw() {
    
    glMatrixMode(GL_MODELVIEW);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
}

//bool collisonCheck(Entity& obj1, Entity& obj2) {
//    //OBJECT 1
//    float top_surface1 = obj1.y + (obj1.height/2);
//    float bottom_surface1 = obj1.y - (obj1.height/2);
//    float right_surface1 = obj1.x + (obj1.width/2);
//    float left_surface1 = obj1.x - (obj1.width/2);
//    
//    //OBJECT 2
//    float top_surface2 = obj2.y + (obj2.height/2);
//    float bottom_surface2 = obj2.y - (obj2.height/2);
//    float right_surface2 = obj2.x + (obj2.width/2);
//    float left_surface2 = obj2.x - (obj2.width/2);
//    
//    
//    return ((bottom_surface1 <= top_surface2) || (left_surface1 <= right_surface2) || (top_surface1 >= bottom_surface2) || (right_surface1 >= left_surface2));
//}

//bool collisonCheck(Entity& obj1, Entity& obj2){
//    //OBJECT 1
//    float radiXA = obj1.x + obj1.width/2;//X radius
//    float radiYA = obj1.y + obj1.height/2;//Y radius
//
//    //OBJECT 2
//    float radiXB = obj1.x + obj1.width/2;//X radius
//    float radiYB = obj1.y + obj1.height/2;//Y radius
//    
//    float dist = sqrtf( powf( (obj1.x - obj2.x), 2.0) + powf( (obj1.y - obj2.y), 2.0) );
//    
//    return (dist >= (radiXA + radiXB) || dist >= (radiYA + radiYB));
//
//}

//void Update(Entity& obj, float lastFrameTicks) {
//    // move stuff and check for collisions
//    float ticks = (float)SDL_GetTicks()/1000.0f;
//    float elapsed = ticks - lastFrameTicks;
//    lastFrameTicks = ticks;
//    
//    //Ball Motion
//    float direction_vector = sqrtf( powf(obj.x, 2.0) + powf(obj.y, 2.0) );
//    float position;
//    
//    position = direction_vector * elapsed;
//    
//    obj.x = position;
//    obj.y = position;
//    obj.Draw();
//    
//}
//void Render() {
//    // for all game elements
//    // setup transforms, render sprites
//}
void Cleanup() {
    // cleanup joysticks, textures, etc.
    glClear(GL_COLOR_BUFFER_BIT);
}




//void ProcessEvents() {
//
//    bool done = false;
//    SDL_Event event;
//
//    // our SDL event loop
//    while (!done) {
//        // check input events
////        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
//
//        // game loop
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//                done = true;
//            }
//            /*----------------------------------KEYBOARD-------------------------------------*/
//
//            //check code
//            const Uint8 *keys = SDL_GetKeyboardState(NULL);
//            if(keys[SDL_SCANCODE_LEFT]) {
//                // go left!
//            } else if(keys[SDL_SCANCODE_RIGHT]) {
//                // go right!
//            }
//            //----------
//            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//                done = true;
//            } else if(event.type == SDL_KEYDOWN) {
//                if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
//                    // DO AN ACTION WHEN SPACE IS PRESSED!
//                }
//            }
//
//        }
//    }
//}