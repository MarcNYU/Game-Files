//
//  ClassDemoApp.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/21/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

//#include "ClassDemoApp.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ClassDemoApp.h"



ClassDemoApp::ClassDemoApp() {
    Init();
    done = false;
    lastFrameTicks = 0.0f;
}
float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    
    Entity player(0.0, 0.0, 0.125, 0.125);
    player.direction_x = 0.0;
    player.direction_y = 1.0;
    player.numFrames = 4;
    player.framesPerSecond = 7.0f;
    
    Entity floor(0.0, -0.8, 1.75, 0.125);
    Entity rightWall(0.845, 0.0, 0.0625, 1.5);
    Entity leftWall(-0.844, 0.0, 0.0625, 1.5);
    Entity platform1(-0.7, -0.5, 0.25, 0.0625);
    Entity platform2(0.7, -0.5, 0.25, 0.0625);
    Entity platform3(0.0, -0.2, 0.5, 0.0625);
    Entity platform4(-0.7, 0.1, 0.25, 0.0625);
    Entity platform5(0.7, 0.1, 0.25, 0.0625);
    
    dynamicEntities.push_back(player);
    staticEntities.push_back(floor);
    staticEntities.push_back(leftWall);
    staticEntities.push_back(rightWall);
    staticEntities.push_back(platform1);
    staticEntities.push_back(platform2);
//    staticEntities.push_back(platform3);
    staticEntities.push_back(platform4);
    staticEntities.push_back(platform5);
    
}
ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}
void ClassDemoApp::Render(float elapsed) {
    // render stuff
    SDL_GL_SwapWindow(displayWindow);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i=0; i < dynamicEntities.size(); i++) {
        dynamicEntities[i].Render(elapsed);
    }
    for(int i=0; i < staticEntities.size(); i++) {
        staticEntities[i].Render(elapsed);
    }
}
void ClassDemoApp::FixedUpdate() {
    dynamicEntities[0].velocity_x = lerp(dynamicEntities[0].velocity_x, 0.0f, FIXED_TIMESTEP * dynamicEntities[0].friction_x);
    dynamicEntities[0].velocity_y = lerp(dynamicEntities[0].velocity_y, 0.0f, FIXED_TIMESTEP * dynamicEntities[0].friction_y);
    dynamicEntities[0].velocity_x += dynamicEntities[0].acceleration_x * FIXED_TIMESTEP;
    dynamicEntities[0].velocity_y += dynamicEntities[0].acceleration_y * FIXED_TIMESTEP;
    dynamicEntities[0].x += dynamicEntities[0].velocity_x * FIXED_TIMESTEP;
    dynamicEntities[0].y += dynamicEntities[0].velocity_y * FIXED_TIMESTEP;
    
//    dynamicEntities[0].gravity_x = lerp(dynamicEntities[0].gravity_x, 0.0f, FIXED_TIMESTEP * dynamicEntities[0].friction_x);
//    dynamicEntities[0].gravity_y = lerp(dynamicEntities[0].gravity_y, 0.0f, FIXED_TIMESTEP * dynamicEntities[0].friction_y);
//    dynamicEntities[0].gravity_x -= dynamicEntities[0].acceleration_x * FIXED_TIMESTEP;
//    dynamicEntities[0].gravity_y -= dynamicEntities[0].acceleration_y * FIXED_TIMESTEP;
//    dynamicEntities[0].x -= dynamicEntities[0].gravity_x * FIXED_TIMESTEP;
//    dynamicEntities[0].y -= dynamicEntities[0].gravity_y * FIXED_TIMESTEP;
    
}
void ClassDemoApp::Update(float elapsed) {
    
    dynamicEntities[0].velocity_x -= dynamicEntities[0].gravity_x * elapsed;
    dynamicEntities[0].velocity_y -= dynamicEntities[0].gravity_y * elapsed;
    
    dynamicEntities[0].gravity_y = 2.0;
    dynamicEntities[0].friction_x = 2.0;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                dynamicEntities[0].velocity_y += 200.0;
                dynamicEntities[0].Update(elapsed);
            }
        }

    }
    
    for(int i=0; i < staticEntities.size(); i++) {
        if (dynamicEntities[0].collidesWith(&staticEntities[i])) {
            if (dynamicEntities[0].collidedLeft || dynamicEntities[0].collidedRight) {
                penetration = fabsf(fabsf(dynamicEntities[0].x - staticEntities[i].x) - dynamicEntities[0].x+dynamicEntities[0].width/2 - staticEntities[i].x+staticEntities[i].width/2);
                if (dynamicEntities[0].collidedLeft) {
                    dynamicEntities[0].x += penetration + dynamicEntities[0].offset;
                    dynamicEntities[0].Update(elapsed);
                }
                if (dynamicEntities[0].collidedRight) {
                    dynamicEntities[0].x -= penetration + dynamicEntities[0].offset;
                    dynamicEntities[0].Update(elapsed);
                }
            }
            if (dynamicEntities[0].collidedTop || dynamicEntities[0].collidedBottom) {
                 penetration = fabsf(fabsf(dynamicEntities[0].x - staticEntities[i].x) - dynamicEntities[0].x+dynamicEntities[0].width/2 - staticEntities[i].x+staticEntities[i].width/2);
                if (dynamicEntities[0].collidedBottom) {
                    dynamicEntities[0].velocity_y = 0.0;
                    dynamicEntities[0].Update(elapsed);
                }
                if (dynamicEntities[0].collidedTop) {
                    dynamicEntities[0].y -= penetration + dynamicEntities[0].offset;
                    dynamicEntities[0].Update(elapsed);
                }
            }
        }
        
    }
    
    for(int i=0; i < dynamicEntities.size(); i++) {
        if (i == 0) {
            if(keys[SDL_SCANCODE_LEFT]) {
                dynamicEntities[0].direction_x = -1.0;
                dynamicEntities[i].Update(elapsed);
            } else if(keys[SDL_SCANCODE_RIGHT]) {
                dynamicEntities[0].direction_x = 1.0;
                dynamicEntities[i].Update(elapsed);
            } else {
                dynamicEntities[0].friction_x = 20.0;
                dynamicEntities[0].acceleration_x = 0.0;
            }
            
        }
    }
    
    for(int i=0; i < staticEntities.size(); i++) {
        staticEntities[i].Update(elapsed);
    }
    
    
    
}
bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    float fixedElapsed = elapsed + timeLeftOver;
    if(fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
        fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
    }
    while (fixedElapsed >= FIXED_TIMESTEP ) {
        fixedElapsed -= FIXED_TIMESTEP;
        FixedUpdate();
    }
    timeLeftOver = fixedElapsed;
    
    Update(fixedElapsed);
    Render(elapsed);
    return done;
}
void ClassDemoApp::shootBullet() {
    bullets[bulletIndex].visible = true;
    bullets[bulletIndex].x = -1.2;
    bullets[bulletIndex].y = 0.0;
    bullets[bulletIndex].angle = (float)(45 - (rand() % 90));
    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
}


//enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL };
//
//int state;
//
//class gameStates : ClassDemoApp {
//public:
//    gameStates () : ClassDemoApp(){}
//    void Render();
//    void Update();
//};
//
//gameStates mainMenu;
//gameStates gameLevel;
//void ClassDemoApp::Render() {
//    switch(state) {
//        case STATE_MAIN_MENU:
//            mainMenu.Render();
//            break;
//        case STATE_GAME_LEVEL:
//            gameLevel.Render();
//            break;
//    }
//}
//
//void ClassDemoApp::Update() {
//    switch(state) {
//        case STATE_MAIN_MENU:
//            mainMenu.Update();
//            break;
//        case STATE_GAME_LEVEL:
//            gameLevel.Update();
//            break;
//    }
//}