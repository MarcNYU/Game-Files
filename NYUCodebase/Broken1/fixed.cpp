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
#include <SDL_mixer.h>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>


#include "ClassDemoApp.h"



ClassDemoApp::ClassDemoApp() {
    Init();
    done = false;
    lastFrameTicks = 0.0f;
}
ClassDemoApp::~ClassDemoApp() {
//    Mix_FreeChunk(someSound);
//    Mix_FreeMusic(music);
    SDL_Quit();
}

void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    //    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glOrtho(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5);
    
    
    int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 );
    
//    SDL_AudioSpec deviceSpec;
//    deviceSpec.freq = 44100; // sampling rate (samples a second)
//    deviceSpec.format = AUDIO_F32; // audio format
//    deviceSpec.channels = 1; // how many channels (1 = mono, 2 = stereo)
//    deviceSpec.samples = 512; // audio buffer size in samples (power of 2)
////    deviceSpec.callback = appAudioCallback(); // our callback function
//    // open new audio device with our requested settings
//    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &deviceSpec, 0,
//                                                SDL_AUDIO_ALLOW_FORMAT_CHANGE);
//    SDL_PauseAudioDevice(dev, 0); // start playback on this device
//    //    someSound = Mix_LoadWAV("some_sound.wav");
//    
    music = Mix_LoadMUS("video marc.mp3");
    
    Entity player;
    player.numFrames = 4;
    player.framesPerSecond = 3.0;
    player.type = "Player";
    player.width = 0.05;
    player.height = 0.05;
    player.friction_x = 10.0;
    player.gravity_y = -1.0;
//    std::cout << "initial: " << player.x << "," << player.y << std::endl;
    
    Entity goal;
    goal.type = "Goal";
    goal.width = 0.05;
    goal.height = 0.05;
    
    Entity crate;
    crate.type = "Crate";
    crate.width = 0.05;
    crate.height = 0.05;
    
    Entity button;
    button.type = "Button";
    button.width = 0.05;
    button.height = 0.05;
    
    //    Entity ice;
    //    ice.width = 0.05;
    //    ice.height = 0.05;
    
    Entity wall1;
    wall1.type = "Wall1";
    wall1.width = 0.05;
    wall1.height = 0.05;
    
    Entity wall2;
    wall2.type = "Wall2";
    wall2.width = 0.05;
    wall2.height = 0.05;
    
    Entity saw1;
    saw1.type = "Saw1";
    saw1.width = 0.07;
    saw1.height = 0.07;
    
    Entity saw2;
    saw2.type = "Saw2";
    saw2.width = 0.07;
    saw2.height = 0.07;
    
    Entity saw3;
    saw3.type = "Saw3";
    saw3.width = 0.07;
    saw3.height = 0.07;
    
    Entity saw4;
    saw4.type = "Saw4";
    saw4.width = 0.07;
    saw4.height = 0.07;
    
    entities.push_back(player);
    entities.push_back(goal);
    entities.push_back(crate);
    entities.push_back(button);
    entities.push_back(wall1);
    entities.push_back(wall2);
    entities.push_back(saw1);
    entities.push_back(saw2);
    entities.push_back(saw3);
    entities.push_back(saw4);
    //    int num = 0;
    //    while (num < 42) {
    //        std::string str = std::to_string(num+1);
    //        ice.type = "Ice"+str;
    //        entities.push_back(ice);
    //        num++;
    //    }
//    for (int i = 0; i < entities.size(); i++) {
//        std::cout << entities[i].type << std::endl;
//    }
    
    state = 3;
    //1 Demo
    //2 Demo
    //3 Demo
    //4
    //5 Broken
    //6 Broken
    //7 Demo
    //8 Game Over
    switch (state) {
        case 0:
            Mix_PlayMusic(music, -1);
            
            readFile("NYUCodebase.app/Contents/Resources/tremor.txt");
            break;
        case 1:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/level1_new.txt");
            break;
        case 2:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/level2_new.txt");
            break;
        case 3:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/level4_new.txt");
            break;
        case 4:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/new_level5.txt");
            break;
        case 5:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/new_level6txt");
            break;
//        case 6:
//            readFile("NYUCodebase.app/Contents/Resources/new_level7.txt");
//            break;
        case 7:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/new_level8.txt");
            break;
        case 8:
            Mix_PlayMusic(music, -1);
            readFile("NYUCodebase.app/Contents/Resources/game_over.txt");
            break;
            
    }
    
    //    readFile("NYUCodebase.app/Contents/Resources/level3_new.txt");
    
}


bool entityCollision(Entity sprite_1, Entity sprite_2){
    //If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
    if( (sprite_1.x >= sprite_2.x && sprite_1.x <= (sprite_2.x + sprite_2.width)) ||
       ((sprite_1.x + sprite_1.width) >= sprite_2.x && (sprite_1.x + sprite_1.width) <= (sprite_2.x + sprite_2.width)) ){
        //Now we look at the y axis:
        if( (sprite_1.y >= sprite_2.y && sprite_1.y <= (sprite_2.y + sprite_2.height)) ||
           ((sprite_1.y + sprite_1.height) >= sprite_2.y && (sprite_1.y + sprite_1.height) <= (sprite_2.y + sprite_2.height)) ){
            //The sprites appear to overlap.
            return true;
        }
    }
    //The sprites do not overlap:
    return false;
}


void ClassDemoApp::RenderMainMenu() {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    drawTitles();
    glPopMatrix();
    
}
void ClassDemoApp::RenderGameLevel1(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameLevel2(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameLevel3(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameLevel4(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameLevel5(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
//void ClassDemoApp::RenderGameLevel6(float elapsed) {
//    SDL_GL_SwapWindow(displayWindow);
//    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    
//    glClear(GL_COLOR_BUFFER_BIT);
//    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
//        entities[i].Render(elapsed);
//    }
//    for (size_t j = 0; j < collisionBoxes.size(); j++) {
//        collisionBoxes[j].Render(elapsed);
//    }
//    
//    glPushMatrix();
//    drawLevel();
//    glPopMatrix();
//}
void ClassDemoApp::RenderGameLevel7(float elapsed) {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    for (size_t i = 0; i < entities.size(); i++) {
//        std::cout << "rendering at " << entities[i].x << "," << entities[i].y << std::endl;
        entities[i].Render(elapsed);
    }
    for (size_t j = 0; j < collisionBoxes.size(); j++) {
        collisionBoxes[j].Render(elapsed);
    }
    
    glPushMatrix();
    drawLevel();
    glPopMatrix();
}
void ClassDemoApp::RenderGameOver() {
    SDL_GL_SwapWindow(displayWindow);
    glClearColor(0.33f, 0.33f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    drawTitles();
    glPopMatrix();
}
void ClassDemoApp::UpdateMainMenu() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                state = 5;
            }
        }
    }
}
void ClassDemoApp::UpdateGameLevel1(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
//        if(event.type == SDL_KEYDOWN) {
//            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
//                if (entities[0].collidedBottom) {
//                    entities[0].direction_y = 1.0;
//                    entities[0].y += .01;
//                    entities[0].Update(elapsed);
//                    entities[0].collidedBottom = false;
//                }
//                
//            }
//        }
    }
    
    if (keys[SDL_SCANCODE_LEFT]) {
        entities[0].direction_x = -1.0;
        entities[0].acceleration_x = -1.0;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0].direction_x = 1.0;
        entities[0].acceleration_x = 1.0;
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (entities[0].collidedBottom) {
            //            entities[0].direction_y = 1.0;
            entities[0].y += .12;
            entities[0].Update(elapsed);
            entities[0].collidedBottom = false;
        }
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //Effect Environment
        //Shake Screen
        screenShakeValue += elapsed;
        screenShakeIntensity = 0.02;
        screenShakeSpeed = 20.0;
    }
    entities[0].Update(elapsed);
    for (size_t i=0; i < entities.size(); i++) {
        for (size_t j=0; j < collisionBoxes.size(); j++) {
            if (entities[i].type == "Player") {
                if (entities[i].collidesWith(collisionBoxes[j])) {
                    //                    std::cout << "Does it enter the test?" << std::endl;
                    //Vertical Collisions
                    if (entities[i].collidedBottom) {
                        //                        std::cout << "Bottom" << std::endl;
                        //                        std::cout << "Befor: "<< entities[i].penetration << std::endl;
                        entities[0].velocity_y = 0.0;
                        entities[i].y -= entities[i].penetration/100000000000;
                        //                        std::cout << "After: "<< entities[i].penetration/55000 << std::endl;
                    } else if (entities[i].collidedTop) {
                        //                        std::cout << "Top" << std::endl;
                        //                        entities[i].y -= entities[i].penetration;
                    }
                    //Hroizontal Collisions
                    if (entities[i].collidedLeft || entities[i].x < -0.002) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Left" << std::endl;
                        //                        entities[i].x += entities[i].penetration;
                        //                        entities[0].acceleration_x = 1.0;
                    } else if (entities[i].collidedRight || entities[i].x > 0.95) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Right" << std::endl;
                        //                        entities[i].x -= entities[i].penetration;
                        //                        entities[0].acceleration_x = -1.0;
                    }
                }
            }
        }
    }
    for (size_t i=0; i < entities.size(); i++) {
        if (entities[i].type != "Player")
        {
            if (entities[0].collidesWith(entities[i])){
                if (entities[i].type == "Goal")
                {
//                    entities[i].width = 0.0;
//                    entities[i].height = 0.0;
                }
            }
        }
    }
}
void ClassDemoApp::UpdateGameLevel2(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
//        if(event.type == SDL_KEYDOWN) {
//            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
//                if (entities[0].collidedBottom) {
//                    entities[0].direction_y = 1.0;
//                    entities[0].Update(elapsed);
//                    entities[0].collidedBottom = false;
//                }
//                
//            }
//        }
    }
    
    if (keys[SDL_SCANCODE_LEFT]) {
        entities[0].direction_x = -1.0;
        entities[0].acceleration_x = -1.0;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0].direction_x = 1.0;
        entities[0].acceleration_x = 1.0;
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (entities[0].collidedBottom) {
            //            entities[0].direction_y = 1.0;
            entities[0].y += .12;
            entities[0].Update(elapsed);
            entities[0].collidedBottom = false;
        }
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //Effect Environment
        //Shake Screen
        screenShakeValue += elapsed;
        screenShakeIntensity = 0.02;
        screenShakeSpeed = 20.0;
    }
    entities[0].Update(elapsed);
    for (size_t i=0; i < entities.size(); i++) {
        for (size_t j=0; j < collisionBoxes.size(); j++) {
            if (entities[i].type == "Player") {
                if (entities[i].collidesWith(collisionBoxes[j])) {
                    //                    std::cout << "Does it enter the test?" << std::endl;
                    //Vertical Collisions
                    if (entities[i].collidedBottom) {
//                        std::cout << "Bottom" << std::endl;
//                        std::cout << "Befor: "<< entities[i].penetration << std::endl;
                        entities[0].velocity_y = 0.0;
                        entities[i].y -= entities[i].penetration/100000000000;
//                        std::cout << "After: "<< entities[i].penetration/55000 << std::endl;
                    } else if (entities[i].collidedTop) {
                        //                        std::cout << "Top" << std::endl;
                        //                        entities[i].y -= entities[i].penetration;
                    }
                    //Hroizontal Collisions
                    if (entities[i].collidedLeft || entities[i].x < -0.002) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Left" << std::endl;
                        //                        entities[i].x += entities[i].penetration;
                        //                        entities[0].acceleration_x = 1.0;
                    } else if (entities[i].collidedRight || entities[i].x > 0.95) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Right" << std::endl;
                        //                        entities[i].x -= entities[i].penetration;
                        //                        entities[0].acceleration_x = -1.0;
                    }
                }
            }
        }
    }
    for (size_t i=0; i < entities.size(); i++) {
        if (entities[i].type != "Player")
        {
            if (entities[0].collidesWith(entities[i])){
                if (entities[i].type == "Goal")
                {
//                    entities[i].width = 0.0;
//                    entities[i].height = 0.0;
                }
            }
        }
    }
}
void ClassDemoApp::UpdateGameLevel3(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
//        if(event.type == SDL_KEYDOWN) {
//            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
//                if (entities[0].collidedBottom) {
//                    entities[0].direction_y = 1.0;
//                    entities[0].Update(elapsed);
//                    entities[0].collidedBottom = false;
//                }
//                
//            }
//        }
    }
    
    if (keys[SDL_SCANCODE_LEFT]) {
        entities[0].direction_x = -1.0;
        entities[0].acceleration_x = -1.0;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0].direction_x = 1.0;
        entities[0].acceleration_x = 1.0;
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (entities[0].collidedBottom) {
            //            entities[0].direction_y = 1.0;
//            if (entities[0].direction_x > 0.0) {
//                entities[0].y += .15;
//                entities[0].acceleration_x = 1.0;
//            }
            entities[0].y += .12;
            entities[0].Update(elapsed);
            entities[0].collidedBottom = false;
        }
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //Effect Environment
        //Shake Screen
        screenShakeValue += elapsed;
        screenShakeIntensity = 0.02;
        screenShakeSpeed = 20.0;
    }
    entities[0].Update(elapsed);
    for (size_t i=0; i < entities.size(); i++) {
        for (size_t j=0; j < collisionBoxes.size(); j++) {
            if (entities[i].type == "Player") {
                if (entities[i].collidesWith(collisionBoxes[j])) {
                    //                    std::cout << "Does it enter the test?" << std::endl;
                    //Vertical Collisions
                    if (entities[i].collidedBottom) {
                        entities[0].velocity_y = 0.0;
                        entities[i].y -= entities[i].penetration/100000000000;
                        //                        std::cout << "Bottom" << std::endl;
                        //                        std::cout << "Befor: "<< entities[i].penetration << std::endl;
                        entities[0].velocity_y = 0.0;
                        //                        entities[i].y -= entities[i].penetration*0.05;
                        //                        std::cout << "After: "<< entities[i].penetration/55000 << std::endl;
                    } else if (entities[i].collidedTop) {
                        //                        std::cout << "Top" << std::endl;
                        //                        entities[i].y -= entities[i].penetration;
                    }
                    //Hroizontal Collisions
                    if (entities[i].collidedLeft || entities[i].x < -0.002) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Left" << std::endl;
                        //                        entities[i].x += entities[i].penetration;
                        //                        entities[0].acceleration_x = 1.0;
                    } else if (entities[i].collidedRight || entities[i].x > 0.95) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Right" << std::endl;
                        //                        entities[i].x -= entities[i].penetration;
                        //                        entities[0].acceleration_x = -1.0;
                    }
                }
            }
            
        }
    }
    for (size_t i=0; i < entities.size(); i++) {
        if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4"))
        {
            entities[i].rotation -= elapsed*1000;
            entities[i].Update(elapsed);
        }
        if (entities[i].type != "Player")
        {
            if (entities[0].collidesWith(entities[i])){
                if ((entities[i].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[i].type == "Saw4"))
                {
                    //GAME OVER
                }
                if (entities[i].type == "Goal")
                {
//                    entities[i].width = 0.0;
//                    entities[i].height = 0.0;
                }
            }
        }
    }

}
void ClassDemoApp::UpdateGameLevel4(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
//        if(event.type == SDL_KEYDOWN) {
//            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
//                if (entities[0].collidedBottom) {
//                    entities[0].direction_y = 1.0;
//                    entities[0].Update(elapsed);
//                    entities[0].collidedBottom = false;
//                }
//                
//            }
//        }
    }
    
    if (keys[SDL_SCANCODE_LEFT]) {
        entities[0].direction_x = -1.0;
        entities[0].acceleration_x = -1.0;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0].direction_x = 1.0;
        entities[0].acceleration_x = 1.0;
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (entities[0].collidedBottom) {
            //            entities[0].direction_y = 1.0;
            entities[0].y += .15;
            entities[0].Update(elapsed);
            entities[0].collidedBottom = false;
        }
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //Effect Environment
        //Shake Screen
        screenShakeValue += elapsed;
        screenShakeIntensity = 0.02;
        screenShakeSpeed = 20.0;
    }
    entities[0].Update(elapsed);
    for (size_t i=0; i < entities.size(); i++) {
        for (size_t j=0; j < collisionBoxes.size(); j++) {
            if (entities[i].type == "Player") {
                if (entities[i].collidesWith(collisionBoxes[j])) {
                    //                    std::cout << "Does it enter the test?" << std::endl;
                    //Vertical Collisions
                    if (entities[i].collidedBottom) {
                        entities[0].velocity_y = 0.0;
                        entities[i].y -= entities[i].penetration/100000000000;
                        //                        std::cout << "Bottom" << std::endl;
                        //                        std::cout << "Befor: "<< entities[i].penetration << std::endl;
                        entities[0].velocity_y = 0.0;
                        //                        entities[i].y -= entities[i].penetration*0.05;
                        //                        std::cout << "After: "<< entities[i].penetration/55000 << std::endl;
                    } else if (entities[i].collidedTop) {
                        //                        std::cout << "Top" << std::endl;
                        //                        entities[i].y -= entities[i].penetration;
                    }
                    //Hroizontal Collisions
                    if (entities[i].collidedLeft || entities[i].x < -0.002) {
                        //                        std::cout << "Left" << std::endl;
                        //                        entities[i].x += entities[i].penetration;
                        //                        entities[0].acceleration_x = 1.0;
                    } else if (entities[i].collidedRight || entities[i].x > 0.95) {
                        //                        std::cout << "Right" << std::endl;
                        //                        entities[i].x -= entities[i].penetration;
                        //                        entities[0].acceleration_x = -1.0;
                    }
                }
            }
        }
    }
    for (size_t i=0; i < entities.size(); i++) {
        if (entities[i].type != "Player")
        {
            if (entities[0].collidesWith(entities[i])){
                if (entities[i].type == "Goal")
                {
//                    entities[i].width = 0.0;
//                    entities[i].height = 0.0;
                }
            }
        }
    }
}
void ClassDemoApp::UpdateGameLevel5(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                if (entities[0].collidedBottom) {
                    entities[0].direction_y = 1.0;
                    entities[0].Update(elapsed);
                    entities[0].collidedBottom = false;
                }
                
            }
        }
    }
    
    if (keys[SDL_SCANCODE_LEFT]) {
        entities[0].direction_x = -1.0;
        entities[0].acceleration_x = -1.0;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0].direction_x = 1.0;
        entities[0].acceleration_x = 1.0;
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //Effect Environment
        //Shake Screen
        screenShakeValue += elapsed;
        screenShakeIntensity = 0.02;
        screenShakeSpeed = 20.0;
    }
    entities[0].Update(elapsed);
    for (size_t i=0; i < entities.size(); i++) {
        for (size_t j=0; j < collisionBoxes.size(); j++) {
            if (entities[i].type == "Player") {
                if (entities[i].collidesWith(collisionBoxes[j])) {
                    //                    std::cout << "Does it enter the test?" << std::endl;
                    //Vertical Collisions
                    if (entities[i].collidedBottom) {
                        //                        std::cout << "Bottom" << std::endl;
                        //                        std::cout << "Befor: "<< entities[i].penetration << std::endl;
                        entities[0].velocity_y = 0.0;
                        //                        entities[i].y -= entities[i].penetration*0.05;
                        //                        std::cout << "After: "<< entities[i].penetration/55000 << std::endl;
                    } else if (entities[i].collidedTop) {
                        //                        std::cout << "Top" << std::endl;
                        //                        entities[i].y -= entities[i].penetration;
                    }
                    //Hroizontal Collisions
                    if (entities[i].collidedLeft || entities[i].x < -0.002) {
                        //                        std::cout << "Left" << std::endl;
                        //                        entities[i].x += entities[i].penetration;
                        //                        entities[0].acceleration_x = 1.0;
                    } else if (entities[i].collidedRight || entities[i].x > 0.95) {
                        //                        std::cout << "Right" << std::endl;
                        //                        entities[i].x -= entities[i].penetration;
                        //                        entities[0].acceleration_x = -1.0;
                    }
                }
            }
        }
    }
    for (size_t i=0; i < entities.size(); i++) {
        if (entities[i].type != "Player")
        {
            if (entities[0].collidesWith(entities[i])){
                if (entities[i].type == "Goal")
                {
//                    entities[i].width = 0.0;
//                    entities[i].height = 0.0;
                }
            }
        }
    }
}
//void ClassDemoApp::UpdateGameLevel6(float elapsed) {
//    while (SDL_PollEvent(&event)) {
//        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//            done = true;
//        }
//        if(event.type == SDL_KEYDOWN) {
//            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
//                if (entities[0].collidedBottom) {
//                    entities[0].velocity_y = 1.0;
//                    entities[0].Update(elapsed);
//                    entities[0].collidedBottom = false;
//                }
//                
//            }
//        }
//    }
//}
void ClassDemoApp::UpdateGameLevel7(float elapsed) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
//        if(event.type == SDL_KEYDOWN) {
//            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
//                if (entities[0].collidedBottom) {
//                    entities[0].direction_y = 1.0;
//                    entities[0].y += .01;
//                    entities[0].Update(elapsed);
//                    entities[0].collidedBottom = false;
//                }
//                
//            }
//        }
    }

    if (keys[SDL_SCANCODE_LEFT]) {
        entities[0].direction_x = -1.0;
        entities[0].acceleration_x = -1.0;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        entities[0].direction_x = 1.0;
        entities[0].acceleration_x = 1.0;
    }
    if (keys[SDL_SCANCODE_SPACE]) {
        //Effect Environment
        //Shake Screen
        screenShakeValue += elapsed;
        screenShakeIntensity = 0.02;
        screenShakeSpeed = 20.0;
    }
    if (keys[SDL_SCANCODE_UP]) {
        if (entities[0].collidedBottom) {
//            entities[0].direction_y = 1.0;
            entities[0].y += .12;
            entities[0].Update(elapsed);
            entities[0].collidedBottom = false;
        }
    }
    entities[0].Update(elapsed);
    for (size_t i=0; i < entities.size(); i++) {
        for (size_t j=0; j < collisionBoxes.size(); j++) {
            if (entities[i].type == "Player") {
                if (entities[i].collidesWith(collisionBoxes[j])) {
                    //                    std::cout << "Does it enter the test?" << std::endl;
                    //Vertical Collisions
                    if (entities[i].collidedBottom) {
                        //                        std::cout << "Bottom" << std::endl;
                        //                        std::cout << "Befor: "<< entities[i].penetration << std::endl;
                        entities[0].velocity_y = 0.0;
                        entities[i].y -= entities[i].penetration/100000000000;
                        //                        std::cout << "After: "<< entities[i].penetration/55000 << std::endl;
                    } else if (entities[i].collidedTop) {
                        //                        std::cout << "Top" << std::endl;
                        //                        entities[i].y -= entities[i].penetration;
                    }
                    //Hroizontal Collisions
                    if (entities[i].collidedLeft || entities[i].x < -0.002) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Left" << std::endl;
                        //                        entities[i].x += entities[i].penetration;
                        //                        entities[0].acceleration_x = 1.0;
                    } else if (entities[i].collidedRight || entities[i].x > 0.95) {
                        entities[i].acceleration_x = 0.0;
                        //                        std::cout << "Right" << std::endl;
                        //                        entities[i].x -= entities[i].penetration;
                        //                        entities[0].acceleration_x = -1.0;
                    }
                }
            }
        }
    }
    for (size_t i=0; i < entities.size(); i++) {
        if (entities[i].type != "Player")
        {
            if (entities[0].collidesWith(entities[i])){
                if (entities[i].type == "Goal")
                {
//                    entities[i].width = 0.0;
//                    entities[i].height = 0.0;
                }
            }
        }
    }
}


void ClassDemoApp::UpdateGameOver() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        
    }
}

void ClassDemoApp::Render(float elapsed) {
    switch(state) {
        case STATE_MAIN_MENU:
            RenderMainMenu();
            break;
        case STATE_GAME_LEVEL1:
            RenderGameLevel1(elapsed);
            break;
        case STATE_GAME_LEVEL2:
            RenderGameLevel2(elapsed);
            break;
        case STATE_GAME_LEVEL3:
            RenderGameLevel3(elapsed);
            break;
        case STATE_GAME_LEVEL4:
            RenderGameLevel4(elapsed);
            break;
        case STATE_GAME_LEVEL5:
            RenderGameLevel5(elapsed);
            break;
//        case STATE_GAME_LEVEL6:
//            RenderGameLevel6(elapsed);
//            break;
        case STATE_GAME_LEVEL7:
            RenderGameLevel7(elapsed);
            break;
        case STATE_GAME_OVER:
            RenderGameOver();
            break;
    }
}
void ClassDemoApp::Update(float elapsed) {
    switch(state) {
        case STATE_MAIN_MENU:
            UpdateMainMenu();
            break;
        case STATE_GAME_LEVEL1:
            UpdateGameLevel1(elapsed);
            break;
        case STATE_GAME_LEVEL2:
            UpdateGameLevel2(elapsed);
            break;
        case STATE_GAME_LEVEL3:
            UpdateGameLevel3(elapsed);
            break;
        case STATE_GAME_LEVEL4:
            UpdateGameLevel4(elapsed);
            break;
        case STATE_GAME_LEVEL5:
            UpdateGameLevel5(elapsed);
            break;
//        case STATE_GAME_LEVEL6:
//            UpdateGameLevel6(elapsed);
//            break;
        case STATE_GAME_LEVEL7:
            UpdateGameLevel7(elapsed);
            break;

        case STATE_GAME_OVER:
            UpdateGameOver();
            break;
    }
}

bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    
    Update(elapsed);
    Render(elapsed);
    return done;
}

void ClassDemoApp::drawLevel() {
    int textureID = LoadTexture("pixel_sprites_sheet.png");
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    
    for(int y=0; y < LEVEL_HEIGHT; y++) {
        for(int x=0; x < LEVEL_WIDTH; x++) {
            if(levelData[y][x] != 0) {
                
                //HACK NOTE
                Entity hitBox;
                hitBox.type = "HitBox";
                hitBox.x = TILE_SIZE * x;
                hitBox.y = (-TILE_SIZE * y)-TILE_SIZE;
                hitBox.width = 0.05;
                hitBox.height = 0.05;
                collisionBoxes.push_back(hitBox);
                
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
//    glTranslatef(0.0f, sin(screenShakeValue * screenShakeSpeed)* screenShakeIntensity, 0.0f);
    
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
        } else if(line == "[Button]") {
            readEntityData(infile);
        } else if(line == "[Ice]") {
            readEntityData(infile);
        } else if(line == "[Wall1]") {
            readEntityData(infile);
        } else if(line == "[Wall2]") {
            readEntityData(infile);
        } else if(line == "[Saw1]") {
            readEntityData(infile);
        } else if(line == "[Saw2]") {
            readEntityData(infile);
        } else if(line == "[Saw3]") {
            readEntityData(infile);
        } else if(line == "[Saw4]") {
            readEntityData(infile);
        }
    }
    infile.close();
}

void ClassDemoApp::placeEntity(std::string type, float placeX, float placeY) {
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i].type == type) {
            entities[i].x = placeX;
            entities[i].y = placeY;
            //            entities[i].sprite.x = placeX;
            //            entities[i].sprite.y = placeY;
        }
    }
}
void ClassDemoApp::appAudioCallback(void *userdata, Uint8 *stream, int len) {
    ClassDemoApp *app = (ClassDemoApp*) userdata;
    float *mixBuffer = new float[len/4];
    memset(stream, 0, len);
    memset(mixBuffer, 0, len);
    int numSoundsMixed = 0;
    for(int i=0; i < app->mixSounds.size(); i++) {
        MixerSound *sound = &app->mixSounds[i];
        if(sound->loaded && sound->playing) {
            for(int s=0; s < len/4; s++) {
                float *sourceBuffer = (float*) (sound->buffer+sound->offset);
                mixBuffer[s] += (sourceBuffer[s] * sound->volume);
            }
            numSoundsMixed++;
            sound->offset += len;
            if(sound->offset >= sound->length-len) {
                if(sound->loop) {
                    sound->offset = 0;
                } else {
                    sound->playing = false;
                }
            }
        }
    }
    if(numSoundsMixed > 0) {
        for(int s=0; s < len/4; s++) {
            ((float*)stream)[s] = mixBuffer[s] / (float)numSoundsMixed;
        }
    }
    free(mixBuffer);
}
//void ClassDemoApp::playSound(int soundIdx, bool loop) {
//    if(soundIndex >= 0 && soundIndex < mixerSounds.size()) {
//        mixSounds[soundIdx].playing = true;
//        mixSounds[soundIdx].offset = 0;
//        mixSounds[soundIdx].loop = loop;
//    }
//}
//int ClassDemoApp::loadSound(const char *soundFile) {
//    Uint8 *buffer;
//    SDL_AudioSpec spec;
//    Uint32 bufferSize;
//    if(SDL_LoadWAV(soundFile, &spec, &buffer, &bufferSize) == NULL) {
//        return -1;
//    }
//    SDL_AudioCVT cvt;
//    SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq,
//                      deviceSpec.format, deviceSpec.channels, deviceSpec.freq);
//    cvt.len = bufferSize;
//    cvt.buf = new Uint8[bufferSize * cvt.len_mult];
//    memcpy(cvt.buf, buffer, bufferSize);
//    SDL_ConvertAudio(&cvt);
//    SDL_FreeWAV(buffer);
//    MixerSound sound;
//    sound.buffer = cvt.buf;
//    sound.length = cvt.len_cvt;
//    sound.loaded = true;
//    sound.offset = 0;
//    sound.format = deviceSpec.format;
//    sound.volume = 1.0;
//    sound.playing = false;
//    mixSounds.push_back(sound);
//    return mixerSounds.size()-1;
//}



