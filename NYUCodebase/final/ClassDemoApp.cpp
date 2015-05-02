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
//    glOrtho(-0.38, 0.38, -0.4, 0.4, -0.4, 0.4);
    
    
    Entity player;
    player.type = "Player";
//    player.scale = 0.25;
    player.width = 0.0625;
    player.height = 0.0625;
    player.spriteSheetTexture = LoadTexture("8-bit.png");
    std::cout << "current textID: " << player.sprite.textureID << std::endl;
    std::cout << "initial: " << player.x << "," << player.y << std::endl;

    Entity goal;
    goal.type = "Goal";
//    goal.scale = 0.25;
    goal.width = 0.0625;
    goal.height = 0.0625;
    
    Entity crate;
    crate.type = "Crate";
//    crate.scale = 0.25;
    crate.width = 0.0625;
    crate.height = 0.0625;

    entities.push_back(player);
    entities.push_back(goal);
    entities.push_back(crate);
    
    readFile("NYUCodebase.app/Contents/Resources/level1.txt");
    //    readFile("NYUCodebase.app/Contents/Resources/level2.txt");
    //    readFile("NYUCodebase.app/Contents/Resources/level3.txt");
    
    
}

void ClassDemoApp::Render() {
    // render stuff
    
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render();
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::Update(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                if (entities[0].collidedBottom) {
                    //cause tremor
                    //update all entites
                }
            }
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                if (entities[0].collidedBottom) {
                    entities[0].direction_y = 1.0;
                }
            }
        }
    }
    
    for (Entity target : entities) {
        if (target.type == "Player") {
            if (!target.collidedBottom) {
                target.direction_y = -1.0;
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                if (target.collidedBottom && !target.collidedRight) {
                    target.direction_x = 1.0;
                }
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                if (target.collidedBottom && !target.collidedLeft) {
                    target.direction_x = -1.0;
                }
            }
        }
        if (target.type == "Crate") {
            if (!target.collidedBottom) {
                target.direction_y = -1.0;
            }
        }
//        target.Update(elapsed);
    }
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i].Update(elapsed);
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

void ClassDemoApp::drawLevel() {
    int textureID = LoadTexture("tremor_sprite_sheet.png");
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    std::vector<float> vertexData;
    std::vector<float>  texCoordData;
    
    for(int y=0; y < LEVEL_HEIGHT; y++) {
        for(int x=0; x < LEVEL_WIDTH; x++) {
            if(levelData[y][x] != 0) {
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
//            float placeX = atoi(xPosition.c_str())*TILE_SIZE;
//            float placeY = atoi(yPosition.c_str())*-TILE_SIZE;
            
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
        }
    }
}

void ClassDemoApp::placeEntity(std::string type, float placeX, float placeY) {
//    for (Entity target : entities) {
//        if (target.type == type) {
//            std::cout << target.type << " = " << type << std::endl;
//            target.x = placeX;
//            target.y = placeY;
//        }
//        std::cout << "set at " << target.x << "," << target.y << std::endl;
//    }
//    std::cout << "current: " << entities[0].x << "," << entities[0].y << std::endl;
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

