#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6

class Entity {
public:
	Entity();

	void Update(float elapsed, const Uint8 *keys);
	void Render(float elapsed);

	bool collidesWith(Entity entity);

	float x;
	float y;
    
    float initial_x;
    float initial_y;

	float width;
	float height;
    int direction_x;
	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;
	float friction_x;
	float friction_y;
	float gravity_y;
	float mass;
	bool isStatic;
    
    float rotation;

	std::string type;

	bool enableCollisions;
	bool isVisible;

	void Jump();

	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
	bool collidedTop;

	void DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY);

	unsigned int textureID;

	int numFrames;
    int fixedFrames;
    int currentIndex;
    int idx;
	int spriteNum;
	float animationElapsed;
	float framesPerSecond;
};

#endif