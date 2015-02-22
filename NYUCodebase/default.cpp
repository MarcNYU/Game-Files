//
//  Space_Invaders.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <math.h>
//#include "ClassDemoApp.h"

SDL_Window* displayWindow;
#define MAX_BULLETS 30

class Bullet {
public:
    Bullet () : x(0.0), y(0.0), visible(true), angle(0.0) {}
    void Update(float elapsed) {y += elapsed;}
    float x;
    float y;
    bool visible;
    float angle;
};

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

class Entity {
public:
    Entity (int texture, float xCord, float yCord, float w, float h, float spd) : x(xCord), y(yCord), rotation(0.0), textureID(texture), width(w), height(h), speed(spd), direction_x(0.0), direction_y(0.0){}
    void Draw();
    float x;
    float y;
    float rotation;
    int textureID;
    float width;
    float height;
    float speed;
    float direction_x;
    float direction_y;
};


#define MAX_BULLETS 30

void ClassDemoApp::shootBullet() {
    bullets[bulletIndex].visible = true;
    bullets[bulletIndex].x = -1.2;
    bullets[bulletIndex].y = 0.0;
    bullets[bulletIndex].angle = (float)(45 - (rand() % 90));
    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
}

void Setup();
bool ProcessEvents();
void Update();
void Render();
void Cleanup();
void invashionTeam(std::vector<Entity> enemyLine, float speed);


int main(int argc, char *argv[])
{
    
    //    ClassDemoApp app;
    //    while(!app.UpdateAndRender()) {}
    //    return 0;
    Setup();
    
    bool done = false;
    SDL_Event event;
    
    
    //
    Bullet bullets[MAX_BULLETS];
    
    
    Entity player(0, 0.0, -0.9, 0.1, 0.1, 0.01);
    
    /*----------------------------------ALIENS-------------------------------------*/
    float zero_position_x = -.9;
    //    float zero_position_y = -0.1;
    
    //    std::vector<std::vector<Entity>> invasion_team;
    std::vector<Entity> enemyLine1;
    //    for (size_t j = 0; j < 5; j++) {
    for (size_t i = 0; i < 11; i++) {
        if (zero_position_x > .6) {
            zero_position_x = -.9;
        }
        zero_position_x += 0.15;
        Entity alien(0, zero_position_x, 0.0, 0.0625, 0.0625, 0.001);
        alien.direction_x = 1.0;
        alien.direction_y = -1.0;
        enemyLine1.push_back(alien);
    }
    //        invasion_team.push_back(enemyLine);
    //    }
    std::vector<Entity> enemyLine2;
    for (size_t i = 0; i < 11; i++) {
        if (zero_position_x > .6) {
            zero_position_x = -.9;
        }
        zero_position_x += 0.15;
        Entity alien(0, zero_position_x, 0.1, 0.0625, 0.0625, 0.001);
        alien.direction_x = 1.0;
        alien.direction_y = -1.0;
        enemyLine2.push_back(alien);
    }
    std::vector<Entity> enemyLine3;
    for (size_t i = 0; i < 11; i++) {
        if (zero_position_x > .6) {
            zero_position_x = -.9;
        }
        zero_position_x += 0.15;
        Entity alien(0, zero_position_x, 0.2, 0.0625, 0.0625, 0.001);
        alien.direction_x = 1.0;
        alien.direction_y = -1.0;
        enemyLine3.push_back(alien);
    }
    std::vector<Entity> enemyLine4;
    for (size_t i = 0; i < 11; i++) {
        if (zero_position_x > .6) {
            zero_position_x = -.9;
        }
        zero_position_x += 0.15;
        Entity alien(0, zero_position_x, 0.3, 0.0625, 0.0625, 0.001);
        alien.direction_x = 1.0;
        alien.direction_y = -1.0;
        enemyLine4.push_back(alien);
    }
    std::vector<Entity> enemyLine5;
    for (size_t i = 0; i < 11; i++) {
        if (zero_position_x > .6) {
            zero_position_x = -.9;
        }
        zero_position_x += 0.15;
        Entity alien(0, zero_position_x, 0.4, 0.0625, 0.0625, 0.001);
        alien.direction_x = 1.0;
        alien.direction_y = -1.0;
        enemyLine5.push_back(alien);
    }
    /*----------------------------------WALLS-------------------------------------*/
    float cord = -1.1;
    
    std::vector<Entity> walls;
    for (size_t i = 0; i < 4; i++) {
        cord += 0.436;
        Entity blocker(0, cord, -0.7, 0.2, 0.0625, 0);
        walls.push_back(blocker);
        
    }
    
    
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float lastFrameTicks = 0.0f;
    float ticks = (float)SDL_GetTicks()/5000000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    float pace;
    
    pace = elapsed;
    
    int phase = 0;
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
            
            /*----------------------------------PLAYER-------------------------------------*/
            if(keys[SDL_SCANCODE_RIGHT]) {
                if ((player.x + (player.height/2)) < 0.95) {
                    float x_position = player.speed;
                    player.x += x_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    //Update
                    player.Draw();
                }
            } else if(keys[SDL_SCANCODE_LEFT]) {
                if ((player.x - (player.height/2)) > -0.95) {
                    float x_position = player.speed;
                    player.x -= x_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    //Update
                    player.Draw();
                }
            } else if(keys[SDL_SCANCODE_SPACE]) {
                for(int num = 0; num < MAX_BULLETS; num++) {
                    bullets[num].Update(elapsed);
                    
                }
            }
            /*----------------------------------ENENIES-------------------------------------*/
            if (enemyLine1[0].direction_x > 0.0) {
                if ((enemyLine1[0].x + enemyLine1[0].width/2) < -0.55) {
                    //                    for (size_t line = 0; line < invasion_team.size(); line++) {
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    
                    for (size_t i = 0; i < enemyLine1.size(); i++) {
                        enemyLine1[i].x += pace;
                        enemyLine2[i].x += pace;
                        enemyLine3[i].x += pace;
                        enemyLine4[i].x += pace;
                        enemyLine5[i].x += pace;
                        //                            invasion_team[line][i].x += invasion_team[0][0].speed;
                        
                        player.Draw();
                        //                            player.Draw();
                        enemyLine1[i].Draw();
                        enemyLine2[i].Draw();
                        enemyLine3[i].Draw();
                        enemyLine4[i].Draw();
                        enemyLine5[i].Draw();
                        walls[0].Draw();
                        walls[1].Draw();
                        walls[2].Draw();
                        walls[3].Draw();
                        
                        switch (phase) {
                            case 2:
                                pace += lastFrameTicks/9000;
                                enemyLine1[i].y = -0.3;
                                enemyLine2[i].y = -0.2;
                                enemyLine3[i].y = -0.1;
                                enemyLine4[i].y = 0.0;
                                enemyLine5[i].y = 0.1;
                                break;
                            case 4:
                                pace += lastFrameTicks/7000;
                                enemyLine1[i].y = -0.5;
                                enemyLine2[i].y = -0.4;
                                enemyLine3[i].y = -0.3;
                                enemyLine4[i].y = -0.2;
                                enemyLine5[i].y = -0.1;
                                break;
                            case 6:
                                pace += lastFrameTicks/500;
                                enemyLine1[i].y = -0.7;
                                enemyLine2[i].y = -0.6;
                                enemyLine3[i].y = -0.5;
                                enemyLine4[i].y = -0.4;
                                enemyLine5[i].y = -0.3;
                                break;
                            case 8:
                                pace += lastFrameTicks/200;
                                enemyLine1[i].y = -0.9;
                                enemyLine2[i].y = -0.8;
                                enemyLine3[i].y = -0.7;
                                enemyLine4[i].y = -0.6;
                                enemyLine5[i].y = -0.5;
                                break;
                            default:
                                break;
                        }
                        //                            if (phase > 0) {
                        //                                invasion_team[line][i].y = -.3;
                        ////                                pace *= logf(2.719);
                        ////                                invasion_team[0][0].speed += .0000000002;
                        //                            }
                        //                        }
                    }
                    //Draw
                }else {
                    phase++;
                    std::cout << phase << std::endl;
                    enemyLine1[0].direction_x = -1.0;
                }
            }
            //            if (invasion_team[0][0].direction_x < 0.0) {
            //                if ((invasion_team[0][0].x - invasion_team[0][0].width/2) > -0.95) {
            if (enemyLine1[0].direction_x < 0.0) {
                if ((enemyLine1[0].x - enemyLine1[0].width/2) > -0.95) {
                    //                    for (size_t line = 0; line < invasion_team.size(); line++) {
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    
                    //                        for (size_t i = 0; i < invasion_team[line].size(); i++) {
                    //                            invasion_team[line][i].x -= pace;
                    //                            invasion_team[line][i].x -= invasion_team[0][0].speed;
                    for (size_t i = 0; i < enemyLine1.size(); i++) {
                        enemyLine1[i].x -= pace;
                        enemyLine2[i].x -= pace;
                        enemyLine3[i].x -= pace;
                        enemyLine4[i].x -= pace;
                        enemyLine5[i].x -= pace;
                        
                        player.Draw();
                        //                            player.Draw();
                        enemyLine1[i].Draw();
                        enemyLine2[i].Draw();
                        enemyLine3[i].Draw();
                        enemyLine4[i].Draw();
                        enemyLine5[i].Draw();
                        walls[0].Draw();
                        walls[1].Draw();
                        walls[2].Draw();
                        walls[3].Draw();
                        
                        switch (phase) {
                            case 1:
                                pace += lastFrameTicks/9000;
                                enemyLine1[i].y = -0.2;
                                enemyLine2[i].y = -0.1;
                                enemyLine3[i].y = 0.0;
                                enemyLine4[i].y = 0.1;
                                enemyLine5[i].y = 0.2;
                                break;
                            case 3:
                                pace += lastFrameTicks/7000;
                                enemyLine1[i].y = -0.4;
                                enemyLine2[i].y = -0.3;
                                enemyLine3[i].y = -0.2;
                                enemyLine4[i].y = -0.1;
                                enemyLine5[i].y = 0.0;
                                break;
                            case 5:
                                pace += lastFrameTicks/500;
                                enemyLine1[i].y = -0.6;
                                enemyLine2[i].y = -0.5;
                                enemyLine3[i].y = -0.4;
                                enemyLine4[i].y = -0.3;
                                enemyLine5[i].y = -0.2;
                                break;
                            case 7:
                                pace += lastFrameTicks/300;
                                enemyLine1[i].y = -0.8;
                                enemyLine2[i].y = -0.7;
                                enemyLine3[i].y = -0.6;
                                enemyLine4[i].y = -0.5;
                                enemyLine5[i].y = -0.4;
                                break;
                            case 9:
                                pace += lastFrameTicks/100;
                                enemyLine1[i].y = -1.0;
                                enemyLine2[i].y = -0.9;
                                enemyLine3[i].y = -0.8;
                                enemyLine4[i].y = -0.7;
                                enemyLine5[i].y = -0.6;
                                break;
                            default:
                                break;
                        }
                        //                            if (phase > 0) {
                        //                                invasion_team[line][i].y = -.2;
                        ////                                pace *= logf(2.719);
                        ////                                invasion_team[0][0].speed += .0000000002;
                        //                            }
                        //                        }
                    }
                    //Draw
                }else {
                    phase++;
                    std::cout << phase << std::endl;
                    //                    invasion_team[0][0].direction_x = 1.0;
                    enemyLine1[0].direction_x = 1.0;
                }
            }
            /*----------------------------------SHEILDS-------------------------------------*/
            //if time
            
        }
        SDL_GL_SwapWindow(displayWindow);
    }
    
    
    Cleanup();
    SDL_Quit();
    return 0;
}

void Entity::Draw() {
    
    glMatrixMode(GL_MODELVIEW);
    
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(width, height, 0.0);
    glRotatef(rotation, 0.0, 0.0, 0.0);
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    GLfloat quadColor[] =  {1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, quadColor);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
}


void Setup() {
    // setup SDL
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    
    // setup OpenGL
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    // Set our projection matrix
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
}

void Cleanup() {
    // cleanup joysticks, textures, etc.
    glClear(GL_COLOR_BUFFER_BIT);
}
