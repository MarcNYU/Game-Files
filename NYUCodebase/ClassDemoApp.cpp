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
};



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