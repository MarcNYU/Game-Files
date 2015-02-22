//
//  ClassDemoApp.h
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_ClassDemoApp_h
#define NYUCodebase_ClassDemoApp_h

class ClassDemoApp {
public:
    ClassDemoApp();
    ~ClassDemoApp();
    void Init();
    bool UpdateAndRender();
    void shootBullet();
    void Render();
private:
    bool done;
    float lastFrameTicks;
    SDL_Window* displayWindow;
    int bulletIndex = 0;
    Bullet bullets[MAX_BULLETS];
};


#endif
