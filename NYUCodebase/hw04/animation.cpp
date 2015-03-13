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


// 60 FPS (1.0f/60.0f)
#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

SDL_Window* displayWindow;


class Entity {
public:
    Entity (float x, float y, float w, float h) : x(x), y(y), width(w), height(h), velocity_x (0.0), velocity_y(0.0), acceleration_x(0.0), acceleration_y(0.0), friction_x(0.0), friction_y(0.0), mass(1.0){}
    
    void Update(float elapsed);
    void Render();
    void DrawSprite(int spriteTexture, int index, int spriteCountX, int
                    spriteCountY) {
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, spriteTexture);
        
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        glTranslatef(x, y, 0.0);
        glScalef(width, height, 1.0);
        
        GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
        // our regular sprite drawing
        float u = (float)(((int)index) % spriteCountX) / (float) spriteCountX;
        float v = (float)(((int)index) / spriteCountX) / (float) spriteCountY;
        float spriteWidth = 1.0/(float)spriteCountX;
        float spriteHeight = 1.0/(float)spriteCountY;
        GLfloat quadUVs[] = { u, v,
            u, v+spriteHeight,
            u+spriteWidth, v+spriteHeight,
            u+spriteWidth, v};
        // our regular sprite drawing
        glVertexPointer(2, GL_FLOAT, 0, quad);
        glEnableClientState(GL_VERTEX_ARRAY);
        
        glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glDrawArrays(GL_QUADS, 0, 4);
        glDisable(GL_TEXTURE_2D);
        
    }
    bool collidesWith(Entity *entity) {
        if (x+width/2 > entity->x-entity->width/2) {
            collidedRight = true;
            return collidedRight;
        }
        if (x-width/2 < entity->x+entity->width/2) {
            collidedLeft = true;
            return collidedLeft;
        }
        if (y+height/2 > entity->y-entity->height/2) {
            collidedTop = true;
            return collidedTop;
        }
        if (y-height/2 < entity->y+entity->height/2) {
            collidedBottom = true;
            return collidedBottom;
        }
        return false;
    }
    
    void FixedUpdate();
    
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
    
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
    
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
    
    
    Entity player(0.0, 0.0, 0.125, 0.125);
    player.velocity_x = 1.0;
    player.velocity_y = 35.0;
    player.acceleration_x = 1.0;
    player.acceleration_y = 1.0;
    player.friction_x = 1.0;
    player.friction_y = 1.0;
    player.gravity_x = 1.0;
    player.gravity_y = 1.0;
    
    Entity floor(0.0, -0.8, 1.75, 0.125);
    Entity rightWall(0.845, 0.0, 0.0625, 1.5);
    Entity leftWall(-0.844, 0.0, 0.0625, 1.5);
    Entity platform1(-0.7, -0.5, 0.25, 0.0625);
    Entity platform2(0.7, -0.5, 0.25, 0.0625);
    Entity platform3(0.0, -0.2, 0.5, 0.0625);
    Entity platform4(-0.7, 0.1, 0.25, 0.0625);
    Entity platform5(0.7, 0.1, 0.25, 0.0625);


    
    const int runLeft[] = {18, 17, 18, 19, 16};
    const int runRight[] = {3, 2, 3, 4, 1};
    const int numFrames = 4;
    float animationElapsed = 0.0f;
    float framesPerSecond = 300.0f;
    int currentIndex = 0;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    float timeLeftOver = 0.0f;
    
    while (!done) {
        
        
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    player.velocity_y = 100.0; //lerp(player.velocity_y, 0.0f, FIXED_TIMESTEP * player.friction_y);
                

                    player.velocity_y += player.acceleration_y * FIXED_TIMESTEP;
                    
                    player.y += player.velocity_y * FIXED_TIMESTEP;
                    
                    player.velocity_y += player.gravity_y * elapsed;
                    glClear(GL_COLOR_BUFFER_BIT);
                    if (player.direction_x > 0.0) {
                        player.DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
                        floor.DrawSprite(0, 0, 1.0, 1.0);
                        leftWall.DrawSprite(0, 0, 1.0, 1.0);
                        rightWall.DrawSprite(0, 0, 1.0, 1.0);
                        platform1.DrawSprite(0, 0, 1.0, 1.0);
                        platform2.DrawSprite(0, 0, 1.0, 1.0);
                        platform3.DrawSprite(0, 0, 1.0, 1.0);
                        platform4.DrawSprite(0, 0, 1.0, 1.0);
                        platform5.DrawSprite(0, 0, 1.0, 1.0);
                    } else if (player.direction_x < 0.0) {
                        player.DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
                        floor.DrawSprite(0, 0, 1.0, 1.0);
                        leftWall.DrawSprite(0, 0, 1.0, 1.0);
                        rightWall.DrawSprite(0, 0, 1.0, 1.0);
                        platform1.DrawSprite(0, 0, 1.0, 1.0);
                        platform2.DrawSprite(0, 0, 1.0, 1.0);
                        platform3.DrawSprite(0, 0, 1.0, 1.0);
                        platform4.DrawSprite(0, 0, 1.0, 1.0);
                        platform5.DrawSprite(0, 0, 1.0, 1.0);
                    }
                    
                }
            }
        }
        
        float fixedElapsed = elapsed + timeLeftOver;
        if(fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
            fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
        }
        while (fixedElapsed >= FIXED_TIMESTEP ) {
            fixedElapsed -= FIXED_TIMESTEP;
        }
        timeLeftOver = fixedElapsed;
        
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            animationElapsed = 0.0;
            if(currentIndex > numFrames-1) {
                currentIndex = 0;
            }
        }
        
        float penetration = fabs((player.y - floor.y) - ((player.y - (player.height/2)) - (floor.y + (floor.height/2))));
        
        player.y -= player.gravity_y * FIXED_TIMESTEP;
        
        if (player.direction_x > 0.0) {
            glClear(GL_COLOR_BUFFER_BIT);
            player.DrawSprite(LoadTexture("beck.png"), 0, 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
            leftWall.DrawSprite(0, 0, 1.0, 1.0);
            rightWall.DrawSprite(0, 0, 1.0, 1.0);
            platform1.DrawSprite(0, 0, 1.0, 1.0);
            platform2.DrawSprite(0, 0, 1.0, 1.0);
            platform3.DrawSprite(0, 0, 1.0, 1.0);
            platform4.DrawSprite(0, 0, 1.0, 1.0);
            platform5.DrawSprite(0, 0, 1.0, 1.0);
        } else if (player.direction_x < 0.0) {
            glClear(GL_COLOR_BUFFER_BIT);
            player.DrawSprite(LoadTexture("beck.png"), 15, 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
            leftWall.DrawSprite(0, 0, 1.0, 1.0);
            rightWall.DrawSprite(0, 0, 1.0, 1.0);
            platform1.DrawSprite(0, 0, 1.0, 1.0);
            platform2.DrawSprite(0, 0, 1.0, 1.0);
            platform3.DrawSprite(0, 0, 1.0, 1.0);
            platform4.DrawSprite(0, 0, 1.0, 1.0);
            platform5.DrawSprite(0, 0, 1.0, 1.0);
        }
        
        
        if(keys[SDL_SCANCODE_LEFT]) {
            player.velocity_x = lerp(player.velocity_x, 0.0f, FIXED_TIMESTEP * player.friction_x);
            
            player.velocity_x += player.acceleration_x * FIXED_TIMESTEP;
            
            player.x -= player.velocity_x * FIXED_TIMESTEP;
            
            player.velocity_x -= player.gravity_x * elapsed;
            
            
            player.direction_x = -1.0;
            glClear(GL_COLOR_BUFFER_BIT);
            player.DrawSprite(LoadTexture("beck.png"), runLeft[4], 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
            leftWall.DrawSprite(0, 0, 1.0, 1.0);
            rightWall.DrawSprite(0, 0, 1.0, 1.0);
            platform1.DrawSprite(0, 0, 1.0, 1.0);
            platform2.DrawSprite(0, 0, 1.0, 1.0);
            platform3.DrawSprite(0, 0, 1.0, 1.0);
            platform4.DrawSprite(0, 0, 1.0, 1.0);
            platform5.DrawSprite(0, 0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            player.DrawSprite(LoadTexture("beck.png"), runLeft[currentIndex], 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
            leftWall.DrawSprite(0, 0, 1.0, 1.0);
            rightWall.DrawSprite(0, 0, 1.0, 1.0);
            platform1.DrawSprite(0, 0, 1.0, 1.0);
            platform2.DrawSprite(0, 0, 1.0, 1.0);
            platform3.DrawSprite(0, 0, 1.0, 1.0);
            platform4.DrawSprite(0, 0, 1.0, 1.0);
            platform5.DrawSprite(0, 0, 1.0, 1.0);
            if(keys[SDL_SCANCODE_UP]) {
                
                glClear(GL_COLOR_BUFFER_BIT);
                if (player.direction_x < 0.0) {
                    player.DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
                    floor.DrawSprite(0, 0, 1.0, 1.0);
                    leftWall.DrawSprite(0, 0, 1.0, 1.0);
                    rightWall.DrawSprite(0, 0, 1.0, 1.0);
                    platform1.DrawSprite(0, 0, 1.0, 1.0);
                    platform2.DrawSprite(0, 0, 1.0, 1.0);
                    platform3.DrawSprite(0, 0, 1.0, 1.0);
                    platform4.DrawSprite(0, 0, 1.0, 1.0);
                    platform5.DrawSprite(0, 0, 1.0, 1.0);
                }
            }
        } else if(keys[SDL_SCANCODE_RIGHT]) {
            player.velocity_x = lerp(player.velocity_x, 0.0f, FIXED_TIMESTEP * player.friction_x);
            
            player.velocity_x += player.acceleration_x * FIXED_TIMESTEP;
            
            player.x += player.velocity_x * FIXED_TIMESTEP;
            
            player.velocity_x += player.gravity_x * elapsed;
            
            player.direction_x = 1.0;
            glClear(GL_COLOR_BUFFER_BIT);
            player.DrawSprite(LoadTexture("beck.png"), runRight[4], 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
            leftWall.DrawSprite(0, 0, 1.0, 1.0);
            rightWall.DrawSprite(0, 0, 1.0, 1.0);
            platform1.DrawSprite(0, 0, 1.0, 1.0);
            platform2.DrawSprite(0, 0, 1.0, 1.0);
            platform3.DrawSprite(0, 0, 1.0, 1.0);
            platform4.DrawSprite(0, 0, 1.0, 1.0);
            platform5.DrawSprite(0, 0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            player.DrawSprite(LoadTexture("beck.png"), runRight[currentIndex], 28.0, 1.0);
            floor.DrawSprite(0, 0, 1.0, 1.0);
            leftWall.DrawSprite(0, 0, 1.0, 1.0);
            rightWall.DrawSprite(0, 0, 1.0, 1.0);
            platform1.DrawSprite(0, 0, 1.0, 1.0);
            platform2.DrawSprite(0, 0, 1.0, 1.0);
            platform3.DrawSprite(0, 0, 1.0, 1.0);
            platform4.DrawSprite(0, 0, 1.0, 1.0);
            platform5.DrawSprite(0, 0, 1.0, 1.0);
            if(keys[SDL_SCANCODE_UP]) {
                
                glClear(GL_COLOR_BUFFER_BIT);
                if (player.direction_x > 0.0) {
                    player.DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
                    floor.DrawSprite(0, 0, 1.0, 1.0);
                    leftWall.DrawSprite(0, 0, 1.0, 1.0);
                    rightWall.DrawSprite(0, 0, 1.0, 1.0);
                    platform1.DrawSprite(0, 0, 1.0, 1.0);
                    platform2.DrawSprite(0, 0, 1.0, 1.0);
                    platform3.DrawSprite(0, 0, 1.0, 1.0);
                    platform4.DrawSprite(0, 0, 1.0, 1.0);
                    platform5.DrawSprite(0, 0, 1.0, 1.0);
                }
            }
        } else if(keys[SDL_SCANCODE_UP]) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            if (player.direction_x > 0.0) {
                player.DrawSprite(LoadTexture("beck.png"), 11, 28.0, 1.0);
                floor.DrawSprite(0, 0, 1.0, 1.0);
                leftWall.DrawSprite(0, 0, 1.0, 1.0);
                rightWall.DrawSprite(0, 0, 1.0, 1.0);
                platform1.DrawSprite(0, 0, 1.0, 1.0);
                platform2.DrawSprite(0, 0, 1.0, 1.0);
                platform3.DrawSprite(0, 0, 1.0, 1.0);
                platform4.DrawSprite(0, 0, 1.0, 1.0);
                platform5.DrawSprite(0, 0, 1.0, 1.0);
            } else if (player.direction_x < 0.0) {
                player.DrawSprite(LoadTexture("beck.png"), 24, 28.0, 1.0);
                floor.DrawSprite(0, 0, 1.0, 1.0);
                leftWall.DrawSprite(0, 0, 1.0, 1.0);
                rightWall.DrawSprite(0, 0, 1.0, 1.0);
                platform1.DrawSprite(0, 0, 1.0, 1.0);
                platform2.DrawSprite(0, 0, 1.0, 1.0);
                platform3.DrawSprite(0, 0, 1.0, 1.0);
                platform4.DrawSprite(0, 0, 1.0, 1.0);
                platform5.DrawSprite(0, 0, 1.0, 1.0);
            }
        }
        float offset;
        if (player.x < floor.x + floor.width/2 && player.x > floor.x - floor.width/2) {
            if ((player.y - (player.height/2)) <= (floor.y + (floor.height/2))){
                player.y += player.gravity_y * FIXED_TIMESTEP;
                //            player.y += penetration + offset;
            }
        }
        if (player.x < platform1.x + platform1.width/2 && player.x > platform1.x - platform1.width/2) {
            if ((player.y - (player.height/2)) <= (platform1.y + (platform1.height/2))){
                player.y += player.gravity_y * FIXED_TIMESTEP;
                //            player.y += penetration + offset;
            }
        }
        if (player.x < platform2.x + platform2.width/2 && player.x > platform2.x - platform2.width/2) {
            if ((player.y - (player.height/2)) <= (platform2.y + (platform2.height/2))){
                player.y += player.gravity_y * FIXED_TIMESTEP;
                //            player.y += penetration + offset;
            }
        }
        if (player.x < platform3.x + platform3.width/2 && player.x > platform3.x - platform3.width/2) {
            if ((player.y - (player.height/2)) <= (platform3.y + (platform3.height/2))){
                player.y += player.gravity_y * FIXED_TIMESTEP;
                //            player.y += penetration + offset;
            }
        }
        if (player.x < platform4.x + platform4.width/2 && player.x > platform4.x - platform4.width/2) {
            if ((player.y - (player.height/2)) <= (platform4.y + (platform4.height/2))){
                player.y += player.gravity_y * FIXED_TIMESTEP;
                //            player.y += penetration + offset;
            }
        }
        if (player.x < platform5.x + platform5.width/2 && player.x > platform5.x - platform5.width/2) {
            if ((player.y - (player.height/2)) <= (platform5.y + (platform5.height/2))){
                player.y += player.gravity_y * FIXED_TIMESTEP;
                //            player.y += penetration + offset;
            }
        }
        
        if (player.x + player.width/2 >= rightWall.x - rightWall.width/2) {
            if ((player.y - (player.height/2)) <= (rightWall.y + (rightWall.height/2))){
                player.velocity_x = lerp(player.velocity_x, 0.0f, FIXED_TIMESTEP * player.friction_x);
                
                player.velocity_x += player.acceleration_x * FIXED_TIMESTEP;
                
                player.x -= player.velocity_x * FIXED_TIMESTEP;
                
                player.velocity_x -= player.gravity_x * elapsed;
                
            }
        }
        if (player.x - player.width/2 <= leftWall.x + leftWall.width/2) {
            if ((player.y - (player.height/2)) <= (leftWall.y + (leftWall.height/2))){
                player.velocity_x = lerp(player.velocity_x, 0.0f, FIXED_TIMESTEP * player.friction_x);
                
                player.velocity_x += player.acceleration_x * FIXED_TIMESTEP;
                
                player.x += player.velocity_x * FIXED_TIMESTEP;
                
                player.velocity_x += player.gravity_x * elapsed;
                
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
float lerp(float v0, float v1, float t) {
    return (1.0-t)*v0 + t*v1;
}

