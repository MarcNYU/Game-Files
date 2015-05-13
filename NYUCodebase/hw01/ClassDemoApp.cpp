//
//  ClassDemoApp.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 5/11/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ClassDemoApp.h"
#include "Entity.h"
#include <time.h>
#include <vector>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

float timeLeftOver = 0.0f;
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

ClassDemoApp::ClassDemoApp() {
    InitOpenGL();
    InitRest();
    clock = 0;
    state = 2;
    done = false;
    lastFrameTicks = 0.0f;
    
    screenShakeValue = 0.0f;
    screenShakeValue = 0.0f;
    screenShakeSpeed = 50.0f;
}
ClassDemoApp::~ClassDemoApp() {
    Mix_FreeMusic(maintheme);
    SDL_Quit();
}
void ClassDemoApp::Reset() {
    state = 0;
    clock = 0;
    done = false;
    lastFrameTicks = 0.0f;
    
    delete player;
    delete levelData;
    entities.clear();
    
    InitRest();
}
void ClassDemoApp::InitOpenGL() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
//    glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
    
    texture = LoadTexture("pixel_sprites_sheet.png");
    maintheme = Mix_LoadMUS("video marc.mp3");
    
    //    jump = Mix_LoadWAV("shoot.wav");
    //    smash = Mix_LoadWAV("explode.wav");
}
void ClassDemoApp::InitRest() {
    Mix_PlayMusic(maintheme, -1);
    texture = LoadTexture("pixel_sprites_sheet.png");
    
    text.font = LoadTexture("font1.png");
    text.size = 0.125;
    text.spacing = -0.060;
    text.r = 1.0;
    text.g = 1.0;
    text.b = 1.0;
    text.a = 1.0;
}
void ClassDemoApp::Render(float elapsed) {
    // render stuff
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    switch(state) {
        case STATE_MAIN_MENU:
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            if (clock > 5) {
                text.size = 0.35;
                text.g = 1.0f;
                text.b = 1.0f;
                text.r = 1.0f;
                text.spacing = -0.15f;
                
                text.Draw("Project_Tremor", 0.0f, 0.0f);
                
                text.size = 0.2;
                text.r = 0.5f;
                text.g = 0.0f;
                text.b = 1.0f;
                text.spacing = -0.125;
                text.Draw(">It's kind of ruff!", 0.0f,-0.15f);
                text.Draw(">By: Marcus Williams", 0.0f,-0.75f);
            }
            glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            break;
        case STATE_TITLE:
            drawTitles();
            break;
        case STATE_GAME_LEVEL1:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL2:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL3:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL4:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL5:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL6:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL7:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_LEVEL8:
            glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            for (size_t i = 0; i < entities.size(); i++) {
                entities[i]->Render(elapsed);
            }
            break;
        case STATE_GAME_OVER:
            drawTitles();
            break;
    }
    glPopMatrix();
    SDL_GL_SwapWindow(displayWindow);
}
bool ClassDemoApp::CollisionX(Entity *hitBox) {
    float Bottom = hitBox->y - hitBox->height * TILE_SIZE;
    float Top = hitBox->y + hitBox->height * TILE_SIZE;
    float Left = hitBox->x - hitBox->width * TILE_SIZE * 4;
    float Right = hitBox->x + hitBox->width * TILE_SIZE * 4;
    
    if (hitBox->velocity_x < 0) {
        if ((levelData[worldToTileCoordY(Bottom)][worldToTileCoordX(Left)]) ||
            (levelData[worldToTileCoordY(Top)][worldToTileCoordX(Left)])) {
            hitBox->collidedLeft = true;
            hitBox->x -= FIXED_TIMESTEP * hitBox->velocity_x;
            hitBox->velocity_x = 0.0f;
            hitBox->acceleration_x = 0.0f;
        }
    }
    else if (hitBox->velocity_x > 0) {
        if ((levelData[worldToTileCoordY(Bottom)][worldToTileCoordX(Right)]) ||
            (levelData[worldToTileCoordY(Top)][worldToTileCoordX(Right)])) {
            hitBox->collidedRight = true;
            hitBox->x -= FIXED_TIMESTEP * hitBox->velocity_x;
            hitBox->velocity_x = 0.0f;
            hitBox->acceleration_x = 0.0f;
        }
    }
    else {
        hitBox->collidedLeft = false;
        hitBox->collidedRight = false;
    }
    return (hitBox->collidedLeft || hitBox->collidedRight);
}

bool ClassDemoApp::CollisionY(Entity *hitBox) {
    float Bottom = hitBox->y - hitBox->height * TILE_SIZE * 4;
    float Top = hitBox->y + hitBox->height * TILE_SIZE * 4;
    float Left = hitBox->x - hitBox->width * TILE_SIZE;
    float Right = hitBox->x + hitBox->width * TILE_SIZE;
    
    if (hitBox->velocity_y < 0){
        if ((levelData[worldToTileCoordY(Bottom)][worldToTileCoordX(Right)]) ||
            (levelData[worldToTileCoordY(Bottom)][worldToTileCoordX(Left)])) {
            hitBox->collidedBottom = true;
            hitBox->y -= FIXED_TIMESTEP * hitBox->velocity_y;
            hitBox->velocity_y = 0.0f;
            hitBox->acceleration_y = 0.0f;
        }
    }
    else if (hitBox->velocity_y > 0 && !hitBox->collidedTop){
        if ((levelData[worldToTileCoordY(Top)][worldToTileCoordX(Right)]) ||
            (levelData[worldToTileCoordY(Top)][worldToTileCoordX(Left)])) {
            hitBox->collidedTop = true;
            hitBox->y -= FIXED_TIMESTEP * hitBox->velocity_y;
            hitBox->velocity_y = 0.0f;
            hitBox->acceleration_y = -4.0f;
        }
    }
    else {
        hitBox->collidedTop = false;
        hitBox->collidedBottom = false;
    }
    return (hitBox->collidedTop || hitBox->collidedBottom);
}
void ClassDemoApp::FixedUpdate() {
    screenShakeIntensity = lerp2(screenShakeIntensity, 0.0f, FIXED_TIMESTEP);
    if (screenShakeIntensity < 0.01f)
        screenShakeIntensity = 0.0f;
    if (state == 1||state == 2||state == 3||state == 5||state == 6||state == 7||state == 8) {
        for (size_t i = 0; i < entities.size(); i++) {
            if (entities[i]->type == "Goal") {
                if (player->collidesWith(*entities[i])) {
                    if (state != 8) {
                        BuildLevelData(state+1);
                        state += 1;
                    }
                }
            }
        }
    }
    if (state == 4) {
        player->FixedUpdateY();
        CollisionY(player);
        player->FixedUpdateX();
        CollisionX(player);
        
        for (size_t i = 0; i < entities.size(); i++) {
            if ((entities[i]->type == "Saw1") || (entities[i]->type == "Saw2") || (entities[i]->type == "Saw3") || (entities[i]->type == "Saw4")) {
                if (player->collidesWith(*entities[i])) {
                    BuildLevelData(8);
                    state = 8;
                }
            }
            if (entities[i]->type == "Goal") {
                if (player->collidesWith(*entities[i])) {
                    if (state != 8) {
                        BuildLevelData(state+1);
                        state += 1;
                    }
                }
            }
        }
    }
}
void ClassDemoApp::Update(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                if (player->collidedBottom) {
                    for (size_t i = 0; i < entities.size(); i++) {
                        if (entities[i]->type == "Crate") {
                            if (player->x < entities[i]->x) {
                                entities[0]->direction_x = 1.0;
                                if (!entities[0]->collidedRight)
                                    entities[0]->acceleration_x = 5.0f;
                                entities[0]->movingRight = true;
                                if (entities[0]->collidedRight && entities[0]->velocity_y < 0) {
                                    entities[0]->velocity_y = -0.35f;
                                    entities[0]->acceleration_y = 0.0f;
                                }
                                entities[i]->Jump();
                            } else if (player->x > entities[i]->x) {
                                entities[0]->direction_x = -1.0;
                                if (!entities[0]->collidedLeft)
                                    entities[0]->acceleration_x = -5.0f;
                                entities[0]->movingLeft = true;
                                if (entities[0]->collidedLeft && entities[0]->velocity_y < 0) {
                                    entities[0]->velocity_y = -0.35f;
                                    entities[0]->acceleration_y = 0.0f;
                                }
                                entities[i]->Jump();
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (state == 0) {
        if (keys[SDL_SCANCODE_RETURN]) {state = 1;}
        if (keys[SDL_SCANCODE_ESCAPE]) {done = true;}
    }
    if (state == 1||state == 2||state == 3||state == 4||state == 5||state == 6||state == 7||state == 8) {
        player->Update(elapsed);
        if (keys[SDL_SCANCODE_UP]) {player->Jump();}
        for (size_t i = 0; i < entities.size(); i++) {
            entities[i]->Update(elapsed);
        }
    }
    if (state == 9) {
        if (keys[SDL_SCANCODE_SPACE])
            Reset();
    }
}
bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    screenShakeValue += elapsed;
    
    float fixedElapsed = elapsed + timeLeftOver;
    if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
        fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
    }
    while (fixedElapsed >= FIXED_TIMESTEP) {
        fixedElapsed -= FIXED_TIMESTEP;
        FixedUpdate();
        
        clock++;
    }
    timeLeftOver = fixedElapsed;
    
    Update(elapsed);
    Render(elapsed);
    return done;
}

float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
    float retVal = dstMin + ((value - srcMin) / (srcMax - srcMin) * (dstMax - dstMin));
    if (retVal < dstMin) {
        retVal = dstMin;
    }
    if (retVal > dstMax) {
        retVal = dstMax;
    }
    return retVal;
}

float easeIn(float from, float to, float time) {
    float tVal = time*time*time*time*time;
    return (1.0f - tVal)*from + tVal*to;
}

float easeOut(float from, float to, float time) {
    float oneMinusT = 1.0f - time;
    float tVal = 1.0f - (oneMinusT * oneMinusT * oneMinusT *
                         oneMinusT * oneMinusT);
    return (1.0f - tVal)*from + tVal*to;
}

float easeInOut(float from, float to, float time) {
    float tVal;
    if (time > 0.5) {
        float oneMinusT = 1.0f - ((0.5f - time)*-2.0f);
        tVal = 1.0f - ((oneMinusT * oneMinusT * oneMinusT * oneMinusT *
                        oneMinusT) * 0.5f);
    }
    else {
        time *= 2.0;
        tVal = (time*time*time*time*time) / 2.0;
    }
    return (1.0f - tVal)*from + tVal*to;
}

float easeOutElastic(float from, float to, float time) {
    float p = 0.3f;
    float s = p / 4.0f;
    float diff = (to - from);
    return from + diff + (diff*pow(2.0f, -10.0f*time) * sin((time - s)*(2 * M_PI) / p));
}
float lerp2(float v0, float v1, float t) {
    return (1.0 - t) * v0 + t * v1;
}
int worldToTileCoordX(float x) {
    int i = (int)(x / TILE_SIZE);
    if (i > LEVEL_WIDTH)
        i = LEVEL_WIDTH;
    if (i < 0)
        i = 0;
    return i;
}
int worldToTileCoordY(float y) {
    int j = (int)(-y / TILE_SIZE);
    if (j > LEVEL_HEIGHT)
        j = LEVEL_HEIGHT;
    if (j < 0)
        j = 0;
    return j;
}
bool ClassDemoApp::ReadHeader(std::ifstream &stream) {
    std::string line;
    mapWidth = -1;
    mapHeight = -1;
    while (getline(stream, line)) {
        if (line == "") { break; }
        std::istringstream sStream(line);
        std::string key, value;
        getline(sStream, key, '=');
        getline(sStream, value);
        if (key == "width") {
            mapWidth = atoi(value.c_str());
        } else if (key == "height"){
            mapHeight = atoi(value.c_str());
        }
    }
    if (mapWidth == -1 || mapHeight == -1) {
        return false;
    } else {
        levelData = new unsigned char*[mapHeight];
        for (int i = 0; i < mapHeight; ++i) {
            levelData[i] = new unsigned char[mapWidth];
        }
        return true;
    }
}

bool ClassDemoApp::ReadLayerData(std::ifstream &stream) {
    std::string line;
    while (getline(stream, line)) {
        if (line == "") { break; }
        std::istringstream sStream(line);
        std::string key, value;
        getline(sStream, key, '=');
        getline(sStream, value);
        if (key == "data") {
            for (int y = 0; y < mapHeight; y++) {
                getline(stream, line);
                std::istringstream lineStream(line);
                std::string tile;
                
                for (int x = 0; x < mapWidth; x++) {
                    getline(lineStream, tile, ',');
                    unsigned char val = (unsigned char)atoi(tile.c_str());
                    if (val > 0) {
                        // be careful, the tiles in this format are indexed from 1 not 0
                        levelData[y][x] = val-1;
                    }
                    else {
                        levelData[y][x] = 0;
                    }
                }
            }
        }
    }
    return true;
}

void ClassDemoApp::PlaceEntity(std::string type, float placeX, float placeY) {
    if (type == "Player") {
        player = new Entity();
        player->type = type;
        player->x = placeX;
        player->y = placeY;
        player->width = TILE_SIZE;
        player->height = TILE_SIZE;
    }
    if ((type == "Saw1") || (type == "Saw2") || (type == "Saw3") || (type == "Saw4")) {
        Entity *saw = new Entity();
        saw->type = type;
        saw->x = placeX + TILE_SIZE / 2;
        saw->y = placeY;
        saw->width = 0.07;
        saw->height = 0.07;
        entities.push_back(saw);
    }
    if ((type == "Wall1") || (type == "Wall2") || (type == "Wall3") || (type == "Wall4") || (type == "Wall4")) {
        Entity *wall = new Entity();
        wall->type = type;
        wall->x = placeX + TILE_SIZE / 2;
        wall->y = placeY;
        wall->width = TILE_SIZE;
        wall->height = TILE_SIZE;
        entities.push_back(wall);
    }
    if (type == "Goal") {
        Entity *waffel = new Entity();
        waffel->type = type;
        waffel->x = placeX + TILE_SIZE / 2;
        waffel->y = placeY;
        waffel->width = TILE_SIZE;
        waffel->height = TILE_SIZE;
    }
    if (type == "Button") {
        Entity *button = new Entity();
        button->type = type;
        button->x = placeX + TILE_SIZE / 2;
        button->y = placeY;
        button->width = TILE_SIZE;
        button->height = TILE_SIZE;
    }
}

bool ClassDemoApp::ReadEntityData(std::ifstream &stream) {
    std::string line;
    std::string type;
    
    while (getline(stream, line)) {
        if (line == "") { break; }
        std::istringstream sStream(line);
        std::string key, value;
        getline(sStream, key, '=');
        getline(sStream, value);
        if (key == "type") {
            type = value;
        }
        else if (key == "location") {
            
            std::istringstream lineStream(value);
            std::string xPosition, yPosition;
            getline(lineStream, xPosition, ',');
            getline(lineStream, yPosition, ',');
            
            float placeX = atoi(xPosition.c_str())* TILE_SIZE;
            float placeY = atoi(yPosition.c_str())* -TILE_SIZE;
            
            PlaceEntity(type, placeX, placeY);
        }
    }
    return true;
}

void ClassDemoApp::BuildLevelData(int level) {
    if (level == 9) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/tremor.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 1) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/level1_new.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 2) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/level2_new.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 3) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/level4_new.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 4) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/new_level5.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 5) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/new_level6txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 6) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/new_level7.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 7) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/new_level8.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
    if (level == 8) {
        std::ifstream stream("NYUCodebase.app/Contents/Resources/game_over.txt");
        std::string line;
        while (getline(stream, line)) {
            if (line == "[header]") {
                if (!ReadHeader(stream)) {
                    return;
                }
            }
            else if (line == "[layer]") {
                ReadLayerData(stream);
            }
            else if (line == "[ObjectsLayer]") {
                ReadEntityData(stream);
            }
        }
    }
}

void ClassDemoApp::drawLevel() {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    for(int y=0; y < LEVEL_HEIGHT; y++) {
        for(int x=0; x < LEVEL_WIDTH; x++) {
            if(levelData[y][x] != 0) {
                
                //                //HACK NOTE
                //                Entity hitBox;
                //                hitBox.type = "HitBox";
                //                hitBox.x = TILE_SIZE * x;
                //                hitBox.y = (-TILE_SIZE * y)-TILE_SIZE;
                //                hitBox.width = 0.05;
                //                hitBox.height = 0.05;
                //                collisionBoxes.push_back(hitBox);
                
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
void ClassDemoApp::drawTitles() {
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