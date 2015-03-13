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

// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6


#define MAX_BULLETS 30


class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void shootBullet();
    void Render(float elapsed);
    void Update(float elapsed);
    void FixedUpdate();
private:
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    std::vector<Entity> staticEntities;
    std::vector<Entity> dynamicEntities;
    int bulletIndex = 0;
    Bullet bullets[MAX_BULLETS];
    float timeLeftOver = 0.0f;
    float penetration;
};

float lerp(float v0, float v1, float t);

#endif
