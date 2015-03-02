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
#include "Entity.h"



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
    
    //Make Assets
    Entity floor;
    
}
ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}
void ClassDemoApp::Render() {
    // render stuff
    SDL_GL_SwapWindow(displayWindow);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(int i=0; i < dynamicEntities.size(); i++) {
        dynamicEntities[i].Render();
    }
    for(int i=0; i < staticEntities.size(); i++) {
        staticEntities[i].Render();
    }
}
void ClassDemoApp::Update(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
    for(int i=0; i < dynamicEntities.size(); i++) {
        dynamicEntities[i].Render();
    }
    for(int i=0; i < staticEntities.size(); i++) {
        staticEntities[i].Update(elapsed);
    }
}
bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    Update(elapsed);
    Render();
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