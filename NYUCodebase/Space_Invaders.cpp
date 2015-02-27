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
#include <string>
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
GLuint LoadTexture(const char *image_path);
void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);
void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a);
void UpdateScore(int num);


void Setup();
void Cleanup();



int main(int argc, char *argv[])
{
    Setup();
    
    bool done = false;
    SDL_Event event;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    float lastFrameTicks = 0.0f;
    float ticks = (float)SDL_GetTicks()/1000000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    float pace;
    
    pace = elapsed;
    int phase = 0;
    
    int score = 0;
    
    
    Entity nullSpace(0, 0.0, 0.0, 0.0, 0.0, 0.001);
    
    
    /*----------------------------------PLAYER-------------------------------------*/
    Entity player(LoadTexture("playerShip1_red.png"), 0.0, -0.9, 0.1, 0.1, 0.02);
    
    /*----------------------------------BULLETS-------------------------------------*/
    std::vector<Entity> bullets;
//    for (int amt = 0; amt < MAX_BULLETS; amt++) {
//        Bullet laser;
//        laser.x = player.x;
//        laser.y = player.y;
//        laser.visible = false;
//        laser.angle = 0.0;
//        
//        bullets.push_back(laser);
//    }
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
    
//    Entity laser(0, player.x, -0.9, 0.015625, 0.03125, 0.001);
    
    /*----------------------------------ALIENS-------------------------------------*/
    float zero_position_x = -.9;

    std::vector<Entity> enemyLine1 = makeEnemyLine(LoadTexture("enemyRed4.png"), zero_position_x, 0.0, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine2 = makeEnemyLine(LoadTexture("enemyRed4.png"), zero_position_x, 0.1, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine3 = makeEnemyLine(LoadTexture("enemyGreen3.png"), zero_position_x, 0.2, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine4 = makeEnemyLine(LoadTexture("enemyBlue2.png"), zero_position_x, 0.3, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine5 = makeEnemyLine(LoadTexture("enemyBlack1.png"), zero_position_x, 0.4, 0.0625, 0.0625, 0.001);
    Entity motherShip (LoadTexture("ufoYellow.png"), -1.5, 0.6, 0.125, 0.125, 0.001);
    Entity locator (0, -.75, 0.0, 0.0625, 0.0625, 0.001);
    locator.direction_x = 1.0;
    locator.direction_y = -1.0;

/*-------------------------------------------------------GAME LOOP-------------------------------------------------*/
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
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
                bullets[clip].y += 0.05;
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
        
        
        /*----------------------------------ENENIES-------------------------------------*/
        if (locator.direction_x > 0.0) {
            if ((locator.x + locator.width/2) < -0.55) {
                
                
                glClear(GL_COLOR_BUFFER_BIT);
                
                for (size_t i = 0; i < enemyLine1.size(); i++) {
                    locator.x += pace/11;
                    enemyLine1[i].x += pace;
                    enemyLine2[i].x += pace;
                    enemyLine3[i].x += pace;
                    enemyLine4[i].x += pace;
                    enemyLine5[i].x += pace;
                    motherShip.x += elapsed;
                    
                    if (bullets[clip].x == enemyLine1[i].x || (bullets[clip].x >= (enemyLine1[i].x - (enemyLine1[i].width/2)) && bullets[clip].x <= (enemyLine1[i].x + (enemyLine1[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine1[i].y - (enemyLine1[i].height/2))) {
                            if (enemyLine1[i].textureID != nullSpace.textureID) {
                                enemyLine1[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 10;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine2[i].x || (bullets[clip].x >= (enemyLine2[i].x - (enemyLine2[i].width/2)) && bullets[clip].x <= (enemyLine2[i].x + (enemyLine2[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine2[i].y - (enemyLine2[i].height/2))) {
                            if (enemyLine2[i].textureID != nullSpace.textureID) {
                                enemyLine2[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 10;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine3[i].x || (bullets[clip].x >= (enemyLine3[i].x - (enemyLine3[i].width/2)) && bullets[clip].x <= (enemyLine3[i].x + (enemyLine3[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine3[i].y - (enemyLine3[i].height/2))) {
                            if (enemyLine3[i].textureID != nullSpace.textureID) {
                                enemyLine3[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 20;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine4[i].x || (bullets[clip].x >= (enemyLine4[i].x - (enemyLine4[i].width/2)) && bullets[clip].x <= (enemyLine4[i].x + (enemyLine4[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine4[i].y - (enemyLine4[i].height/2))) {
                            if (enemyLine4[i].textureID != nullSpace.textureID) {
                                enemyLine4[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 30;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine5[i].x || (bullets[clip].x >= (enemyLine5[i].x - (enemyLine5[i].width/2)) && bullets[clip].x <= (enemyLine5[i].x + (enemyLine5[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine5[i].y - (enemyLine5[i].height/2))) {
                            if (enemyLine5[i].textureID != nullSpace.textureID) {
                                enemyLine5[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 50;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == motherShip.x || (bullets[clip].x >= (motherShip.x - (motherShip.width/2)) && bullets[clip].x <= (motherShip.x + (motherShip.width/2))) || motherShip.x >= 2.5) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (motherShip.y - (motherShip.height/2))) {
                            motherShip.x = -2.5;
                            bullets[clip].y = player.y;
                            bullets[clip].x = player.x;
                            shot = false;
                            score += 150;
                        }
                        
                    }
                    
                    //REDRAW ASSETS
                    if (shot == true) {
                        bullets[clip].Draw();
                    }
                    player.Draw();
//                    locator.Draw();
                    enemyLine1[i].Draw();
                    enemyLine2[i].Draw();
                    enemyLine3[i].Draw();
                    enemyLine4[i].Draw();
                    enemyLine5[i].Draw();
                    motherShip.Draw();
                    UpdateScore(score);
                    glDisableClientState(GL_COLOR_ARRAY);

                    
                    
                    
                    switch (phase) {
                        case 2:
                            pace += lastFrameTicks/9000;//SPEED SHIFT
                            enemyLine1[i].y = -0.3;//BOTTOMLINE
                            enemyLine2[i].y = -0.2;
                            enemyLine3[i].y = -0.1;
                            enemyLine4[i].y = 0.0;
                            enemyLine5[i].y = 0.1;//TOPLINE
                            break;
                        case 4:
                            pace += lastFrameTicks/7000;//SPEED SHIFT
                            enemyLine1[i].y = -0.5;//BOTTOMLINE
                            enemyLine2[i].y = -0.4;
                            enemyLine3[i].y = -0.3;
                            enemyLine4[i].y = -0.2;
                            enemyLine5[i].y = -0.1;//TOPLINE
                            break;
                        case 6:
                            pace += lastFrameTicks/100;//SPEED SHIFT
                            enemyLine1[i].y = -0.71;//BOTTOMLINE
                            enemyLine2[i].y = -0.6;
                            enemyLine3[i].y = -0.5;
                            enemyLine4[i].y = -0.4;
                            enemyLine5[i].y = -0.3;//TOPLINE
                            break;
                        case 8:
                            pace += lastFrameTicks/100;//SPEED SHIFT
                            enemyLine3[i].y = -0.71;
                            enemyLine4[i].y = -0.6;
                            enemyLine5[i].y = -0.5;//TOPLINE
                            break;
                        case 11:
                            pace += lastFrameTicks/100;//SPEED SHIFT
                            enemyLine5[i].y = -0.71;//TOPLINE
                            break;
                        default:
                            break;
                    }
                    if (enemyLine1[i].y <= -0.7 || enemyLine2[i].y <= -0.7 || enemyLine3[i].y <= -0.7 ||enemyLine4[i].y <= -0.7 || enemyLine5[i].y <= -0.7) {
                        glClear(GL_COLOR_BUFFER_BIT);
                        glLoadIdentity();
                        glTranslatef(-0.4, 0.0, 0.0);
                        DrawText(LoadTexture("font1.png"), "GAME OVER", 0.1, 0.000000000001, 1.0, 1.0, 1.0, 1.0);
                    }
                }
            }else {
                phase++;
                locator.direction_x = -1.0;
                enemyLine1[0].direction_x = -1.0;
                enemyLine2[0].direction_x = -1.0;
                enemyLine3[0].direction_x = -1.0;
                enemyLine4[0].direction_x = -1.0;
                enemyLine5[0].direction_x = -1.0;
            }
        }
        
        if (locator.direction_x < 0.0) {
            if ((locator.x - enemyLine1[0].width/2) > -0.95) {
                
                
                glClear(GL_COLOR_BUFFER_BIT);
                
                
                for (size_t i = 0; i < enemyLine1.size(); i++) {
                    locator.x -= pace/11;
                    enemyLine1[i].x -= pace;
                    enemyLine2[i].x -= pace;
                    enemyLine3[i].x -= pace;
                    enemyLine4[i].x -= pace;
                    enemyLine5[i].x -= pace;
                    motherShip.x += elapsed;
                    
                    if (bullets[clip].x == enemyLine1[i].x || (bullets[clip].x >= (enemyLine1[i].x - (enemyLine1[i].width/2)) && bullets[clip].x <= (enemyLine1[i].x + (enemyLine1[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine1[i].y - (enemyLine1[i].height/2))) {
                            if (enemyLine1[i].textureID != nullSpace.textureID) {
                                enemyLine1[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 10;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine2[i].x || (bullets[clip].x >= (enemyLine2[i].x - (enemyLine2[i].width/2)) && bullets[clip].x <= (enemyLine2[i].x + (enemyLine2[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine2[i].y - (enemyLine2[i].height/2))) {
                            if (enemyLine2[i].textureID != nullSpace.textureID) {
                                enemyLine2[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 10;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine3[i].x || (bullets[clip].x >= (enemyLine3[i].x - (enemyLine3[i].width/2)) && bullets[clip].x <= (enemyLine3[i].x + (enemyLine3[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine3[i].y - (enemyLine3[i].height/2))) {
                            if (enemyLine3[i].textureID != nullSpace.textureID) {
                                enemyLine3[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 20;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine4[i].x || (bullets[clip].x >= (enemyLine4[i].x - (enemyLine4[i].width/2)) && bullets[clip].x <= (enemyLine4[i].x + (enemyLine4[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine4[i].y - (enemyLine4[i].height/2))) {
                            if (enemyLine4[i].textureID != nullSpace.textureID) {
                                enemyLine4[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 30;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == enemyLine5[i].x || (bullets[clip].x >= (enemyLine5[i].x - (enemyLine5[i].width/2)) && bullets[clip].x <= (enemyLine5[i].x + (enemyLine5[i].width/2)))) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (enemyLine5[i].y - (enemyLine5[i].height/2))) {
                            if (enemyLine5[i].textureID != nullSpace.textureID) {
                                enemyLine5[i] = nullSpace;
                                bullets[clip].y = player.y;
                                bullets[clip].x = player.x;
                                shot = false;
                                score += 50;
                            }
                            
                        }
                        
                    } else if (bullets[clip].x == motherShip.x || (bullets[clip].x >= (motherShip.x - (motherShip.width/2)) && bullets[clip].x <= (motherShip.x + (motherShip.width/2))) || motherShip.x >= 2.5) {
                        if ((bullets[clip].y + (bullets[clip].height/2)) > (motherShip.y - (motherShip.height/2))) {
                            motherShip.x = -2.5;
                            bullets[clip].y = player.y;
                            bullets[clip].x = player.x;
                            shot = false;
                            score += 150;
                        }
                        
                    }
                    
                    //REDRAW ASSETS
                    if (shot == true) {
                        bullets[clip].Draw();
                    }
                    player.Draw();
//                    locator.Draw();
                    enemyLine1[i].Draw();
                    enemyLine2[i].Draw();
                    enemyLine3[i].Draw();
                    enemyLine4[i].Draw();
                    enemyLine5[i].Draw();
                    motherShip.Draw();
                    UpdateScore(score);
                    glDisableClientState(GL_COLOR_ARRAY);
                    
                    
                    
                    switch (phase) {
                        case 1:
                            pace += lastFrameTicks/9000;//SPEED SHIFT
                            enemyLine1[i].y = -0.2;//BOTTOMLINE
                            enemyLine2[i].y = -0.1;
                            enemyLine3[i].y = 0.0;
                            enemyLine4[i].y = 0.1;
                            enemyLine5[i].y = 0.2;//TOPLINE
                            break;
                        case 3:
                            pace += lastFrameTicks/7000;//SPEED SHIFT
                            enemyLine1[i].y = -0.4;//BOTTOMLINE
                            enemyLine2[i].y = -0.3;
                            enemyLine3[i].y = -0.2;
                            enemyLine4[i].y = -0.1;
                            enemyLine5[i].y = 0.0;//TOPLINE
                            break;
                        case 5:
                            pace += lastFrameTicks/5000;//SPEED SHIFT
                            enemyLine1[i].y = -0.6;//BOTTOMLINE
                            enemyLine2[i].y = -0.5;
                            enemyLine3[i].y = -0.4;
                            enemyLine4[i].y = -0.3;
                            enemyLine5[i].y = -0.2;//TOPLINE
                            break;
                        case 7:
                            pace += lastFrameTicks/100;//SPEED SHIFT
                            enemyLine2[i].y = -0.71;
                            enemyLine3[i].y = -0.6;
                            enemyLine4[i].y = -0.5;
                            enemyLine5[i].y = -0.4;//TOPLINE
                            break;
                        case 9:
                            pace += lastFrameTicks/100;//SPEED SHIFT
                            enemyLine4[i].y = -0.71;
                            enemyLine5[i].y = -0.6;//TOPLINE
                            break;
                        default:
                            break;
                    }
                    if (enemyLine1[i].y <= -0.7 || enemyLine2[i].y <= -0.7 || enemyLine3[i].y <= -0.7 ||enemyLine4[i].y <= -0.7 || enemyLine5[i].y <= -0.7) {
                        glClear(GL_COLOR_BUFFER_BIT);
                        glLoadIdentity();
                        glTranslatef(-0.4, 0.0, 0.0);
                        DrawText(LoadTexture("font1.png"), "GAME OVER", 0.1, 0.000000000001, 1.0, 1.0, 1.0, 1.0);
                    }
                }
            } else {
                phase++;
                locator.direction_x = 1.0;
                enemyLine1[0].direction_x = 1.0;
                enemyLine2[0].direction_x = 1.0;
                enemyLine3[0].direction_x = 1.0;
                enemyLine4[0].direction_x = 1.0;
                enemyLine5[0].direction_x = 1.0;
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


void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY) {
    // our regular sprite drawing
    float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
    float spriteWidth = 1.0/(float)spriteCountX;
    float spriteHeight = 1.0/(float)spriteCountY;
    GLfloat quadUVs[] = { u, v,
        u, v+spriteHeight,
        u+spriteWidth, v+spriteHeight,
        u+spriteWidth, v
    };
    // our regular sprite drawing
}

void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a) {
    glBindTexture(GL_TEXTURE_2D, fontTexture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float texture_size = 1.0/16.0f;
    std::vector<float> vertexData;
    std::vector<float> texCoordData;
    std::vector<float> colorData;
    for(int i=0; i < text.size(); i++) {
        float texture_x = (float)(((int)text[i]) % 16) / 16.0f;
        float texture_y = (float)(((int)text[i]) / 16) / 16.0f;
        colorData.insert(colorData.end(), {r,g,b,a, r,g,b,a, r,g,b,a, r,g,b,a});
        vertexData.insert(vertexData.end(), {((size+spacing) * i) + (-0.5f * size), 0.5f * size, ((size+spacing) * i) +
            (-0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), -0.5f * size, ((size+spacing) * i) + (0.5f * size), 0.5f
            * size});
        texCoordData.insert(texCoordData.end(), {texture_x, texture_y, texture_x, texture_y + texture_size, texture_x +
            texture_size, texture_y + texture_size, texture_x + texture_size, texture_y});
    }
    glColorPointer(4, GL_FLOAT, 0, colorData.data());
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDrawArrays(GL_QUADS, 0, text.size() * 4);
}


/*-----------------------------------------------------------------------------------------------------------------*/



void UpdateScore(int num){
    std::string numDis;
    std::string str = std::to_string(num);
    if (num < 100) {
        numDis = "000000" + str;
    } else if (num < 1000) {
        numDis = "00000" + str;
    } else if (num < 10000) {
        numDis = "0000" + str;
    } else if (num < 100000) {
        numDis = "000" + str;
    } else if (num < 1000000) {
        numDis = "00" + str;
    } else if (num < 10000000) {
        numDis = "0" + str;
    }
    glLoadIdentity();
    glTranslatef(-0.9, 0.9, 0.0);
    DrawText(LoadTexture("font1.png"), numDis, 0.1, 0.00000000000001, 1.0, 1.0, 1.0, 1.0);
}

