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

#define MAX_BULLETS 30


class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void shootBullet();
    void Render();
    void Update();
private:
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    int bulletIndex = 0;
//    Bullet bullets[MAX_BULLETS];
};


//void ClassDemoApp::shootBullet() {
//    bullets[bulletIndex].visible = true;
//    bullets[bulletIndex].x = -1.2;
//    bullets[bulletIndex].y = 0.0;
//    bullets[bulletIndex].angle = (float)(45 - (rand() % 90));
//    bulletIndex++;
//    if(bulletIndex > MAX_BULLETS-1) {
//        bulletIndex = 0;
//    }
//}

enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL };

int state;

class gameStates : ClassDemoApp {
public:
    gameStates () : ClassDemoApp(){}
    void Render();
    void Update();
};

gameStates mainMenu;
gameStates gameLevel;

void ClassDemoApp::Render() {
    switch(state) {
        case STATE_MAIN_MENU:
            mainMenu.Render();
            break;
        case STATE_GAME_LEVEL:
            gameLevel.Render();
            break;
    }
}

void ClassDemoApp::Update() {
    switch(state) {
        case STATE_MAIN_MENU:
            mainMenu.Update();
            break;
        case STATE_GAME_LEVEL:
            gameLevel.Update();
            break;
    }
}