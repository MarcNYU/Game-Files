
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
void Setup();
void Cleanup();

int main()
{
    
    bool done = false;
    SDL_Event event;
    
    Setup();
    
    
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
            
        }
        SDL_GL_SwapWindow(displayWindow);
        
        float lastFrameTicks = 0.0f;
        
        float ticks = (float)SDL_GetTicks()/10.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        float position = 0.0;
        position += elapsed;
    }
    
    Cleanup();
    SDL_Quit();
    return 0;
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

void Cleanup() {
    // cleanup joysticks, textures, etc.
    glClear(GL_COLOR_BUFFER_BIT);
}





