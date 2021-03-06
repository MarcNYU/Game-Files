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
#include <SDL_mixer.h>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>


#include "ClassDemoApp.h"



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
//    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
    
    
    int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 );
    
    Mix_Chunk *someSound;
    //    someSound = Mix_LoadWAV("some_sound.wav");
    
    music = Mix_LoadMUS("video marc.mp3");
    
    Entity player;
    player.numFrames = 4;
    player.framesPerSecond = 3.0;
    player.type = "Player";
    player.width = 0.05;
    player.height = 0.05;
    player.friction_x = 5.0;
    player.gravity_y = 1.0;
    std::cout << "initial: " << player.x << "," << player.y << std::endl;
    
    Entity goal;
    goal.type = "Goal";
    goal.width = 0.05;
    goal.height = 0.05;
    
    Entity crate;
    crate.type = "Crate";
    crate.width = 0.05;
    crate.height = 0.05;
    
    Entity button;
    button.type = "Button";
    button.width = 0.05;
    button.height = 0.05;
    
    //    Entity ice;
    //    ice.width = 0.05;
    //    ice.height = 0.05;
    
    Entity wall1;
    wall1.type = "Wall1";
    wall1.width = 0.05;
    wall1.height = 0.05;
    
    Entity wall2;
    wall2.type = "Wall2";
    wall2.width = 0.05;
    wall2.height = 0.05;
    
    Entity saw1;
    saw1.type = "Saw1";
    saw1.width = 0.07;
    saw1.height = 0.07;
    
    Entity saw2;
    saw2.type = "Saw2";
    saw2.width = 0.07;
    saw2.height = 0.07;
    
    Entity saw3;
    saw3.type = "Saw3";
    saw3.width = 0.07;
    saw3.height = 0.07;
    
    Entity saw4;
    saw4.type = "Saw4";
    saw4.width = 0.07;
    saw4.height = 0.07;
    
    entities.push_back(player);
    entities.push_back(goal);
    entities.push_back(crate);
    entities.push_back(button);
    entities.push_back(wall1);
    entities.push_back(wall2);
    entities.push_back(saw1);
    entities.push_back(saw2);
    entities.push_back(saw3);
    entities.push_back(saw4);
    //    int num = 0;
    //    while (num < 42) {
    //        std::string str = std::to_string(num+1);
    //        ice.type = "Ice"+str;
    //        entities.push_back(ice);
    //        num++;
    //    }
    for (int i = 0; i < entities.size(); i++) {
        std::cout << entities[i].type << std::endl;
    }
    
    state = 1;
    switch (state) {
        case 0:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/tremor.txt");
            break;
        case 1:
            readFile("NYUCodebase.app/Contents/Resources/level1_new.txt");
            break;
        case 2:
            readFile("NYUCodebase.app/Contents/Resources/level2_new.txt");
            break;
        case 3:
            readFile("NYUCodebase.app/Contents/Resources/level4_new.txt");
            break;
        case 4:
            readFile("NYUCodebase.app/Contents/Resources/game_over.txt");
            break;
            
    }
    
    //    readFile("NYUCodebase.app/Contents/Resources/level3_new.txt");
    
}


bool entityCollision(Entity sprite_1, Entity sprite_2){
    //If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
    if( (sprite_1.x >= sprite_2.x && sprite_1.x <= (sprite_2.x + sprite_2.width)) ||
       ((sprite_1.x + sprite_1.width) >= sprite_2.x && (sprite_1.x + sprite_1.width) <= (sprite_2.x + sprite_2.width)) ){
        //Now we look at the y axis:
        if( (sprite_1.y >= sprite_2.y && sprite_1.y <= (sprite_2.y + sprite_2.height)) ||
           ((sprite_1.y + sprite_1.height) >= sprite_2.y && (sprite_1.y + sprite_1.height) <= (sprite_2.y + sprite_2.height)) ){
            //The sprites appear to overlap.
            return true;
        }
    }
    //The sprites do not overlap:
    return false;
}


void ClassDemoApp::RenderMainMenu() {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    drawTitle();
    glPopMatrix();
    
}
void ClassDemoApp::RenderGameLevel1(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameLevel2(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameLevel3(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameOver(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    
    glPushMatrix();
    drawTitle();
    glPopMatrix();
}
void ClassDemoApp::UpdateMainMenu() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                state = 5;
            }
        }
    }
}
void ClassDemoApp::UpdateGameLevel1(float elapsed) {
    std::cout << "In Level1" << std::endl;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                if (entities[0].collidedBottom) {
                    entities[0].velocity_y = 1.0;
                    entities[0].Update(elapsed);
                    entities[0].collidedBottom = false;
                }
                
            }
        }
    }
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i].type == "Player") {
            //            worldToTileCoordinates(entities[i].x, entities[i].y, x, y);
            //Apply Gravity
            if (entities[0].collidedBottom) {
                entities[0].velocity_y = 0.0;
                entities[0].Update(elapsed);
            }
            if (entities[0].collidedTop) {
                entities[0].velocity_y = -1.0;
                entities[0].Update(elapsed);
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                //                if (entities[i].collidedBottom && !entities[i].collidedRight) {
                //                    entities[i].direction_x = 1.0;
                //                    entities[i].Update(elapsed);
                //                }
                entities[0].direction_x = 1.0;
                entities[0].Update(elapsed);
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                //                if (entities[i].collidedBottom && !entities[i].collidedLeft) {
                //                    entities[i].direction_x = -1.0;
                //                    entities[i].Update(elapsed);
                //                }
                entities[0].direction_x = -1.0;
                entities[0].Update(elapsed);
            }
            if(keys[SDL_SCANCODE_SPACE]) {
                entities[0].charge += 1;
                entities[0].Update(elapsed);
                if (entities[0].collidedBottom) {
                    //cause tremor
                    //update all entites
                    //                     charge++;
                    //                     entities[0].Update(elapsed);
                }
                std::cout << "Meter: " << entities[0].charge << std::endl;
            }
        }
        if (entityCollision(entities[0], entities[i])) {
            if (entities[i].type == "Goal") {
                //Win State
                state = 2;
            }
            if (entities[i].type == "Crate") {
                //Do something
            }
        }
        
        if (entities[0].charge != 0) {
            if (entities[0].charge >= 3) {
                //ADD SMALL SMOKE EFFECT
                if (entities[i].type == "Crate") {
                    entities[i].direction_y = 1.0;
                    entities[i].Update(elapsed);
                }
                entities[0].charge = 0;
            }
            //            if (3 < entities[0].charge <= 6) {
            if (3 < entities[0].charge && entities[0].charge <= 6) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == earth) {
                 //ACTIVATE DUST1
                 }
                 if (surface == log) {
                 //ACTIVATE DUST2
                 }
                 */
                if (entities[i].type == "Crate") {
                    if (entities[0].x > entities[i].x) {
                        entities[i].direction_x = -1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    if (entities[0].x < entities[i].x) {
                        entities[i].direction_x = 1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    
                }
                entities[0].charge = 0;
            }
            //            if (6 < entities[0].charge <= 9) {
            if (6 < entities[0].charge && entities[0].charge <= 9) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == earth) {
                 //ACTIVATE DUST1
                 }
                 if (surface == log) {
                 //ACTIVATE DUST2
                 }
                 */
                if (entities[i].type == "Crate") {
                    if (entities[0].x > entities[i].x) {
                        entities[i].direction_x = -1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    if (entities[0].x < entities[i].x) {
                        entities[i].direction_x = 1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    
                }
                entities[0].charge = 0;
                //Shake Screen
                screenShakeValue += elapsed;
                screenShakeIntensity = 10.0;
                screenShakeSpeed = 2.0;
                glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
            }
            if (entities[0].charge >= 10) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == earth) {
                 //ACTIVATE DUST1
                 }
                 if (surface == log) {
                 //ACTIVATE DUST2
                 }
                 */
                if (entities[i].type == "Crate") {
                    if (entities[0].x > entities[i].x) {
                        entities[i].direction_x = -1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    if (entities[0].x < entities[i].x) {
                        entities[i].direction_x = 1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    
                }
                entities[0].charge = 0;
                //Violently Shake Screen
                screenShakeValue += elapsed;
                screenShakeIntensity = 50.0;
                screenShakeSpeed = 4.0;
                glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
            }
            
        }
        
    }
    
}
void ClassDemoApp::UpdateGameLevel2(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                if (entities[0].collidedBottom) {
                    entities[0].velocity_y = 1.0;
                    entities[0].Update(elapsed);
                    entities[0].collidedBottom = false;
                }
                
            }
        }
    }
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i].type == "Player") {
            //            worldToTileCoordinates(entities[i].x, entities[i].y, x, y);
            //Apply Gravity
            if (entities[i].collidedBottom) {
                entities[i].velocity_y = 0.0;
                entities[i].Update(elapsed);
            }
            if (entities[i].collidedTop) {
                entities[i].velocity_y = -1.0;
                entities[i].Update(elapsed);
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                //                if (entities[i].collidedBottom && !entities[i].collidedRight) {
                //                    entities[i].direction_x = 1.0;
                //                    entities[i].Update(elapsed);
                //                }
                entities[i].direction_x = 1.0;
                entities[i].Update(elapsed);
                std::cout << "Direction: " << entities[0].direction_x << std::endl;
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                //                if (entities[i].collidedBottom && !entities[i].collidedLeft) {
                //                    entities[i].direction_x = -1.0;
                //                    entities[i].Update(elapsed);
                //                }
                entities[i].direction_x = -1.0;
                entities[i].Update(elapsed);
                std::cout << "Direction: " << entities[0].direction_x << std::endl;
            }
            if(keys[SDL_SCANCODE_SPACE]) {
//                while (entities[0].charge < 10) {
//                    entities[0].charge += 1;
//                    std::cout << "Counter: " << entities[0].charge << std::endl;
//                }
                entities[0].charge += 1;
                //                entities[0].Update(elapsed);
                if (entities[0].collidedBottom) {
                    //cause tremor
                    //update all entites
                    //                     charge++;
                    //                     entities[0].Update(elapsed);
                }
                std::cout << "Meter: " << entities[0].charge << std::endl;
            }
        }
        if (entityCollision(entities[0], entities[i])) {
            if (entities[i].type == "Goal") {
                //Win State
            }
            if (entities[i].type == "Crate") {
                //Do something
            }
        }
        
        if (entities[0].charge != 0) {
            if (entities[0].charge >= 3) {
                //ADD SMALL SMOKE EFFECT
                if (entities[i].type == "Crate") {
                    entities[i].direction_y = 1.0;
                    entities[i].Update(elapsed);
                }
                entities[0].charge = 0;
            }
            //            if (3 < entities[0].charge <= 6) {
            if (3 < entities[0].charge && entities[0].charge <= 6) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == earth) {
                 //ACTIVATE DUST1
                 }
                 if (surface == log) {
                 //ACTIVATE DUST2
                 }
                 */
                if (entities[i].type == "Crate") {
                    if (entities[0].x > entities[i].x) {
                        entities[i].direction_x = -1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    if (entities[0].x < entities[i].x) {
                        entities[i].direction_x = 1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    
                }
                entities[0].charge = 0;
            }
            //            if (6 < entities[0].charge <= 9) {
            if (6 < entities[0].charge && entities[0].charge <= 9) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == earth) {
                 //ACTIVATE DUST1
                 }
                 if (surface == log) {
                 //ACTIVATE DUST2
                 }
                 */
                if (entities[i].type == "Crate") {
                    if (entities[0].x > entities[i].x) {
                        entities[i].direction_x = -1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    if (entities[0].x < entities[i].x) {
                        entities[i].direction_x = 1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    
                }
                entities[0].charge = 0;
                //Shake Screen
                screenShakeValue += elapsed;
                screenShakeIntensity = 10.0;
                screenShakeSpeed = 2.0;
                glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
            }
            if (entities[0].charge >= 10) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == earth) {
                 //ACTIVATE DUST1
                 }
                 if (surface == log) {
                 //ACTIVATE DUST2
                 }
                 */
                if (entities[i].type == "Crate") {
                    if (entities[0].x > entities[i].x) {
                        entities[i].direction_x = -1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    if (entities[0].x < entities[i].x) {
                        entities[i].direction_x = 1.0;
                        entities[i].direction_y = 1.0;
                        entities[i].Update(elapsed);
                    }
                    
                }
                entities[0].charge = 0;
                //Violently Shake Screen
                screenShakeValue += elapsed;
                screenShakeIntensity = 50.0;
                screenShakeSpeed = 4.0;
                glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
            }
            
        }
        
    }
}
void ClassDemoApp::UpdateGameLevel3(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                if (entities[0].collidedBottom) {
                    entities[0].velocity_y = 1.0;
                    entities[0].Update(elapsed);
                    entities[0].collidedBottom = false;
                }
                
            }
        }
    }
    for (size_t i = 0; i < entities.size(); i++) {
        if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4")) {
            entities[i].rotation -= elapsed*1000;
            entities[i].Update(elapsed);
        }
        if (entities[i].type == "Player") {
            //            worldToTileCoordinates(entities[i].x, entities[i].y, x, y);
            //Apply Gravity
            if (entities[i].collidedBottom) {
                entities[i].velocity_y = 0.0;
                entities[i].Update(elapsed);
            }
            if (entities[i].collidedTop) {
                entities[i].velocity_y = -1.0;
                entities[i].Update(elapsed);
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                //                if (entities[i].collidedBottom && !entities[i].collidedRight) {
                //                    entities[i].direction_x = 1.0;
                //                    entities[i].Update(elapsed);
                //                }
                entities[i].direction_x = 1.0;
                entities[i].Update(elapsed);
                std::cout << "Direction: " << entities[0].direction_x << std::endl;
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                //                if (entities[i].collidedBottom && !entities[i].collidedLeft) {
                //                    entities[i].direction_x = -1.0;
                //                    entities[i].Update(elapsed);
                //                }
                entities[i].direction_x = -1.0;
                entities[i].Update(elapsed);
                std::cout << "Direction: " << entities[0].direction_x << std::endl;
            }
            if(keys[SDL_SCANCODE_SPACE]) {
                entities[0].charge += 1;
                //                entities[0].Update(elapsed);
                if (entities[0].collidedBottom) {
                    //cause tremor
                    //update all entites
                    //                     charge++;
                    //                     entities[0].Update(elapsed);
                }
                std::cout << "Meter: " << entities[0].charge << std::endl;
            }
        }
        if (entityCollision(entities[0], entities[i])) {
            if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4")) {
                //Activate Game Over
            }
            if (entities[i].type == "Goal") {
                //Win State
            }
        }
        
        if (entities[0].charge != 0) {
            if (entities[0].charge >= 3) {
                //ADD SMALL SMOKE EFFECT
                entities[0].charge = 0;
            }
            //            if (3 < entities[0].charge <= 6) {
            if (3 < entities[0].charge && entities[0].charge <= 6) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == pipe || surface == metal) {
                 //ACTIVATE DUST4
                 }
                 */
                if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4")) {
                    entities[i].direction_y = 1.0;
                    entities[i].Update(elapsed);
                }
                entities[0].charge = 0;
            }
            //            if (6 < entities[0].charge <= 9) {
            if (6 < entities[0].charge && entities[0].charge <= 9) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == pipe || surface == metal) {
                 //ACTIVATE DUST4
                 }
                 */
                if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4")) {
                    entities[i].direction_y = 1.0;
                    entities[i].Update(elapsed);
                }
                entities[0].charge = 0;
                //Shake Screen
                screenShakeValue += elapsed;
                screenShakeIntensity = 10.0;
                screenShakeSpeed = 2.0;
                glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
            }
            if (entities[0].charge >= 10) {
                //ADD SMOKE EFFECT
                /*
                 if (surface == pipe || surface == metal) {
                 //ACTIVATE DUST4
                 }
                 */
                if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4")) {
                    entities[i].direction_y = 1.0;
                    entities[i].Update(elapsed);
                }
                entities[0].charge = 0;
                //Violently Shake Screen
                screenShakeValue += elapsed;
                screenShakeIntensity = 50.0;
                screenShakeSpeed = 4.0;
                glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
            }
            
        }
        
    }
    
}



void ClassDemoApp::UpdateGameOver(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        
    }
}

void ClassDemoApp::Render(float elapsed) {
    switch(state) {
        case STATE_MAIN_MENU:
            RenderMainMenu();
            break;
        case STATE_GAME_LEVEL1:
            RenderGameLevel1(elapsed);
            break;
        case STATE_GAME_LEVEL2:
            RenderGameLevel2(elapsed);
            break;
        case STATE_GAME_LEVEL3:
            RenderGameLevel3(elapsed);
            break;
        case STATE_GAME_OVER:
            RenderGameOver(elapsed);
            break;
    }
}
void ClassDemoApp::Update(float elapsed) {
    switch(state) {
        case STATE_MAIN_MENU:
            UpdateMainMenu();
            break;
        case STATE_GAME_LEVEL1:
            UpdateGameLevel1(elapsed);
            break;
        case STATE_GAME_LEVEL2:
            UpdateGameLevel2(elapsed);
            break;
        case STATE_GAME_LEVEL3:
            UpdateGameLevel3(elapsed);
            break;
        case STATE_GAME_OVER:
            UpdateGameOver(elapsed);
            break;
    }
}

bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    
    Update(elapsed);
    Render(elapsed);
    return done;
}

void ClassDemoApp::drawLevel() {
    int textureID = LoadTexture("pixel_sprites_sheet.png");
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    for(int y=0; y < LEVEL_HEIGHT; y++) {
        for(int x=0; x < LEVEL_WIDTH; x++) {
            if(levelData[y][x] != 0) {
                
                //HACK NOTE
                Entity hitBox;
                hitBox.type = "HitBox";
                hitBox.x = TILE_SIZE * x;
                hitBox.y = (-TILE_SIZE * y)-TILE_SIZE;
                hitBox.width = 0.05;
                hitBox.height = 0.05;
                collisionBoxes.push_back(hitBox);
                
                float u = (float)(((int)levelData[y][x]) % SPRITE_COUNT_X) / (float) SPRITE_COUNT_X;
                float v = (float)(((int)levelData[y][x]) / SPRITE_COUNT_X) / (float) SPRITE_COUNT_Y;
                float spriteWidth = 1.0f/(float)SPRITE_COUNT_X;
                float spriteHeight = 1.0f/(float)SPRITE_COUNT_Y;
                vertexData.insert(vertexData.end(), {
                    TILE_SIZE * x, -TILE_SIZE * y,
                    TILE_SIZE * x, (-TILE_SIZE * y)-TILE_SIZE,
                    (TILE_SIZE * x)+TILE_SIZE, (-TILE_SIZE * y)-TILE_SIZE,
                    (TILE_SIZE * x)+TILE_SIZE, -TILE_SIZE * y
                });
                texCoordData.insert(texCoordData.end(), { u, v,
                    u, v+(spriteHeight),
                    u+spriteWidth, v+(spriteHeight),
                    u+spriteWidth, v
                });
                
            }
        }
    }
    
    glLoadIdentity();
    glTranslatef(-TILE_SIZE * LEVEL_WIDTH/2, TILE_SIZE * LEVEL_HEIGHT/2, 0.0f);
    
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, vertexData.size()/2.0);
    glDisable(GL_TEXTURE_2D);
}
void ClassDemoApp::drawTitle() {
    int textureID = LoadTexture("new_pixel_sprites_sheet.png");
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    for(int y=0; y < LEVEL_HEIGHT; y++) {
        for(int x=0; x < LEVEL_WIDTH; x++) {
            if(levelData[y][x] != 0) {
                float u = (float)(((int)levelData[y][x]) % 14) / (float) 14;
                float v = (float)(((int)levelData[y][x]) / 14) / (float) SPRITE_COUNT_Y;
                float spriteWidth = 1.0f/(float)14;
                float spriteHeight = 1.0f/(float)SPRITE_COUNT_Y;
                vertexData.insert(vertexData.end(), {
                    TILE_SIZE * x, -TILE_SIZE * y,
                    TILE_SIZE * x, (-TILE_SIZE * y)-TILE_SIZE,
                    (TILE_SIZE * x)+TILE_SIZE, (-TILE_SIZE * y)-TILE_SIZE,
                    (TILE_SIZE * x)+TILE_SIZE, -TILE_SIZE * y
                });
                texCoordData.insert(texCoordData.end(), { u, v,
                    u, v+(spriteHeight),
                    u+spriteWidth, v+(spriteHeight),
                    u+spriteWidth, v
                });
                
            }
        }
    }
    
    glLoadIdentity();
    glTranslatef(-TILE_SIZE * LEVEL_WIDTH/2, TILE_SIZE * LEVEL_HEIGHT/2, 0.0f);
    
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, vertexData.size()/2.0);
    glDisable(GL_TEXTURE_2D);
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

void worldToTileCoordinates(float worldX, float worldY, int *gridX, int *gridY) {
    *gridX = (int)(worldX / TILE_SIZE);
    *gridY = (int)(-worldY / TILE_SIZE);
}

bool ClassDemoApp::readHeader(std::ifstream &stream) {
    std::string line;
    mapWidth = -1;
    mapHeight = -1;
    while(getline(stream, line)) {
        if(line == "") { break; }
        std::istringstream sStream(line);
        std::string key,value;
        getline(sStream, key, '=');
        getline(sStream, value);
        if(key == "width") {
            mapWidth = atoi(value.c_str());
        } else if(key == "height"){
            mapHeight = atoi(value.c_str());
        }
    }
    if(mapWidth == -1 || mapHeight == -1) {
        return false;
    } else { // allocate our map data
        levelData = new unsigned char*[mapHeight];
        for(int i = 0; i < mapHeight; ++i) {
            levelData[i] = new unsigned char[mapWidth];
        }
        return true;
    }
}

bool ClassDemoApp::readLayerData(std::ifstream &stream) {
    std::string line;
    while(getline(stream, line)) {
        if(line == "") { break; }
        std::istringstream sStream(line);
        std::string key,value;
        std::getline(sStream, key, '=');
        std::getline(sStream, value);
        if(key == "data") {
            for(int y=0; y < mapHeight; y++) {
                std::getline(stream, line);
                std::istringstream lineStream(line);
                std::string tile;
                for(int x=0; x < mapWidth; x++) {
                    std::getline(lineStream, tile, ',');
                    unsigned char val = (unsigned char)atoi(tile.c_str());
                    if(val > 0) {
                        // be careful, the tiles in this format are indexed from 1 not 0
                        levelData[y][x] = val-1;
                    } else {
                        levelData[y][x] = 0;
                    }
                }
            }
        }
    }
    return true;
}

bool ClassDemoApp::readEntityData(std::ifstream &stream) {
    std::string line;
    std::string type;
    while(getline(stream, line)) {
        if(line == "") { break; }
        std::istringstream sStream(line);
        std::string key,value;
        std::getline(sStream, key, '=');
        std::getline(sStream, value);
        if(key == "type") {
            type = value;
        } else if(key == "location") {
            std::istringstream lineStream(value);
            std::string xPosition, yPosition;
            std::getline(lineStream, xPosition, ',');
            std::getline(lineStream, yPosition, ',');
            float placeX = atoi(xPosition.c_str())*TILE_SIZE;
            float placeY = atoi(yPosition.c_str())*-TILE_SIZE;
            
            placeEntity(type, placeX, placeY);
        }
    }
    return true;
}

void ClassDemoApp::readFile(std::string levelFile){
    std::ifstream infile(levelFile);
    std::string line;
    while (getline(infile, line)) {
        if(line == "[header]") {
            if(!readHeader(infile)) {
                return;
            }
        } else if(line == "[layer]") {
            readLayerData(infile);
        } else if(line == "[Player]") {
            readEntityData(infile);
        } else if(line == "[Goal]") {
            readEntityData(infile);
        } else if(line == "[Crate]") {
            readEntityData(infile);
        } else if(line == "[Button]") {
            readEntityData(infile);
        } else if(line == "[Ice]") {
            readEntityData(infile);
        } else if(line == "[Wall1]") {
            readEntityData(infile);
        } else if(line == "[Wall1]") {
            readEntityData(infile);
        } else if(line == "[Wall2]") {
            readEntityData(infile);
        } else if(line == "[Wall3]") {
            readEntityData(infile);
        } else if(line == "[Wall4]") {
            readEntityData(infile);
        } else if(line == "[Saw1]") {
            readEntityData(infile);
        } else if(line == "[Saw2]") {
            readEntityData(infile);
        } else if(line == "[Saw3]") {
            readEntityData(infile);
        } else if(line == "[Saw4]") {
            readEntityData(infile);
        }
    }
    infile.close();
}

void ClassDemoApp::placeEntity(std::string type, float placeX, float placeY) {
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i].type == type) {
            std::cout << entities[i].type << " = " << type << std::endl;
            entities[i].x = placeX;
            entities[i].y = placeY;
            
            entities[i].sprite.x = placeX;
            entities[i].sprite.y = placeY;
        }
        std::cout << "set at " << entities[i].x << "," << entities[i].y << std::endl;
    }
    std::cout << "current: " << entities[0].x << "," << entities[0].y << std::endl;
}



