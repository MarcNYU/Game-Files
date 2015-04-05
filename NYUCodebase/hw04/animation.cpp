//
//  animation.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 3/7/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//


#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include <string>


// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

SDL_Window* displayWindow;


class SheetSprite {
public:
    SheetSprite(unsigned int textureID, float u, float v, float width, float height) : textureID(textureID), u(u), v(v), width(width), height(height){}
    
    void Draw(float scale) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        GLfloat quad[] = {-width * scale , height * scale, -width * scale, -height * scale,
            width * scale, -height * scale, width * scale, height * scale};
        GLfloat quadUVs[] = {u, v, u, v+height, u+width, v+height, u+width, v};
        
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glDrawArrays(GL_QUADS, 0, 4);
        glDisable(GL_TEXTURE_2D);
    }

    
    float scale;
    unsigned int textureID;
    float u;
    float v;
    float width;
    float height;
};

class Entity {
public:
    Entity (float x, float y, float w, float h) : x(x), y(y), width(w), height(h), velocity_x (0.0), velocity_y(0.0), acceleration_x(0.0), acceleration_y(0.0), friction_x(0.0), friction_y(0.0), mass(1.0), direction_x(0.0), direction_y(0.0), numFrames(0), framesPerSecond(0.0), gravity_x(0.0), gravity_y(0.0), spriteSheetTexture(0), sprite(spriteSheetTexture, 0.0, 0.0, width, height) {}
    
    void Update(float elapsed);
    void Render(float elapsed);
    
    bool collidesWith(Entity *entity);
    
    void FixedUpdate();
    SheetSprite sprite;
    
    float x;
    float y;
    
    float width;
    float height;
    
    float direction_x;
    float direction_y;
    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float gravity_x;
    float gravity_y;
    float mass;
    bool isStatic;
    
    bool enableCollisions;
    
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    
    int numFrames;
    std::string name;
    float animationElapsed = 0.0f;
    float framesPerSecond;
    int currentIndex = 0;
    float offset;
    float penetration;
    float scale;
    unsigned int spriteSheetTexture;
};


class Bullet {
public:
    void Update(float elapsed);
    float x;
    float y;
    bool visible;
    float angle;
};

GLuint LoadTexture(const char *image_path);
float lerp(float v0, float v1, float t);


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    SDL_Event event;
    
    float lastFrameTicks = 0.0f;
    float ticks = (float)SDL_GetTicks()/1000000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    
    Entity player(0.0, 0.0, 0.104, 0.22);
    player.name = "player";
    player.scale = 0.7f;
    player.spriteSheetTexture = LoadTexture("volt.png");
    player.sprite = SheetSprite(player.spriteSheetTexture, 425.0f/1024.0f, 468.0f/1024.0f,
                                93.0f/1024.0f, 84.0f/1024.0f);
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float timeLeftOver = 0.0f;
    
    while (!done) {
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        
        if (player.direction_x > 0.0) {
            glClear(GL_COLOR_BUFFER_BIT);
            player.Render(elapsed);
           
        } else if (player.direction_x < 0.0) {
            glClear(GL_COLOR_BUFFER_BIT);
            player.Render(elapsed);
            
        }
        
        
        if(keys[SDL_SCANCODE_LEFT]) {
            
            player.direction_x = -1.0;
            glClear(GL_COLOR_BUFFER_BIT);
            player.Render(elapsed);
           
            if(keys[SDL_SCANCODE_UP]) {
                
                glClear(GL_COLOR_BUFFER_BIT);
                if (player.direction_x < 0.0) {
                    player.Render(elapsed);
                    
                }
            }
        } else if(keys[SDL_SCANCODE_RIGHT]) {
            
            player.direction_x = 1.0;
            glClear(GL_COLOR_BUFFER_BIT);
            player.Render(elapsed);
 
            if(keys[SDL_SCANCODE_UP]) {
                
                glClear(GL_COLOR_BUFFER_BIT);
                if (player.direction_x > 0.0) {
                    player.Render(elapsed);
                    
                }
            }
        } else if(keys[SDL_SCANCODE_UP]) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            if (player.direction_x > 0.0) {
                player.Render(elapsed);
                
            } else if (player.direction_x < 0.0) {
                player.Render(elapsed);
                
            }
        }
        
        SDL_GL_SwapWindow(displayWindow);
    }
    
    SDL_Quit();
    return 0;
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
void Entity::Render(float elapsed) {
    //    sprite.u = 0.1;//increment .1
    //    sprite.v = 0.0;//0
    //    sprite.v = 0.23;//1
    //    sprite.v = 0.45;//2
    //    sprite.v = 0.7;//3
    if (name == "player") {
        sprite.width = 0.104;
        sprite.height = 0.22;
        sprite.Draw(scale);
        std::vector<float> idel_r_s = {0.0, 0.1};
        std::vector<float> idel_r = {0.1, 0.3};
        std::vector<float> run_r_s = {0.0, 0.1, 0.2, 0.1};
        std::vector<float> run_r = {0.0, 0.1, 0.2, 0.1};
        std::vector<float> jump_r_s = {0.3, 0.4};
        std::vector<float> jump_r = {0.3, 0.4};
        std::vector<float> idel_l_s = {0.9, 0.8};
        std::vector<float> idel_l = {0.8, 0.6};
        std::vector<float> run_l_s = {0.9, 0.8, 0.7, 0.8};
        std::vector<float> run_l = {0.9, 0.8, 0.7, 0.8};
        std::vector<float> jump_l_s = {0.6, 0.5};
        std::vector<float> jump_l = {0.6, 0.5};
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            animationElapsed = 0.0;
            if(currentIndex > 8) {
                currentIndex = 0;
            }
        }
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
//        if (keys[SDL_SCANCODE_SPACE]) {
//            if(keys[SDL_SCANCODE_RIGHT]) {
//                if (collidedBottom) {
//                    //Rigth Running Animation
//                    sprite.v = 0.45;
//                    for (currentIndex; currentIndex < run_r_s.size(); currentIndex++) {
//                        sprite.u = run_r_s[currentIndex];
//                    }
//                    
//                }
//            } else if(keys[SDL_SCANCODE_LEFT]) {
//                if (collidedBottom) {
//                    //Left Running Animation
//                    sprite.v = 0.45;
//                    for (currentIndex; currentIndex < run_l_s.size(); currentIndex++) {
//                        sprite.u = run_l_s[currentIndex];
//                    }
//                }
//            } else if(keys[SDL_SCANCODE_UP]) {
//                if (direction_x < 0.0) {
//                    //Left Jump
//                    sprite.v = 0.45;
//                    for (currentIndex; currentIndex < jump_l_s.size(); currentIndex++) {
//                        sprite.u = jump_l_s[currentIndex];
//                    }
//                } else
//                    //Right Jump
//                    sprite.v = 0.45;
//                for (currentIndex; currentIndex < jump_r_s.size(); currentIndex++) {
//                    sprite.u = jump_r_s[currentIndex];
//                }
//            }
//            else {
//                if (true) {
//                    if (direction_x < 0.0) {
//                        //Left Idel
//                        sprite.v = 0.0;
//                        for (currentIndex; currentIndex < idel_l_s.size(); currentIndex++) {
//                            sprite.u = idel_l_s[currentIndex];
//                        }
//                    } else
//                        //Right Idel
//                        sprite.v = 0.0;
//                    for (currentIndex; currentIndex < idel_r_s.size(); currentIndex++) {
//                        sprite.u = idel_r_s[currentIndex];
//                    }
//                } else {
//                    if (direction_x < 0.0) {
//                        //Left Fall
//                        sprite.v = 0.0;
//                        sprite.u = 0.7;
//                    } else
//                        //Right Fall
//                        sprite.v = 0.0;
//                    sprite.u = 0.2;
//                }
//            }
////            if (!collidedBottom) {
////                if (direction_x < 0.0) {
////                    //Left Fall
////                    sprite.v = 0.0;
////                    sprite.u = 0.7;
////                } else
////                    //Right Fall
////                    sprite.v = 0.0;
////                sprite.u = 0.2;
////            }
//            
//        }
//        else {
            if(keys[SDL_SCANCODE_RIGHT]) {
                    //Rigth Running Animation
                 direction_x = 1.0;
                sprite.v = 0.7;
//                sprite.u = 0.0;
//                for (float num : run_r) {
//                    sprite.u = num;
//                }
                sprite.u = run_r[currentIndex];
                
            } else if(keys[SDL_SCANCODE_LEFT]) {
                    //Left Running Animation
                direction_x = -1.0;
                    sprite.v = 0.7;
                    sprite.u = 0.9;
                
            } else if(keys[SDL_SCANCODE_UP]) {
                if (direction_x < 0.0) {
                    //Left Jump
                    sprite.v = 0.7;
                     sprite.u = 0.5;
                } else
                    //Right Jump
                    sprite.v = 0.7;
                    sprite.u = 0.4;
                
            } else {
                    if (direction_x < 0.0) {
                        //Left Idel
                        sprite.v = 0.0;
                        sprite.u = 0.8;
                        
                    } else
                        //Right Idel
                        sprite.v = 0.0;
                        sprite.u = 0.1;
                    
                }
//            else {
//                    if (direction_x < 0.0) {
//                        //Left Fall
//                        sprite.v = 0.0;
//                        sprite.u = 0.7;
//                    } else
//                        //Right Fall
//                        sprite.v = 0.0;
//                        sprite.u = 0.2;
//                }
            }
            //            if (!collidedBottom) {
            //                if (direction_x < 0.0) {
            //                    //Left Fall
            //                    sprite.v = 0.0;
            //                    sprite.u = 0.7;
            //                } erlse
            //                    //Right Fall
            //                    sprite.v = 0.0;
            //                sprite.u = 0.2;
            //            }
//        }
        
//    }
}

float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

void Entity::FixedUpdate() {
    velocity_x = lerp(velocity_x, 0.0f, FIXED_TIMESTEP * friction_x);
    velocity_y = lerp(velocity_y, 0.0f, FIXED_TIMESTEP * friction_y);
    velocity_x += acceleration_x * FIXED_TIMESTEP;
    velocity_y += acceleration_y * FIXED_TIMESTEP;
    x += velocity_x * FIXED_TIMESTEP;
    y += velocity_y * FIXED_TIMESTEP;
}
bool Entity::collidesWith(Entity *entity) {
    //Bottom Collison
    if (y-height/2 < entity->height) {
        collidedBottom = true;
        return true;
    }
    //Right Collison
    if (x+width/2 > entity->width) {
        collidedRight = true;
        return true;
    }
    //Left Collison
    if (x-width/2 < entity->width) {
        collidedLeft = true;
        return true;
    }
    //Top Collison
    if (y+height/2 > entity->height) {
        collidedTop = true;
        return true;
    }
    return false;
}


void Bullet::Update(float elapsed) {
    x += elapsed;
}
