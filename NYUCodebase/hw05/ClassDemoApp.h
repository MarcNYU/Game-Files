//
//  ClassDemoApp.h
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_ClassDemoApp_h
#define NYUCodebase_ClassDemoApp_h

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include "Entity.h"




#define MAX_BULLETS 30
#define LEVEL_WIDTH 128
#define LEVEL_HEIGHT 32
#define TILE_SIZE 16
#define SPRITE_COUNT_X 50
#define SPRITE_COUNT_Y 33
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
    void shootBullet();
    void Render(float elapsed);
    void Update(float elapsed);
    void buildLevel();
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
    int bulletIndex = 0;
    Bullet bullets[MAX_BULLETS];
    float penetration;
    unsigned char **levelData;
    int mapWidth;
    int mapHeight;
    std::vector<int> vertexData;
    std::vector<float>  texCoordData;
    
};



#endif
