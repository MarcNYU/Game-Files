//
//  ptest.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 2/15/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

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

void drawBall();
void drawPlayer(float x, float y, float z, float h, float w, float d);
void runCar(const char *image_path, float speed);



// controller
/*while (sdl_PollEvent(&event)) {
 
 
 
 
 
 */
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    SDL_Event event;
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 1200, 1000);
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
    
    
    typedef struct SDL_Surface
    {
        int w; // width of the image
        int h; // height of the image
        int pitch; // size of a row in bytes
        void *pixels; // pointer to pixel data
        // …other data
    } SDL_Surface;
    
    
    drawBall();
    drawPlayer(17.0, 0.0, 0.0, 1.0, 6.5, 1.0);
//    drawPlayer(-34.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }else if(event.type == SDL_KEYDOWN) {
                
                if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    // DO AN ACTION WHEN SPACE IS PRESSED!
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_UP){
                    float lastFrameTicks = 0.0f;
                    float ticks = (float)SDL_GetTicks()/1000.0f;
                    float elapsed = ticks - lastFrameTicks;
                    lastFrameTicks = ticks;
                    float position = 0.0;
                    position += elapsed;
                    drawPlayer(-34.0, position, 0.0, 1.0, 1.0, 1.0);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN){
                    float lastFrameTicks = 0.0f;
                    float ticks = (float)SDL_GetTicks()/1000.0f;
                    float elapsed = ticks - lastFrameTicks;
                    lastFrameTicks = ticks;
                    float position = 0.0;
                    position += elapsed;
                    drawPlayer(-34.0, position, 0.0, 1.0, 1.0, 1.0);
                }
                
                
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

void drawBall(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(0.0535, 0.0625, 0.0);
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

void drawPlayer(float x, float y, float z, float h, float w, float d){
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    glTranslatef(x, y, z);
    glScalef(h, w , d);
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

void runCar(const char *image_path, float speed){
    
    float lastFrameTicks = 0.0f;
    
    float ticks = (float)SDL_GetTicks()/speed;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    float position = -3.0;
    position += elapsed;
    
    DrawSprite(LoadTexture(image_path), 0.0, position, 0.0);
}
//___________________________________________________________________________________________________________

//void drawBall(){
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glScalef(0.0535, 0.0625, 0.0);
//    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
//    GLfloat quadColor[] =  {1.0, 1.0, 1.0, 1.0,
//        1.0, 1.0, 1.0, 1.0,
//        1.0, 1.0, 1.0, 1.0,
//        1.0, 1.0, 1.0, 1.0};
//    glVertexPointer(2, GL_FLOAT, 0, quad);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glColorPointer(4, GL_FLOAT, 0, quadColor);
//    glEnableClientState(GL_COLOR_ARRAY);
//    glDrawArrays(GL_QUADS, 0, 4);
//
//
//}
//
//int main() {
//    Setup();
//    bool done = false;
//    SDL_Event event;
//
////    Entity p1(0.125, 0.5, -0.5, 0.0, 2.0, 0.0);
////    Entity p2(0.125, 0.5, 0.5, 0.0, 2.0, 0.0);
////    Entity ball(1.0, 1.0, 0.0, 0.0, 2.0, 0.0);
////    ball.Draw();
//
//    //        ProcessEvents();
//
//
//    // our SDL event loop
//    while (!done) {
//        drawBall();
//        // game loop
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//                done = true;
//            }
////            /*----------------------------------KEYBOARD-------------------------------------*/
////            else if(event.type == SDL_KEYDOWN) {
////                if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
////                    // DO AN ACTION WHEN SPACE IS PRESSED!
////                }
////            }
////            const Uint8 *keys = SDL_GetKeyboardState(NULL);
////            if(keys[SDL_SCANCODE_UP]) {
////                // go up!
////            } else if(keys[SDL_SCANCODE_DOWN]) {
////                // go down!
////            }
//
//            Update();
//            Render();
//        }
//        Cleanup();
//    }
//}
//
//void Entity::Draw() {
//    glTranslatef(x, y, 0.0);
//    glScalef(width, height, 0.0);
//    glRotatef(rotation, 0.0, 0.0, 0.0);
//    GLfloat quad[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
//    GLfloat quadColor[] =  {1.0, 1.0, 1.0, 1.0,
//                            1.0, 1.0, 1.0, 1.0,
//                            1.0, 1.0, 1.0, 1.0,
//                            1.0, 1.0, 1.0, 1.0};
//    glVertexPointer(2, GL_FLOAT, 0, quad);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glColorPointer(4, GL_FLOAT, 0, quadColor);
//    glEnableClientState(GL_COLOR_ARRAY);
//    glDrawArrays(GL_QUADS, 0, 4);
//}
//
//
//void Setup() {
//    // setup SDL
//    SDL_Init(SDL_INIT_VIDEO);
//    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1000, SDL_WINDOW_OPENGL);
//
//    // setup OpenGL
//    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
//    SDL_GL_MakeCurrent(displayWindow, context);
//
//    // Set our projection matrix
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glViewport(0, 0, 1200, 1000);
//    glMatrixMode(GL_PROJECTION);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void Update() {
//    // move stuff and check for collisions
//
//}
//void Render() {
//    // for all game elements
//    // setup transforms, render sprites
//}
//void Cleanup() {
//    // cleanup joysticks, textures, etc.
//    glClear(GL_COLOR_BUFFER_BIT);
//}




//void ProcessEvents() {
//
//    bool done = false;
//    SDL_Event event;
//
//    // our SDL event loop
//    while (!done) {
//        // check input events
////        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
//
//        // game loop
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//                done = true;
//            }
//            /*----------------------------------KEYBOARD-------------------------------------*/
//
//            //check code
//            const Uint8 *keys = SDL_GetKeyboardState(NULL);
//            if(keys[SDL_SCANCODE_LEFT]) {
//                // go left!
//            } else if(keys[SDL_SCANCODE_RIGHT]) {
//                // go right!
//            }
//            //----------
//            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
//                done = true;
//            } else if(event.type == SDL_KEYDOWN) {
//                if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
//                    // DO AN ACTION WHEN SPACE IS PRESSED!
//                }
//            }
//
//        }
//    }
//}

