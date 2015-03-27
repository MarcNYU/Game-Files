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

#include "ClassDemoApp copy.h"



ClassDemoApp::ClassDemoApp() {
    Init();
    done = false;
    lastFrameTicks = 0.0f;
}


void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    Entity player(1.0, 1.0, 0.125, 0.125);
    player.scale = 0.9f;
    player.spriteSheetTexture = LoadTexture("game_sprites");
    player.sprite = SheetSprite(player.spriteSheetTexture, 425.0f/1024.0f, 468.0f/1024.0f,
                                  93.0f/1024.0f, 84.0f/1024.0f);
    entities.push_back(player);
    
    
}
ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}
void ClassDemoApp::Render() {
    // render stuff
    SDL_GL_SwapWindow(displayWindow);
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i].Render();
    }
}
void ClassDemoApp::Update(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
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
