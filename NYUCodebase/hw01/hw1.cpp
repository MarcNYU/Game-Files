//
//  hw1.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/16/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <stdio.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>



SDL_Window* displayWindow;

typedef struct {
    float x;
    float y;
    float r;
    float g;
    float b;
} Vertex2D;



void DrawSprite(GLint texture, float x, float y, float rotation);
GLuint LoadTexture(const char *image_path);

void drawRoad();
void drawArow(float x, float y, float z, float h, float w, float d);
void runCar(const char *image_path, float speed);



// controller
/*while (sdl_PollEvent(&event)) {
 
 
 
 
 
 */
void Setup() {
    // setup SDL
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
    
    // setup OpenGL
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    // Set our projection matrix
    glClearColor(0.33f, 1.0f, 0.33f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 1200, 1000);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
}
int main()
{
    //	SDL_Init(SDL_INIT_VIDEO);
    //	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
    //	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    //	SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    SDL_Event event;
    
    //    glClearColor(0.33f, 1.0f, 0.33f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    glViewport(0, 0, 1200, 1000);
    //    glMatrixMode(GL_PROJECTION);
    //    glMatrixMode(GL_MODELVIEW);
    Setup();
    
    typedef struct SDL_Surface
    {
        int w; // width of the image
        int h; // height of the image
        int pitch; // size of a row in bytes
        void *pixels; // pointer to pixel data
        // …other data
    } SDL_Surface;
    
    
    drawRoad();
    drawArow(2.0, 0.3, 0.0, 0.5, 0.125, 1.0);
    drawArow(-8.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    drawArow(0.0, -3.0, 0.0, 1.0, 1.0, 1.0);
    drawArow(8.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
            /*----------------------------Check INPUTS-------------------------*/
            if(keys[SDL_SCANCODE_UP]) {
                std::cout<<"UP"<<std::endl;
            } else if(keys[SDL_SCANCODE_DOWN]) {
                std::cout<<"DOWN"<<std::endl;
            }
            
            //dependent on controller
            // XB360
            
            
            /*else if (event.type == sdl_joyaxismotion){
             if(event.jaxis.whith ==0
             if(event.jaxis.axis==0
             float unitvalue = (float) event.jaxis.value/32767.0f
             if(fab (unitval) < 0.1
             unitval = 0.0
             if(event.jaxis ==0
             xspeed = unitvalue
             else if (event.jaxis.axis ==1
             yspeed = -unitvalue
             
             }
             
             
             
             */
        }
        SDL_GL_SwapWindow(displayWindow);
        
        //        glClear(GL_COLOR_BUFFER_BIT);
        
        //        runCar("sp_car.png", 10.0f);
        float lastFrameTicks = 0.0f;
        
        float ticks = (float)SDL_GetTicks()/10.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        float position = -0.7;
        position += elapsed;
        
        DrawSprite(LoadTexture("sp_car.png"), -0.1, 0.0, position);
        
        DrawSprite(LoadTexture("lx_car.png"), 0.1, 0.2, 0.0);
        
        DrawSprite(LoadTexture("truck.png"), 0.1, -0.1, 0.0);
        
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

void DrawSprite(GLint texture, float x, float y, float rotation) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glScalef(0.125, 0.125, 1.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    glVertexPointer(2, GL_FLOAT, 0, quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
    
}

void drawRoad(){
    glScalef(0.33333, 2.0, 0.0);
    GLfloat quad1[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
    GLfloat quadColor[] =  {0.3, 0.3, 0.3, 1.0,
        0.3, 0.3, 0.3, 1.0,
        0.3, 0.3, 0.3, 1.0,
        0.3, 0.3, 0.3, 1.0};
    glVertexPointer(2, GL_FLOAT, 0, quad1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, quadColor);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
    
    
}

void drawArow(float x, float y, float z, float h, float w, float d){
    glTranslatef(x, y, z);
    glScalef(h, w , d);
    Vertex2D triangle[3] = {{0.0, 0.5, 0.0, 1.0, 0.0},
        {-0.5, -0.5, 0.0, 1.0, 0.0},
        {0.5, -0.5, 0.0, 1.0, 0.0}};
    glVertexPointer(2, GL_FLOAT, sizeof(float) * 5, triangle);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, sizeof(float) * 5, &triangle[0].g);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
}

void runCar(const char *image_path, float speed){
    
    float lastFrameTicks = 0.0f;
    
    float ticks = (float)SDL_GetTicks()/speed;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    float position = -3.0;
    position += elapsed;
    
    DrawSprite(LoadTexture(image_path), 0.0, position, 0.0);
}







