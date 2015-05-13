#include "ClassDemoApp.h"
#include "Entity.h"
#include <time.h>
#include <vector>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define LEVEL_HEIGHT 20
#define LEVEL_WIDTH 20
#define TILE_SIZE 0.05f
#define SPRITE_COUNT_X 10
#define SPRITE_COUNT_Y 7

float timeLeftOver = 0.0f;

GLuint LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);
	return textureID;
}
float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax);
float easeIn(float from, float to, float time);
float easeOut(float from, float to, float time);
float easeInOut(float from, float to, float time);
float easeOutElastic(float from, float to, float time);
int worldToTileCoordX(float x);

int worldToTileCoordY(float y);

float lerp2(float v0, float v1, float t);


ClassDemoApp::ClassDemoApp() {
	Init();
	Reinitialize();
	clock = 0;
	gameState = 0;
	done = false;
	lastFrameTicks = 0.0f;

	screenShakeValue = 0.0f;
	screenShakeSpeed = 50.0f;
}

ClassDemoApp::~ClassDemoApp() {
	Mix_FreeMusic(maintheme);
	SDL_Quit();
}
void ClassDemoApp::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);
//    glOrtho(-0.83, 0.83, -0.5, 0.5, -0.5, 0.5);
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    maintheme = Mix_LoadMUS("video marc.mp3");
    
    jump = Mix_LoadWAV("jump.wav");
    quake = Mix_LoadWAV("smash.wav");
    
    
    player.numFrames = 4;
    player.fixedFrames = 8;
    player.framesPerSecond = 3.0;
    player.idx = 0;
    player.animationElapsed = 0.0f;
    player.type = "Player";
    player.width = 0.05;
    player.height = 0.05;
    
    Entity goal;
    goal.type = "Goal";
    goal.width = 0.05;
    goal.height = 0.05;
    
    Entity crate;
    crate.type = "Crate";
    crate.width = 0.05;
    crate.height = 0.05;
    
    Entity button;
    button.type = "Button";
    button.width = 0.05;
    button.height = 0.05;
    
    int num = 0;
    int wallTotal = 2;
    while (num < wallTotal) {
        Entity wall;
        wall.width = 0.05;
        wall.height = 0.05;
        std::string str = std::to_string(num+1);
        wall.type = "Wall"+str;
        entities.push_back(wall);
        num++;
    }
    num = 0;
    int sawTotal = 4;
    while (num < sawTotal) {
        Entity saw;
        saw.width = 0.05;
        saw.height = 0.05;
        std::string str = std::to_string(num+1);
        saw.type = "Saw"+str;
        entities.push_back(saw);
        num++;
    }
    num = 0;
    entities.push_back(goal);
    entities.push_back(crate);
    entities.push_back(button);
}

void ClassDemoApp::Reinitialize() {
    Mix_PlayMusic(maintheme, 1);
    texture = LoadTexture("pixel_sprites_sheet.png");
    
    text.font = LoadTexture("font1.txt");
    text.size = 0.125;
    text.spacing = -0.060;
    text.r = 0.0;
    text.g = 1.0;
    text.b = 0.0;
    text.a = 1.0;
    
}
void ClassDemoApp::Render(float elapsed) {
    glClearColor(0.0f, 0.59f, 0.74f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    if (gameState == 0) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, LoadTexture("tremor.png"));
        
        glMatrixMode(GL_MODELVIEW);
        
        glLoadIdentity();
        glScalef(2.0, 2.0, 2.0);
        
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
    if (gameState == 1) {
        text.size = 0.1;
        text.r = 1.0f;
        text.g = 1.0f;
        text.b = 1.0f;
        text.spacing = -0.055;
        glLoadIdentity();
        text.Draw("Controls:", -1.2, 0.8);
        text.Draw("UP Arrow: Jump", -1.2, 0.6);
        text.Draw("LEFT Arrow: Left", -1.2, 0.5);
        text.Draw("RIGHT Arrow: Right", -1.2, 0.4);
        text.Draw("Z: Magenitude 5", -1.2, 0.3);
        text.Draw("X: Magenitude 10", -1.2, 0.2);
        text.Draw("Press SPACE to start", -1.2, -0.4);
        text.Draw("Press ESCAPE to exit", -1.2, -0.5);
    }
    if (gameState > 1) {
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_Z]) {
            if (clock > 5) {
                screenShakeIntensity += elapsed;
                if (screenShakeIntensity < 0.5)
                    screenShakeIntensity = easeInOut(-1.33, 0.5, screenShakeIntensity);
                else
                    screenShakeIntensity = 0.0f;
            }
            glTranslatef(sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, 0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            player.Render(elapsed);
            for (Entity obj : entities)
                obj.Render(elapsed);

        } else if (keys[SDL_SCANCODE_X]) {
            if (clock > 5) {
                screenShakeIntensity += elapsed;
                if (screenShakeIntensity < 1.5)
                    screenShakeIntensity = easeInOut(-1.33, 0.5, screenShakeIntensity);
                else
                    screenShakeIntensity = 0.0f;
            }
            glTranslatef(sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity, 0.0f, sin(screenShakeValue * screenShakeSpeed) * screenShakeIntensity);
            drawLevel();
            player.Render(elapsed);
            for (Entity obj : entities)
                obj.Render(elapsed);
        } else {
            drawLevel();
            player.Render(elapsed);
            for (Entity obj : entities)
                obj.Render(elapsed);
        }
    }
    
    glPopMatrix();
    
    SDL_GL_SwapWindow(displayWindow);
}
void ClassDemoApp::Update(float elapsed) {
    
    SDL_Event event;
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
    }
    
    if (gameState == 0) {
        if (keys[SDL_SCANCODE_RETURN] || keys[SDL_SCANCODE_RETURN2])
            gameState = 1;
    }
    
    if (gameState == 1) {
        if (keys[SDL_SCANCODE_SPACE]) {
            BuildLevelData(0);
            gameState = 2;
        }
        if (keys[SDL_SCANCODE_ESCAPE])
            done = true;
    }
    if (gameState > 1) {
        if (keys[SDL_SCANCODE_ESCAPE])
            done = true;
        player.Update(elapsed, keys);
        if (keys[SDL_SCANCODE_UP])
            Mix_PlayChannel(-1, jump, 0);
            player.Jump();
        for (Entity obj : entities) {
            if (obj.type == "Saw1" || obj.type == "Saw2" || obj.type == "Saw3" || obj.type == "Saw4") {
                obj.rotation -= elapsed*1000;
            }
            obj.Update(elapsed, keys);
        }
        if (keys[SDL_SCANCODE_Z]) {
            Mix_PlayChannel(-1, quake, 0);
            for (Entity obj : entities) {
                if (obj.type == "Crate") {
                    if (obj.y < player.y) {
                        obj.acceleration_x = -1.0;
                        obj.Jump();
                    } else if (obj.y > player.y) {
                        obj.acceleration_x = 1.0;
                        obj.Jump();
                    }
                    obj.acceleration_x = 0.0;
                }
                if (obj.type == "Saw1" || obj.type == "Saw2" || obj.type == "Saw3" || obj.type == "Saw4") {
                    obj.acceleration_x = 0.0;
                    obj.Jump();
                }
            }
        }
        if (keys[SDL_SCANCODE_X]) {
            Mix_PlayChannel(-1, quake, 0);
            for (Entity obj : entities) {
                if (obj.type == "Crate") {
                    if (obj.y < player.y) {
                        obj.acceleration_x = -3.0;
                        obj.Jump();
                    } else if (obj.y > player.y) {
                        obj.acceleration_x = 3.0;
                        obj.Jump();
                    }
                    obj.acceleration_x = 0.0;
                }
                if (obj.type == "Saw1" || obj.type == "Saw2" || obj.type == "Saw3" || obj.type == "Saw4") {
                    obj.acceleration_x = 0.0;
                    obj.Jump();
                }
            }
        }
    }
}

bool ClassDemoApp::UpdateAndRender() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;
    screenShakeValue += elapsed;
    
    float fixedElapsed = elapsed + timeLeftOver;
    if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
        fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
    }
    
    while (fixedElapsed >= FIXED_TIMESTEP) {
        fixedElapsed -= FIXED_TIMESTEP;
        FixedUpdate();
        clock++;
    }
    timeLeftOver = fixedElapsed;
    
    Update(elapsed);
    Render(elapsed);
    return done;
}

void ClassDemoApp::Reset() {
    gameState = 0;
    clock = 0;
    done = false;
    lastFrameTicks = 0.0f;
    
    player.x = 0.0;
    player.y = 0.0;
    delete levelData;
    entities.clear();
    
    Reinitialize();
}
void ClassDemoApp::FixedUpdate() {
    screenShakeIntensity = lerp2(screenShakeIntensity, 0.0f, FIXED_TIMESTEP);
    if (screenShakeIntensity < 0.01f)
        screenShakeIntensity = 0.0f;
    
    if (gameState == 2 || gameState == 6 || gameState == 9) {
        AxisCollision_Y(player);
        AxisCollision_X(player);
        
        for (Entity obj : entities) {
            if (obj.type == "Saw1" || obj.type == "Saw2" || obj.type == "Saw3" || obj.type == "Saw4") {
                if (player.collidesWith(obj)) {
                    
                    player.x = player.initial_x;
                    player.y = player.initial_y;
                }
            }
            if (obj.type == "Goal") {
                gameState +=1;
            }
            if (obj.type == "Button") {
                player.collidesWith(obj);
                AxisCollision_Y(obj);
                if (obj.collidedTop) {
                    for (size_t i=0; i < entities.size(); i++) {
                        if ((entities[i].type == "Wall1") || (entities[0].type == "Wall1")) {
                            Entity blank;
                            entities[i] = blank;
                        }
                    }
                }
                for (Entity crate : entities) {
                    if (crate.type == "Crate") {
                        crate.collidesWith(obj);
                        AxisCollision_Y(obj);
                        if (obj.collidedTop) {
                            for (size_t i=0; i < entities.size(); i++) {
                                if ((entities[i].type == "Wall1") || (entities[0].type == "Wall1")) {
                                    Entity blank;
                                    entities[i] = blank;
                                }
                            }
                        }
                    }
                }
            }
            if (obj.type == "Crate") {
                player.collidesWith(obj);
                AxisCollision_Y(obj);
            }
            if ((obj.type == "Wall1") || (obj.type == "Wall1")){
                player.collidesWith(obj);
                AxisCollision_Y(obj);
            }
        }
    }
}
bool ClassDemoApp::AxisCollision_X(Entity e) {
    float tileBottom = e.y - e.height * TILE_SIZE;
    float tileTop = e.y + e.height * TILE_SIZE;
    float tileLeft = e.x - e.width * TILE_SIZE * 4;
    float tileRight = e.x + e.width * TILE_SIZE * 4;
    
    if (e.velocity_x < 0) {
        if ((levelData[worldToTileCoordY(tileBottom)][worldToTileCoordX(tileLeft)]) ||
            (levelData[worldToTileCoordY(tileTop)][worldToTileCoordX(tileLeft)])) {
            e.collidedLeft = true;
            e.x -= FIXED_TIMESTEP * e.velocity_x;
            e.velocity_x = 0.0f;
            e.acceleration_x = 0.0f;
        }
    }
    else if (e.velocity_x > 0) {
        if ((levelData[worldToTileCoordY(tileBottom)][worldToTileCoordX(tileRight)]) ||
            (levelData[worldToTileCoordY(tileTop)][worldToTileCoordX(tileRight)])) {
            e.collidedRight = true;
            e.x -= FIXED_TIMESTEP * e.velocity_x;
            e.velocity_x = 0.0f;
            e.acceleration_x = 0.0f;
        }
    }
    else {
        e.collidedLeft = false;
        e.collidedRight = false;
    }
    return (e.collidedLeft || e.collidedRight);
}

bool ClassDemoApp::AxisCollision_Y(Entity e) {
    float tileBottom = e.y - e.height * TILE_SIZE * 4;
    float tileTop = e.y + e.height * TILE_SIZE * 4;
    float tileLeft = e.x - e.width * TILE_SIZE;
    float tileRight = e.x + e.width * TILE_SIZE;
    
    if (e.velocity_y < 0){
        if ((levelData[worldToTileCoordY(tileBottom)][worldToTileCoordX(tileRight)]) ||
            (levelData[worldToTileCoordY(tileBottom)][worldToTileCoordX(tileLeft)])) {
            e.collidedBottom = true;
            e.y -= FIXED_TIMESTEP * e.velocity_y;
            e.velocity_y = 0.0f;
            e.acceleration_y = 0.0f;
        }
    }
    else if (e.velocity_y > 0 && !e.collidedTop){
        if ((levelData[worldToTileCoordY(tileTop)][worldToTileCoordX(tileRight)]) ||
            (levelData[worldToTileCoordY(tileTop)][worldToTileCoordX(tileLeft)])) {
            e.collidedTop = true;
            e.y -= FIXED_TIMESTEP * e.velocity_y;
            e.velocity_y = 0.0f;
            e.acceleration_y = -4.0f;
        }
    }
    else {
        e.collidedTop = false;
        e.collidedBottom = false;
    }
    return (e.collidedTop || e.collidedBottom);
}
void ClassDemoApp::ReadFile(std::string levelFile){
    std::ifstream infile(levelFile);
    std::string line;
    while (getline(infile, line)) {
        if(line == "[header]") {
            if(!ReadHeader(infile)) {
                return;
            }
        } else if(line == "[layer]") {
            ReadLayerData(infile);
        } else if(line == "[Player]" || line == "[Goal]" || line == "[Crate]" || line == "[Button]" || line == "[Wall1]" || line == "[Wall2]" || line == "[Saw1]" || line == "[Saw2]" || line == "[Saw3]" || line == "[Saw4]") {
            ReadEntityData(infile);
        }
    }
    infile.close();
}
bool ClassDemoApp::ReadHeader(std::ifstream &stream) {
	string line;
	mapWidth = -1;
	mapHeight = -1;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "width") {
			mapWidth = atoi(value.c_str());
		}
		else if (key == "height"){
			mapHeight = atoi(value.c_str());
		}
	}
	if (mapWidth == -1 || mapHeight == -1) {
		return false;
	}
	else {
		levelData = new unsigned char*[mapHeight];
		for (int i = 0; i < mapHeight; ++i) {
			levelData[i] = new unsigned char[mapWidth];
		}
		return true;
	}
}

bool ClassDemoApp::ReadLayerData(std::ifstream &stream) {
	string line;
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "data") {
			for (int y = 0; y < mapHeight; y++) {
				getline(stream, line);
				istringstream lineStream(line);
				string tile;

				for (int x = 0; x < mapWidth; x++) {
					getline(lineStream, tile, ',');
					unsigned char val = (unsigned char)atoi(tile.c_str());
					if (val > 0) {
						levelData[y][x] = val;
					}
					else {
						levelData[y][x] = 0;
					}
				}
			}
		}
	}
	return true;
}

void ClassDemoApp::PlaceEntity(string type, float placeX, float placeY) {
	if (type == "Player") {
		player.x = placeX;
		player.y = placeY;
	}
    for (size_t i = 0; i < entities.size(); i++) {
        if (entities[i].type == type) {
            entities[i].x = placeX;
            entities[i].y = placeY;
        }
    }
}

bool ClassDemoApp::ReadEntityData(std::ifstream &stream) {
	string line;
	string type;
		
	while (getline(stream, line)) {
		if (line == "") { break; }
		istringstream sStream(line);
		string key, value;
		getline(sStream, key, '=');
		getline(sStream, value);
		if (key == "type") {
			type = value;
		}
		else if (key == "location") {

			istringstream lineStream(value);
			string xPosition, yPosition;
			getline(lineStream, xPosition, ',');
			getline(lineStream, yPosition, ',');

			float placeX = atoi(xPosition.c_str())* TILE_SIZE;
			float placeY = atoi(yPosition.c_str())* -TILE_SIZE;

			PlaceEntity(type, placeX, placeY);
		}
	}
	return true;
}

void ClassDemoApp::BuildLevelData(int level) {
	if (level == 0) {
        ReadFile("NYUCodebase.app/Contents/Resources/new_level6txt");
	}
	if (level == 1) {
		ReadFile("NYUCodebase.app/Contents/Resources/level2_new.txt");
	}
	if (level == 2) {
        ReadFile("NYUCodebase.app/Contents/Resources/level1_new.txt");
	}
    if (level == 3) {
        ReadFile("NYUCodebase.app/Contents/Resources/new_level7.txt");
    }
    if (level == 4) {
        ReadFile("NYUCodebase.app/Contents/Resources/new_level8.txt");
    }
    if (level == 5) {
        ReadFile("NYUCodebase.app/Contents/Resources/level4_new.txt");
    }
//    if (level == 6) {
//        readFile("NYUCodebase.app/Contents/Resources/level3_new.txt");
//    }
}

void ClassDemoApp::drawLevel() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	vector<float> vertexData;
	vector<float> texCoordData;
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
            
//            //HACK NOTE
//            Entity hitBox;
//            hitBox.type = "HitBox";
//            hitBox.x = TILE_SIZE * x;
//            hitBox.y = (-TILE_SIZE * y)-TILE_SIZE;
//            hitBox.width = 0.05;
//            hitBox.height = 0.05;
//            collisionBoxes.push_back(hitBox);
            
			if (levelData[y][x]) {
				float u = (float)(((int)levelData[y][x] - 1) % SPRITE_COUNT_X) / (float)SPRITE_COUNT_X;
				float v = (float)(((int)levelData[y][x] - 1) / SPRITE_COUNT_X) / (float)SPRITE_COUNT_Y;
				float spriteWidth = 1.0f / (float)SPRITE_COUNT_X;
				float spriteHeight = 1.0f / (float)SPRITE_COUNT_Y;
				vertexData.insert(vertexData.end(), {
					TILE_SIZE * x, -TILE_SIZE * y,
					TILE_SIZE * x, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, (-TILE_SIZE * y) - TILE_SIZE,
					(TILE_SIZE * x) + TILE_SIZE, -TILE_SIZE * y
				});
				texCoordData.insert(texCoordData.end(), { u, v,
					u, v + (spriteHeight),
					u + spriteWidth, v + (spriteHeight),
					u + spriteWidth, v
				});
			}
		}
	}
    glLoadIdentity();
    glTranslatef(-TILE_SIZE * LEVEL_WIDTH/2, TILE_SIZE * LEVEL_HEIGHT/2, 0.0f);
    
	glVertexPointer(2, GL_FLOAT, 0, vertexData.data());
	glEnableClientState(GL_VERTEX_ARRAY);
    
	glTexCoordPointer(2, GL_FLOAT, 0, texCoordData.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
	glDrawArrays(GL_QUADS, 0, vertexData.size() / 2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}




int worldToTileCoordX(float x) {
    int cordX = (int)(x / TILE_SIZE);
    if (cordX > LEVEL_WIDTH)
        cordX = LEVEL_WIDTH;
    if (cordX < 0)
        cordX = 0;
    return cordX;
}

int worldToTileCoordY(float y) {
    int cordY = (int)(-y / TILE_SIZE);
    if (cordY > LEVEL_HEIGHT)
        cordY = LEVEL_HEIGHT;
    if (cordY < 0)
        cordY = 0;
    return cordY;
}

float lerp2(float v0, float v1, float t) {
    return (1.0 - t) * v0 + t * v1;
}


float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
    float retVal = dstMin + ((value - srcMin) / (srcMax - srcMin) * (dstMax - dstMin));
    if (retVal < dstMin) {
        retVal = dstMin;
    }
    if (retVal > dstMax) {
        retVal = dstMax;
    }
    return retVal;
}

float easeIn(float from, float to, float time) {
    float tVal = time*time*time*time*time;
    return (1.0f - tVal)*from + tVal*to;
}

float easeOut(float from, float to, float time) {
    float oneMinusT = 1.0f - time;
    float tVal = 1.0f - (oneMinusT * oneMinusT * oneMinusT *
                         oneMinusT * oneMinusT);
    return (1.0f - tVal)*from + tVal*to;
}

float easeInOut(float from, float to, float time) {
    float tVal;
    if (time > 0.5) {
        float oneMinusT = 1.0f - ((0.5f - time)*-2.0f);
        tVal = 1.0f - ((oneMinusT * oneMinusT * oneMinusT * oneMinusT *
                        oneMinusT) * 0.5f);
    }
    else {
        time *= 2.0;
        tVal = (time*time*time*time*time) / 2.0;
    }
    return (1.0f - tVal)*from + tVal*to;
}

float easeOutElastic(float from, float to, float time) {
    float p = 0.3f;
    float s = p / 4.0f;
    float diff = (to - from);
    return from + diff + (diff*pow(2.0f, -10.0f*time) * sin((time - s)*(2 * M_PI) / p));
}