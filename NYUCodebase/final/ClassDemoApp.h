//
//  ClassDemoApp.h
//  NYUCodebase
//
//  Created by Marcus Williams on 4/14/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_ClassDemoApp_h
#define NYUCodebase_ClassDemoApp_h

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include "Entity.h"


#define LEVEL_WIDTH 15
#define LEVEL_HEIGHT 15
#define TILE_SIZE 0.05f
#define SPRITE_COUNT_X 10
#define SPRITE_COUNT_Y 7
#define WORLD_OFFSET_X 1
#define WORLD_OFFSET_Y 1

GLuint LoadTexture(const char *image_path);
void worldToTileCoordinates(float worldX, float worldY, int *gridX, int *gridY);

class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void Render();
    void Update(float elapsed);
    void drawLevel();
    bool readHeader(std::ifstream &stream);
    bool readLayerData(std::ifstream &stream);
    bool readEntityData(std::ifstream &stream);
    void readFile(std::string levelFile);
    void placeEntity(std::string type, float placeX, float placeY);
private:
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    std::vector<Entity> entities;
    float penetration;
    unsigned char **levelData;
    int mapWidth;
    int mapHeight;
    
    
};

float lerp(float v0, float v1, float t);

#endif
