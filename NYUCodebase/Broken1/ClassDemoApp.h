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
#include <SDL_mixer.h>
#include <vector>
#include "Entity.h"
#include "PerlinNoise.h"


#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 20
#define TILE_SIZE 0.05f
#define SPRITE_COUNT_X 10
#define SPRITE_COUNT_Y 7


GLuint LoadTexture(const char *image_path);
void worldToTileCoordinates(float worldX, float worldY, int *gridX, int *gridY);
void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a);
class MixerSound {
public:
    Uint32 offset;
    Uint32 length;
    Uint8 *buffer;
    float volume;
    SDL_AudioFormat format;
    bool loaded;
    bool playing;
    bool loop;
};
class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void FixedUpdate();
    void Render(float elapsed);
    void Update(float elapsed);
    void drawLevel();
    void drawTitles();
    bool readHeader(std::ifstream &stream);
    bool readLayerData(std::ifstream &stream);
    bool readEntityData(std::ifstream &stream);
    void readFile(std::string levelFile);
    void placeEntity(std::string type, float placeX, float placeY);
    int loadSound(const char *soundFile);
    void appAudioCallback(void *userdata, Uint8 *stream, int len);
    void playSound(int soundIndex, bool loop);
    void RenderMainMenu();
    void RenderGameLevel1(float elapsed);
    void RenderGameLevel2(float elapsed);
    void RenderGameLevel3(float elapsed);
    void RenderGameLevel4(float elapsed);
    void RenderGameLevel5(float elapsed);
    void RenderGameLevel6(float elapsed);
    void RenderGameLevel7(float elapsed);
    void RenderGameOver();
    void UpdateMainMenu();
    void UpdateGameLevel1(float elapsed);
    void UpdateGameLevel2(float elapsed);
    void UpdateGameLevel3(float elapsed);
    void UpdateGameLevel4(float elapsed);
    void UpdateGameLevel5(float elapsed);
    void UpdateGameLevel6(float elapsed);
    void UpdateGameLevel7(float elapsed);
    void UpdateGameOver();
private:
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    std::vector<Entity> entities;
    std::vector<Entity> collisionBoxes;
    std::vector<float> vertexData;
    std::vector<float> texCoordData;
    std::vector<MixerSound> mixSounds;
    float screenShakeValue;
    float screenShakeSpeed;
    float screenShakeIntensity;
    unsigned char **levelData;
    int mapWidth;
    int mapHeight;
    enum GameState { STATE_MAIN_MENU, STATE_GAME_LEVEL1, STATE_GAME_LEVEL2, STATE_GAME_LEVEL3, STATE_GAME_LEVEL4, STATE_GAME_LEVEL5, STATE_GAME_LEVEL6, STATE_GAME_LEVEL7, STATE_GAME_OVER, STATE_TITLE };
    int state;
    Mix_Music *music;
    Mix_Chunk *someSound;
    
};

#endif
