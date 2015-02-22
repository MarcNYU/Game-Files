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
    void Update(float elapsed) {y += elapsed;}
    float x;
    float y;
    bool visible;
    float angle;
};



std::vector<Entity> makeEnemyLine(int texture, float zero_position_x, float zero_position_y, float w, float h, float spd);
void playerControls(Entity player);
GLuint LoadTexture(const char *image_path);
void DrawSpriteSheetSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);
void DrawText(int fontTexture, std::string text, float size, float spacing, float r, float g, float b, float a);
void shootBullet(Bullet bullets[MAX_BULLETS], int bulletIndex);


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
    int phase = 0;
    
    const int runAnimation[] = {9, 10, 11, 12, 13};
    const int numFrames = 5;
    float animationElapsed = 0.0f;
    float framesPerSecond = 30.0f;
    
    int index = 10;
    int spriteCountX = 8;
    int spriteCountY = 4;
    float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
    float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
    float spriteWidth = 1.0/(float)spriteCountX;
    float spriteHeight = 1.0/(float)spriteCountY;
    GLfloat quadUVs[] = { u, v,
        u, v+spriteHeight,
        u+spriteWidth, v+spriteHeight,
        u+spriteWidth, v};
    
    
    
    std::vector<Bullet> bullets;
    for (int amt = 0; amt < MAX_BULLETS; amt++) {
        Bullet lazer;
    }
    
    /*----------------------------------PLAYER-------------------------------------*/
    Entity player(LoadTexture("playerShip1_red.png"), 0.0, -0.9, 0.1, 0.1, 0.001);
    
    /*----------------------------------ALIENS-------------------------------------*/
    float zero_position_x = -.9;

    std::vector<Entity> enemyLine1 = makeEnemyLine(LoadTexture("enemyRed4.png"), zero_position_x, 0.0, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine2 = makeEnemyLine(LoadTexture("enemyRed4.png"), zero_position_x, 0.1, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine3 = makeEnemyLine(LoadTexture("enemyGreen3.png"), zero_position_x, 0.2, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine4 = makeEnemyLine(LoadTexture("enemyBlue2.png"), zero_position_x, 0.3, 0.0625, 0.0625, 0.001);
    std::vector<Entity> enemyLine5 = makeEnemyLine(LoadTexture("enemyBlack1.png"), zero_position_x, 0.4, 0.0625, 0.0625, 0.001);
    
    /*----------------------------------WALLS-------------------------------------*/
    float cord = -1.1;
    
    std::vector<Entity> walls;
    for (size_t i = 0; i < 4; i++) {
        cord += 0.436;
        Entity blocker(LoadTexture("meteorGrey_big1.png"), cord, -0.7, 0.2, 0.0625, 0);
        walls.push_back(blocker);
        
    }
    /*----------------------------------GAME LOOP-------------------------------------*/
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
            
//            animationElapsed += elapsed;
//            if(animationElapsed > 1.0/framesPerSecond) {
//                currentIndex++;
//                animationElapsed = 0.0;
//                if(currentIndex > numFrames-1) {
//                    currentIndex = 0;
//                }
//            }
//            DrawSpriteSheetSprite(spriteTestTexture, runAnimation[currentIndex], 8, 4);
            
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
                shootBullet(<#Bullet *bullets#>, <#int bulletIndex#>)
            }

            
            /*----------------------------------ENENIES-------------------------------------*/
            if (enemyLine1[0].direction_x > 0.0) {
                if ((enemyLine1[0].x + enemyLine1[0].width/2) < -0.55) {
                    
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    
                    for (size_t i = 0; i < enemyLine1.size(); i++) {
                        enemyLine1[i].x += pace;
                        enemyLine2[i].x += pace;
                        enemyLine3[i].x += pace;
                        enemyLine4[i].x += pace;
                        enemyLine5[i].x += pace;
                        
                        
                        player.Draw();
                        
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
//                                enemyLine1[i].y = -0.7;
                                enemyLine2[i].y = -0.6;
                                enemyLine3[i].y = -0.5;
                                enemyLine4[i].y = -0.4;
                                enemyLine5[i].y = -0.3;
                                break;
                            case 8:
                                pace += lastFrameTicks/300;
//                                enemyLine1[i].y = -0.9;
//                                enemyLine2[i].y = -0.8;
//                                enemyLine3[i].y = -0.7;
                                enemyLine4[i].y = -0.6;
                                enemyLine5[i].y = -0.5;
                                break;
                            default:
                                break;
                        }
                        
                    }
                    //Draw
                }else {
                    phase++;
                    std::cout << phase << std::endl;
                    enemyLine1[0].direction_x = -1.0;
                }
            }
            
            if (enemyLine1[0].direction_x < 0.0) {
                if ((enemyLine1[0].x - enemyLine1[0].width/2) > -0.95) {
                    
                    
                    glClear(GL_COLOR_BUFFER_BIT);
                    
                    
                    for (size_t i = 0; i < enemyLine1.size(); i++) {
                        enemyLine1[i].x -= pace;
                        enemyLine2[i].x -= pace;
                        enemyLine3[i].x -= pace;
                        enemyLine4[i].x -= pace;
                        enemyLine5[i].x -= pace;
                        
                        player.Draw();
                        
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
//                                enemyLine1[i].y = -0.8;
//                                enemyLine2[i].y = -0.7;
                                enemyLine3[i].y = -0.6;
                                enemyLine4[i].y = -0.5;
                                enemyLine5[i].y = -0.4;
                                break;
                            case 9:
                                pace += lastFrameTicks/300;
//                                enemyLine1[i].y = -1.0;
//                                enemyLine2[i].y = -0.9;
//                                enemyLine3[i].y = -0.8;
//                                enemyLine4[i].y = -0.7;
                                enemyLine5[i].y = -0.6;
                                break;
                            default:
                                break;
                        }
                        
                    }
                    //Draw
                }else {
                    phase++;
                    std::cout << phase << std::endl;
                    
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    SDL_FreeSurface(surface);
    return textureID;
}

void shootBullet(Bullet bullets[MAX_BULLETS], int bulletIndex) {
    bullets[bulletIndex].visible = true;
//    bullets[bulletIndex].x = -1.2;
    bullets[bulletIndex].y = -0.7;
//    bullets[bulletIndex].angle = (float)(45 - (rand() % 90));
    bulletIndex++;
    if(bulletIndex > MAX_BULLETS-1) {
        bulletIndex = 0;
    }
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





void Update(float pace, float lastFrameTicks, Entity player, std::vector<Entity> enemyLine1, std::vector<Entity> enemyLine2, std::vector<Entity> enemyLine3, std::vector<Entity> enemyLine4, std::vector<Entity> enemyLine5, std::vector<Entity> walls) {
    
    /*----------------------------------PLAYER-------------------------------------*/
    playerControls(player);
    
    /*----------------------------------ENENIES-------------------------------------*/
    int phase = 0;
    if (enemyLine1[0].direction_x > 0.0) {
        if ((enemyLine1[0].x + enemyLine1[0].width/2) < -0.55) {
            
            
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (size_t i = 0; i < enemyLine1.size(); i++) {
                enemyLine1[i].x += pace;
                enemyLine2[i].x += pace;
                enemyLine3[i].x += pace;
                enemyLine4[i].x += pace;
                enemyLine5[i].x += pace;
                
                
                player.Draw();
                
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
                        pace += lastFrameTicks/600000;
                        enemyLine1[i].y = -0.7;
                        enemyLine2[i].y = -0.6;
                        enemyLine3[i].y = -0.5;
                        enemyLine4[i].y = -0.4;
                        enemyLine5[i].y = -0.3;
                        break;
                    case 8:
                        pace += lastFrameTicks/600000;
                        enemyLine1[i].y = -0.9;
                        enemyLine2[i].y = -0.8;
                        enemyLine3[i].y = -0.7;
                        enemyLine4[i].y = -0.6;
                        enemyLine5[i].y = -0.5;
                        break;
                    default:
                        break;
                }
                
            }
            //Draw
        }else {
            phase++;
            std::cout << phase << std::endl;
            enemyLine1[0].direction_x = -1.0;
        }
    }
    
    if (enemyLine1[0].direction_x < 0.0) {
        if ((enemyLine1[0].x - enemyLine1[0].width/2) > -0.95) {
            
            
            glClear(GL_COLOR_BUFFER_BIT);
            
            
            for (size_t i = 0; i < enemyLine1.size(); i++) {
                enemyLine1[i].x -= pace;
                enemyLine2[i].x -= pace;
                enemyLine3[i].x -= pace;
                enemyLine4[i].x -= pace;
                enemyLine5[i].x -= pace;
                
                player.Draw();
                
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
                        pace += lastFrameTicks/6000;
                        enemyLine1[i].y = -0.6;
                        enemyLine2[i].y = -0.5;
                        enemyLine3[i].y = -0.4;
                        enemyLine4[i].y = -0.3;
                        enemyLine5[i].y = -0.2;
                        break;
                    case 7:
                        pace += lastFrameTicks/600000;
                        enemyLine1[i].y = -0.8;
                        enemyLine2[i].y = -0.7;
                        enemyLine3[i].y = -0.6;
                        enemyLine4[i].y = -0.5;
                        enemyLine5[i].y = -0.4;
                        break;
                    case 9:
                        pace += lastFrameTicks/600000;
                        enemyLine1[i].y = -1.0;
                        enemyLine2[i].y = -0.9;
                        enemyLine3[i].y = -0.8;
                        enemyLine4[i].y = -0.7;
                        enemyLine5[i].y = -0.6;
                        break;
                    default:
                        break;
                }
                
            }
            //Draw
        }else {
            phase++;
            std::cout << phase << std::endl;
            
            enemyLine1[0].direction_x = 1.0;
        }
    }
    /*----------------------------------SHEILDS-------------------------------------*/
    //if time

}



void playerControls(Entity player) {
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
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
//        for(int num = 0; num < MAX_BULLETS; num++) {
//            bullets[num].Update(elapsed);
//
//        }
    }

}

