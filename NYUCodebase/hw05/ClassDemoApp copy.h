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
#include "Entity copy.h"




#define MAX_BULLETS 30

GLuint LoadTexture(const char *image_path);

class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void shootBullet();
    void Render();
    void Update(float elapsed);
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
};



#endif
