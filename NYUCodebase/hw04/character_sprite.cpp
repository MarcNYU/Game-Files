//
//  hw04.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 3/1/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>

SDL_Window* displayWindow;

class SheetSprite {
public:
    SheetSprite(int textureID, float u, float v, float width, float height) : textureID(textureID), u(u), v(v), width(width), height(height) {}
    
    void Draw(float scale) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        GLfloat quad[] = {-width * scale , height * scale, -width * scale, -height * scale,
            width * scale, -height * scale, width * scale, height * scale};
        GLfloat quadUVs[] = {u, v, u, v+height, u+width, v+height, u+width, v};
        // draw arrays
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
    

    Entity (int texture, float x, float y, float w, float h) : texture(texture), x(x), y(y), width(w), height(h), velocity_x (0.0), velocity_y(0.0), acceleration_x(0.0), acceleration_y(0.0), friction_x(0.0), friction_y(0.0), mass(1.0){}
    
    void Update(float elapsed);
    void Render();
    
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
    
    int texture;
    
    float x;
    float y;
    
    float width;
    float height;
    
    float velocity_x;
    float velocity_y;
    float acceleration_x;
    float acceleration_y;
    float friction_x;
    float friction_y;
    float mass;
    bool isStatic;
    
    bool enableCollisions;
    
    bool collidedTop;
    bool collidedBottom;
    bool collidedLeft;
    bool collidedRight;
    
    
};

GLuint LoadTexture(const char *image_path);

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    bool done = false;
    
    SDL_Event event;
    
    std::vector<SheetSprite> playerAnimations;
    Entity player(LoadTexture("beck_sprites.png"), 0.0, 0.0, 1.0, 1.0);
    SheetSprite character = player.makeSprite(160.0, 0.0, 24.0,28.0);
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        character.Draw(1.0);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surface);
    return textureID;
}
