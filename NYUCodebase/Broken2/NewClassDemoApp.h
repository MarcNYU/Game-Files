//
//  ClassDemoApp.h
//  NYUCodebase
//
//  Created by Marcus Williams on 5/10/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef __NYUCodebase__ClassDemoApp__
#define __NYUCodebase__ClassDemoApp__

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include "NewEntity.h"
#include "TextFile.h"


#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 20
#define TILE_SIZE 0.05f
#define SPRITE_COUNT_X 10
#define SPRITE_COUNT_Y 7

class ClassDemoApp {
public:
    
    ClassDemoApp();
    ~ClassDemoApp();
    
    void BuildLevelData(int level);
    bool ReadHeader(std::ifstream &stream);
    bool ReadLayerData(std::ifstream &stream);
    bool ReadEntityData(std::ifstream &stream);
    void drawLevel();
    void drawTitles();
    void drawTitle();
    void PlaceEntity(std::string type, float placeX, float placeY);
    
    void InitOpenGL();
    void InitRest();
    bool UpdateAndRender();
    
    bool CollisionX(Entity* hitBox);
    bool CollisionY(Entity* hitBox);
    void FixedUpdate();
    
    void Render(float elapsed);
    void Update(float elapsed);
    
    void Reset();
    
private:
    Entity* player;
    std::vector<Entity*> entities;
    
    float screenShakeValue;
    float screenShakeSpeed;
    float screenShakeIntensity;
    
    float textAnimationValue;
    
    float animationAValue;
    float animationBValue;
    float animationCValue;
    
    Text text;
    int itemLoc;
    int clock;
    
    int mapHeight;
    int mapWidth;
    unsigned char** levelData;
    GLuint texture;
    
    float title;
    std::vector<float> vertexData;
    std::vector<float> texCoordData;
    
    enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL1, STATE_GAME_LEVEL2, STATE_GAME_LEVEL3, STATE_GAME_LEVEL4, STATE_GAME_LEVEL5,STATE_GAME_LEVEL6, STATE_GAME_LEVEL7, STATE_GAME_LEVEL8, STATE_GAME_OVER, STATE_TITLE };
    int state;
    bool done;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float lastFrameTicks;
    SDL_Window* displayWindow;
    SDL_Event event;
    
    Mix_Music* maintheme;
    
    Mix_Chunk* jump;
    Mix_Chunk* smash;
};

//GLuint LoadTexture(const char *image_path);
int worldToTileCoordX(float x);
int worldToTileCoordY(float y);
float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax);
float easeIn(float from, float to, float time);
float easeOut(float from, float to, float time);
float easeInOut(float from, float to, float time);
float easeOutElastic(float from, float to, float time);
float lerp2(float v0, float v1, float t);

#endif /* defined(__NYUCodebase__ClassDemoApp__) */
