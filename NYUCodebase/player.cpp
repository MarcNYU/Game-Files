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
#include <array>
#include <math.h>
#include "Entity.h"
//#include "ClassDemoApp.h"

SDL_Window* displayWindow;
#define MAX_BULLETS 30

class Bullet : public Entity {
public:
    Bullet() : Entity(0, x, y, 0.015625, 0.03125, 1.0){}
    void Update(float elapsed) {y += elapsed;}
    float x;
    float y;
    bool visible;
    float angle;
    //    int texture;
};



std::vector<Entity> makeEnemyLine(int texture, float zero_position_x, float zero_position_y, float w, float h, float spd);
void playerControls(Entity player);
GLuint LoadTexture(const char *image_path);
void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);
void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a);
void shootBullet(std::vector<Bullet> bullets, int bulletIndex);


void Setup();
bool ProcessEvents();
void Update(float pace, float lastFrameTicks, Entity player, std::vector<Entity> enemyLine1, std::vector<Entity> enemyLine2, std::vector<Entity> enemyLine3, std::vector<Entity> enemyLine4, std::vector<Entity> enemyLine5, std::vector<Entity> walls);
void Render();
void Cleanup();



int main(int argc, char *argv[])
{
    Setup();
    
    bool done = false;
    SDL_Event event;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    float lastFrameTicks = 0.0f;
    float ticks = (float)SDL_GetTicks()/5000000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    float pace;
    
    pace = elapsed;
    
     Entity nullSpace(0, 0.0, 0.0, 0.0, 0.0, 0.0);
    
    /*----------------------------------PLAYER-------------------------------------*/
    Entity player(LoadTexture("playerShip1_red.png"), 0.0, -0.9, 0.1, 0.1, 0.005);
    player.Draw();
    
    /*----------------------------------BULLETS-------------------------------------*/
    std::vector<Entity> bullets;
    for (int amt = 0; amt < MAX_BULLETS; amt++) {
        Entity laser(0, player.x, player.y, 0.015625, 0.03125, 1.0);
//        laser.x = player.x;
//        laser.y = -0.7;
//        laser.visible = false;
//        laser.angle = 0.0;
        bullets.push_back(laser);
    }
    
    bool shot = false;
    int clip = -1;
    
    /*----------------------------------ALIENS-------------------------------------*/
    float zero_position_x = -.9;
    
    std::vector<Entity> enemyLine1 = makeEnemyLine(LoadTexture("enemyRed4.png"), zero_position_x, 0.0, 0.0625, 0.0625, 0.001);

    /*----------------------------------GAME LOOP-------------------------------------*/
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }

            /*----------------------------------PLAYER-------------------------------------*/
            if(keys[SDL_SCANCODE_RIGHT]) {
                if ((player.x + (player.height/2)) < 0.95) {
                    float x_position = player.speed;
//                    bullets[clip].x = player.x;
                    player.x += x_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    //Update
//                    bullets[clip].Draw();
                    player.Draw();
                }
            } else if(keys[SDL_SCANCODE_LEFT]) {
                if ((player.x - (player.height/2)) > -0.95) {
                    float x_position = player.speed;
//                    bullets[clip].x = player.x;
                    player.x -= x_position;
                    glClear(GL_COLOR_BUFFER_BIT);
                    //Update
//                    bullets[clip].Draw();
                    player.Draw();
                }
            } else if(keys[SDL_SCANCODE_SPACE]) {
                shot = true;
                clip++;
                bullets[clip].x = player.x;
            }
            
            
            if (clip < bullets.size()) {
                if (shot == true) {
//                    bullets[clip].x = player.x;
//                    glLoadIdentity();
                    bullets[clip].y += 0.01;
                    glClear(GL_COLOR_BUFFER_BIT);
                    bullets[clip].Draw();
                    player.Draw();
                    if (bullets[clip].y > 1.1) {
                        bullets[clip].y = player.y;
                        bullets[clip].x = player.x;
                        shot = false;
                    }
                    
                }

            } else
                clip = 0;
            
            
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (size_t i = 0; i < enemyLine1.size(); i++) {
                
                if (bullets[clip].x == enemyLine1[i].x || (bullets[clip].x >= (enemyLine1[i].x - (enemyLine1[i].width/2)) && bullets[clip].x <= (enemyLine1[i].x + (enemyLine1[i].width/2)))) {
                    if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine1[i].y - (enemyLine1[i].height/2))) {
                        if (enemyLine1[i].textureID != 0) {
                            enemyLine1[i] = nullSpace;
                            bullets[clip].y = player.y;
                            bullets[clip].x = player.x;
                            shot = false;
                        }
                        
                    }

                }
                
            
                bullets[clip].Draw();
                enemyLine1[i].Draw();
                player.Draw();

            }

        }
        
        SDL_GL_SwapWindow(displayWindow);
    }
    
    
    Cleanup();
    SDL_Quit();
    return 0;
}




void Setup() {
    // setup SDL
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    
    // setup OpenGL
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    // Set our projection matrix
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
}



void Cleanup() {
    // cleanup joysticks, textures, etc.
    glClear(GL_COLOR_BUFFER_BIT);
}

GLuint LoadTexture(const char *image_path) {
    SDL_Surface *surface = IMG_Load(image_path);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA,
                 GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}

void shootBullet(Bullet bullets[MAX_BULLETS], int bulletIndex) {
    bullets[bulletIndex].Draw();
    bullets[bulletIndex].visible = true;
    //    bullets[bulletIndex].x = -1.2;
    bullets[bulletIndex].y = -0.7;
    //    bullets[bulletIndex].angle = (float)(45 - (rand() % 90));
    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
}

std::vector<Entity> makeEnemyLine(int texture, float zero_position_x, float zero_position_y, float w, float h, float spd) {
    std::vector<Entity> enemyLine;
    for (size_t i = 0; i < 11; i++) {
        zero_position_x += 0.15;
        Entity alien(texture, zero_position_x, zero_position_y, w, h, spd);
        alien.direction_x = 1.0;
        alien.direction_y = -1.0;
        enemyLine.push_back(alien);
    }
    return enemyLine;
}




/*-----------------------------------------------------------------------------------------------------------------*/

