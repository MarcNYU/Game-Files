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
ClassDemoApp::~ClassDemoApp() {
    SDL_Quit();
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    readFile("NYUCodebase.app/Contents/Resources/level_map.txt");
    
    Entity player(0.0, 0.0, 0.104, 0.22);
    player.name = "player";
    player.scale = 0.7f;
    player.spriteSheetTexture = LoadTexture("volt.png");
    player.sprite = SheetSprite(player.spriteSheetTexture, 425.0f/1024.0f, 468.0f/1024.0f,
                                  93.0f/1024.0f, 84.0f/1024.0f);
    entities.push_back(player);
    Entity robot(0.0, 0.0, 0.103, 0.22);
    robot.name = "robot";
    robot.scale = 0.7f;
    robot.spriteSheetTexture = LoadTexture("robot.png");
    robot.sprite = SheetSprite(robot.spriteSheetTexture, 425.0f/1024.0f, 468.0f/1024.0f,
                                93.0f/1024.0f, 84.0f/1024.0f);
    entities.push_back(robot);
    Entity tiger(0.0, 0.0, 0.103, 0.22);
    tiger.name = "tiger";
    tiger.scale = 0.7f;
    tiger.spriteSheetTexture = LoadTexture("tiger.png");
    tiger.sprite = SheetSprite(tiger.spriteSheetTexture, 425.0f/1024.0f, 468.0f/1024.0f,
                               93.0f/1024.0f, 84.0f/1024.0f);
    entities.push_back(tiger);
    
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(entities[0].y, entities[0].x, 0.0f);
    buildLevel();
    glPopMatrix();
    
}

void ClassDemoApp::Render(float elapsed) {
    // render stuff
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        entities[i].Render(elapsed);
    }
    for (size_t i = 0; i < texCoordData.size(); i++) {
        texCoordData[i];
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
//    Render(elapsed);
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
void ClassDemoApp::buildLevel() {
    glLoadIdentity();
    glTranslatef(-TILE_SIZE * LEVEL_WIDTH/2, TILE_SIZE * LEVEL_HEIGHT/2, 0.0f);
    
    for(int y=0; y < LEVEL_HEIGHT; y++) {
        for(int x=0; x < LEVEL_WIDTH; x++) {
            if(levelData[y][x] != 0) {
                // add vertices
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
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, vertexData.size()/2);
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
    *gridX = (int)((worldX + (WORLD_OFFSET_X)) / TILE_SIZE);
    *gridY = (int)((-worldY + (WORLD_OFFSET_Y)) / TILE_SIZE);
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
            float placeX = atoi(xPosition.c_str())/16*TILE_SIZE;
            float placeY = atoi(yPosition.c_str())/16*-TILE_SIZE;
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
        } else if(line == "[Enemy]") {
            readEntityData(infile);
        }
    }
}

void ClassDemoApp::placeEntity(std::string type, float placeX, float placeY) {
    /*
    if (type == "Player") {
        entities[0].x = placeX;
        entities[0].y = placeY;
    } else
        for (int i = 1; i < entities.size(); i++) {
            entities[i].x = placeX;
            entities[i].y = placeY;
    }
     */
}

