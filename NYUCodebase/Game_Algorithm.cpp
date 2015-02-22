//
//  Game_Algorithm.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/19/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "Game_Algorithm.h"
#include "Entity.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>


SDL_Window* displayWindow;


void Setup();
bool ProcessEvents();
void Update();
void Render();
void Cleanup();

int main (){
    Setup();
    bool done = false;
    while (!done) {
        done = ProcessEvents();
        Update();
    }
    Cleanup();
}

void Entity::DrawVectorGraphic() {
    
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

void Entity::DrawSprite(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(width, height, 1.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);

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

void PlayerControl () {
    
}

bool ProcessEvents(){
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float lastFrameTicks = 0.0f;
    float rate = 1000.0f;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            return true;
        }
        float ticks = (float)SDL_GetTicks()/rate;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        
        float position, revolutions, sizeX, sizeY;
        
        
        //Keyboard
        if(keys[SDL_SCANCODE_W]) {
//                std::cout<<"UP"<<std::endl;
        }else if (keys[SDL_SCANCODE_S]) {
//                std::cout<<"Down"<<std::endl;
        }else if (keys[SDL_SCANCODE_A]) {
//                std::cout<<"LEFT"<<std::endl;
        }else if (keys[SDL_SCANCODE_D]) {
//                std::cout<<"RIGHT"<<std::endl;
        }else if (keys[SDL_SCANCODE_SPACE]) {
//                std::cout<<"JUMP"<<std::endl;
        }else if (keys[SDL_SCANCODE_1]) {
//                std::cout<<"SLOT 1"<<std::endl;
        }else if (keys[SDL_SCANCODE_2]) {
//                std::cout<<"SLOT 2"<<std::endl;
        }else if (keys[SDL_SCANCODE_3]) {
//                std::cout<<"SLOT 3"<<std::endl;
        }else if (keys[SDL_SCANCODE_TAB]) {
//                std::cout<<"ACTION"<<std::endl;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_P) {
//                std::cout<<"PAUSE STATE"<<std::endl;
            }
        }
        //Mouse
        if(event.type == SDL_MOUSEMOTION) {
            float unitX = (((float)event.motion.x / 800.0f) * 2.666f ) - 1.333f;
            float unitY = (((float)(600-event.motion.y) / 600.0f) * 2.0f ) - 1.0f;
        }else if(event.type == SDL_MOUSEBUTTONDOWN) {
            // event.button.x is the click x position
            // event.button.y is the click y position
            // event.button.button is the mouse button that was clicked (1,2,3,etc.)
        }
        
        Update();
        
    }
    return false;
}

void Cleanup() {
    // cleanup joysticks, textures, etc.
    glClear(GL_COLOR_BUFFER_BIT);
}


GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(surface);
    return textureID;
}


