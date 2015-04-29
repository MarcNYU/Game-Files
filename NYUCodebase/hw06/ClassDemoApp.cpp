//
//  ClassDemoApp.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 4/14/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include "ClassDemoApp.h"
#include <string>


ClassDemoApp::ClassDemoApp() {
    Init();
    done = false;
    lastFrameTicks = 0.0f;
}
ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
    Entity player(0.0, 0.0, 0.0625, 0.0625);
    dynamicEntities.push_back(player);
    for (int x = 0; x < rand()%10; x++) {
//        Entity asteriod((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX);
         Entity asteriod(-0.2, 0.5, 0.5, 0.5);
        staticEntities.push_back(asteriod);
    }

    
}
void ClassDemoApp::Render() {
    // render stuff
    
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //    glTranslatef(-entities[0].y, -entities[0].x, 0.0f);
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    dynamicEntities[0].Render("tr");
    for (size_t c = 0; c < staticEntities.size(); c++) {
        staticEntities[c].Render("py");
    }
    
}
void ClassDemoApp::Update(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
    if(keys[SDL_SCANCODE_UP]) {
        
        
    }else if (keys[SDL_SCANCODE_DOWN]) {
        
    }else if (keys[SDL_SCANCODE_LEFT]) {
        
    }else if (keys[SDL_SCANCODE_RIGHT]) {
        
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

