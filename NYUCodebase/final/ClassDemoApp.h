#ifndef CLASSDEMOAPP_H
#define CLASSDEMOAPP_H

#include <vector>
#include <string>
#include <time.h>
#include "Entity.h"
#include "Text.h"

class ClassDemoApp {
public:

	ClassDemoApp();
	~ClassDemoApp();

	void BuildLevelData(int level);
    void ReadFile(std::string levelFile);
	bool ReadHeader(ifstream &stream);
	bool ReadLayerData(ifstream &stream);
	bool ReadEntityData(ifstream &stream);
	void drawLevel();
	void PlaceEntity(string type, float placeX, float placeY);
	
	void Init();
	void Reinitialize();
	bool UpdateAndRender();

	bool AxisCollision_X(Entity e);
	bool AxisCollision_Y(Entity e);
	void FixedUpdate();

	void Render(float elapsed);
	void Update(float elapsed);

	void Reset();

private:
	Entity player;
	vector<Entity> entities;

	float screenShakeValue;
	float screenShakeSpeed;
	float screenShakeIntensity;

	Text text;
	int clock;

	int mapHeight;
	int mapWidth;
	unsigned char** levelData;
	GLuint texture;

	float titleAnimationValue;

	int gameState;
	bool done;
	float lastFrameTicks;
	SDL_Window* displayWindow;

	Mix_Music* maintheme;

	Mix_Chunk* jump;
	Mix_Chunk* quake;
};

#endif