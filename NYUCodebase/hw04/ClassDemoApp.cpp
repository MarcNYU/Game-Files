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
void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    Entity player(0.0, 0.0, 0.125, 0.125);
    player.velocity_x = 1.0;
    player.velocity_y = 1.0;
    player.acceleration_x = 1.0;
    player.acceleration_y = 1.0;
    player.friction_x = 1.0;
    player.friction_y = 1.0;
    player.gravity_x = 1.0;
    player.gravity_y = 1.5;
    
    Entity floor(0.0, -1.0, 2.0, 0.125);
    
}
ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}
void ClassDemoApp::Render() {
    // render stuff
    SDL_GL_SwapWindow(displayWindow);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
//    for(int i=0; i < dynamicEntities.size(); i++) {
//        dynamicEntities[i].Render();
//    }
//    for(int i=0; i < staticEntities.size(); i++) {
//        staticEntities[i].Render();
//    }
}
void ClassDemoApp::Update(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
//    for(int i=0; i < dynamicEntities.size(); i++) {
//        dynamicEntities[i].Update(elapsed);
//    }
//    for(int i=0; i < staticEntities.size(); i++) {
//        staticEntities[i].Update(elapsed);
//    }
    
}
bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    timeLeftOver = fixedElapsed;
    animationElapsed += elapsed;
    
//    Update(elapsed);
//    Render();
    const int runLeft[] = {18, 17, 18, 19, 16};
    const int runRight[] = {3, 2, 3, 4, 2};
    const int numFrames = 4;
    float animationElapsed = 0.0f;
    float framesPerSecond = 300.0f;
    int currentIndex = 0;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float timeLeftOver = 0.0f;
    
    float penetration = fabs((player.y - floor.y) - ((player.y - (player.height/2)) - (floor.y + (floor.height/2))));
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                player.velocity_y = lerp(player.velocity_y, 0.0f, FIXED_TIMESTEP * player.friction_y);
                
                player.velocity_y += player.acceleration_y * FIXED_TIMESTEP;
                
                player.y += player.velocity_y * FIXED_TIMESTEP;
                
                player.velocity_y += player.gravity_y * elapsed;
                
                glClear(GL_COLOR_BUFFER_BIT);
                if (player.direction_x > 0.0) {
                    player.DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
                    floor.DrawSprite(0, 0, 1.0, 1.0);
                } else if (player.direction_x < 0.0) {
                    player.DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
                    floor.DrawSprite(0, 0, 1.0, 1.0);
                }
                
            }
        }

    }
    if(animationElapsed > 1.0/framesPerSecond) {
        currentIndex++;
        animationElapsed = 0.0;
        if(currentIndex > numFrames-1) {
            currentIndex = 0;
        }
    }
    
    player.y -= player.gravity_y * FIXED_TIMESTEP;
    
    if (player.direction_x > 0.0) {
        glClear(GL_COLOR_BUFFER_BIT);
        player.DrawSprite(LoadTexture("beck.png"), 0, 28.0, 1.0);
        floor.DrawSprite(0, 0, 1.0, 1.0);
    } else if (player.direction_x < 0.0) {
        glClear(GL_COLOR_BUFFER_BIT);
        player.DrawSprite(LoadTexture("beck.png"), 15, 28.0, 1.0);
        floor.DrawSprite(0, 0, 1.0, 1.0);
    }
    if ((player.y - (player.height/2)) < (floor.y + (floor.height/2))){
        player.y += player.gravity_y * FIXED_TIMESTEP;
    }
    
    if(keys[SDL_SCANCODE_LEFT]) {
        player.velocity_x = lerp(player.velocity_x, 0.0f, FIXED_TIMESTEP * player.friction_x);
        
        player.velocity_x += player.acceleration_x * FIXED_TIMESTEP;
        
        player.x -= player.velocity_x * FIXED_TIMESTEP;
        
        player.velocity_x -= player.gravity_x * elapsed;
        
        
        player.direction_x = -1.0;
        glClear(GL_COLOR_BUFFER_BIT);
        player.DrawSprite(LoadTexture("beck.png"), runLeft[4], 28.0, 1.0);
        floor.DrawSprite(0, 0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        player.DrawSprite(LoadTexture("beck.png"), runLeft[currentIndex], 28.0, 1.0);
        floor.DrawSprite(0, 0, 1.0, 1.0);
        if(keys[SDL_SCANCODE_UP]) {
            glClear(GL_COLOR_BUFFER_BIT);
            if (player.direction_x < 0.0) {
                player.DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
                floor.DrawSprite(0, 0, 1.0, 1.0);
            }
        }
    } else if(keys[SDL_SCANCODE_RIGHT]) {
        player.velocity_x = lerp(player.velocity_x, 0.0f, FIXED_TIMESTEP * player.friction_x);
        
        player.velocity_x += player.acceleration_x * FIXED_TIMESTEP;
        
        player.x += player.velocity_x * FIXED_TIMESTEP;
        
        player.velocity_x += player.gravity_x * elapsed;
        
        player.direction_x = 1.0;
        glClear(GL_COLOR_BUFFER_BIT);
        player.DrawSprite(LoadTexture("beck.png"), runRight[4], 28.0, 1.0);
        floor.DrawSprite(0, 0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        player.DrawSprite(LoadTexture("beck.png"), runRight[currentIndex], 28.0, 1.0);
        floor.DrawSprite(0, 0, 1.0, 1.0);
        if(keys[SDL_SCANCODE_UP]) {
            glClear(GL_COLOR_BUFFER_BIT);
            if (player.direction_x > 0.0) {
                player.DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
                floor.DrawSprite(0, 0, 1.0, 1.0);
            }
        }
    } else if(keys[SDL_SCANCODE_UP]) {
        glClear(GL_COLOR_BUFFER_BIT);
        if (player.direction_x > 0.0) {
            player.DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
        } else if (player.direction_x < 0.0) {
            player.DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
        }
    }
    

    SDL_GL_SwapWindow(displayWindow);
    
    glClear(GL_COLOR_BUFFER_BIT);
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