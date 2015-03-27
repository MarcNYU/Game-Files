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

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

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
    player.numFrames = 16;
    dynamicEntities.push_back(player);
    
    
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
    for (int i = 0; i < dynamicEntities.size(); i++) {
        dynamicEntities[i].velocity_x = lerp(dynamicEntities[i].velocity_x, 0.0f, FIXED_TIMESTEP * dynamicEntities[i].friction_x);
        dynamicEntities[i].velocity_y = lerp(dynamicEntities[i].velocity_y, 0.0f, FIXED_TIMESTEP * dynamicEntities[i].friction_y);
        dynamicEntities[i].velocity_x += dynamicEntities[i].acceleration_x * FIXED_TIMESTEP;
        dynamicEntities[i].velocity_y += dynamicEntities[i].acceleration_y * FIXED_TIMESTEP;
        dynamicEntities[i].x += dynamicEntities[i].velocity_x * FIXED_TIMESTEP;
        dynamicEntities[i].y += dynamicEntities[i].velocity_y * FIXED_TIMESTEP;

    }
}
void ClassDemoApp::Update(float elapsed) {
    for (int i = 0; i < dynamicEntities.size(); i++) {
//        dynamicEntities[i].velocity_x -= dynamicEntities[i].gravity_x * elapsed;
//        dynamicEntities[i].velocity_y -= dynamicEntities[i].gravity_y * elapsed;
//        
//        dynamicEntities[i].gravity_y = 3.0;
//        dynamicEntities[i].friction_x = 2.0;
    }
    
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {}
    }
    
    // Collison Check
    
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


//
//
//bool readHeader(std::ifstream &stream) {
//    string line;
//    mapWidth = -1;
//    mapHeight = -1;
//    while(getline(stream, line)) {
//        if(line == "") { break; }
//        istringstream sStream(line);
//        string key,value;
//        getline(sStream, key, '=');
//        getline(sStream, value);
//        if(key == "width") {
//            mapWidth = atoi(value.c_str());
//        } else if(key == "height"){
//            mapHeight = atoi(value.c_str());
//        }
//    }
//    if(mapWidth == -1 || mapHeight == -1) {
//        return false;
//    } else { // allocate our map data
//        levelData = new unsigned char*[mapHeight];
//        for(int i = 0; i < mapHeight; ++i) {
//            levelData[i] = new unsigned char[mapWidth];
//        }
//        return true;
//    }
//}
//bool readLayerData(std::ifstream &stream) {
//    string line;
//    while(getline(stream, line)) {
//        if(line == "") { break; }
//        istringstream sStream(line);
//        string key,value;
//        getline(sStream, key, '=');
//        getline(sStream, value);
//        if(key == "data") {
//            for(int y=0; y < mapHeight; y++) {
//                getline(stream, line);
//                istringstream lineStream(line);
//                string tile;
//                for(int x=0; x < mapWidth; x++) {
//                    getline(lineStream, tile, ',');
//                    unsigned char val = (unsigned char)atoi(tile.c_str());
//                    if(val > 0) {
//                        // be careful, the tiles in this format are indexed from 1 not 0
//                        levelData[y][x] = val-1;
//                    } else {
//                        levelData[y][x] = 0;
//                    }
//                }
//            }
//        }
//    }
//    return true;
//}
//bool readEntityData(std::ifstream &stream) {
//    string line;
//    string type;
//    while(getline(stream, line)) {
//        if(line == "") { break; }
//        istringstream sStream(line);
//        string key,value;
//        getline(sStream, key, '=');
//        getline(sStream, value);
//        if(key == "type") {
//            type = value;
//        } else if(key == "location") {
//            istringstream lineStream(value);
//            string xPosition, yPosition;
//            getline(lineStream, xPosition, ',');
//            getline(lineStream, yPosition, ‘,');
//                    float placeX = atoi(xPosition.c_str())/16*TILE_SIZE;
//                    float placeY = atoi(yPosition.c_str())/16*-TILE_SIZE;
//                    placeEntity(type, placeX, placeY);
//                    }
//                    }
//                    return true;
//                    }
