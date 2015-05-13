#include "Entity.h"

Entity::Entity() {
	friction_x = 5.0f;
	friction_y = 0.0f;
	velocity_x = 0.0f;
	velocity_y = 0.0f;
	acceleration_x = 0.0f;
	gravity_y = -4.0f;
	enableCollisions = true;
	collidedBottom = false;
	collidedRight = false;
	collidedLeft = false;
	collidedTop = false;
	isStatic = true;
	textureID = NULL;

	animationElapsed = 0.0f;

	isVisible = false;
}

float lerp1(float v0, float v1, float t) {
	return (1.0 - t) * v0 + t * v1;
}
GLuint LoadTexture2(const char *image_path) {
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

void Entity::Update(float elapsed, const Uint8 *keys) {
    
	if (type == "player") {
		if (!keys[SDL_SCANCODE_RIGHT])
            direction_x = 0;
		if (!keys[SDL_SCANCODE_LEFT])
            direction_x = 0;

		if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_LEFT])
		{
			if (keys[SDL_SCANCODE_RIGHT]) {
				if (!collidedRight)
					acceleration_x = 5.0f;
                direction_x = 1;
				if (collidedRight && velocity_y < 0) {
					velocity_y = -0.35f;
					gravity_y = 0.0f;
				}
			}
			else
                direction_x = -1;

			if (keys[SDL_SCANCODE_LEFT]) {
				if (!collidedLeft)
					acceleration_x = -5.0f;
                direction_x = -1;
				
				if (collidedLeft && velocity_y < 0) {
					velocity_y = -0.35f;
					gravity_y = 0.0f;
				}
			}
			else
                direction_x = 1;
				
		}
		else {
			acceleration_x = 0.0f;
            direction_x = 0;
			
		}
        
	}
    if ((type == "Saw1") || (type == "Saw3")) {
        if (x <= 0.26) {
            velocity_x = 0.125;
        }
        if (x >= 0.45) {
            velocity_x = -0.125;
        }
    }
    if ((type == "Saw2")) {
        if (x <= 0.269) {
            velocity_x = 0.125;
        }
        if (x >= 0.45) {
            velocity_x = -0.125;
        }
    }
    if ((type == "Saw4")) {
        if (x <= 0.7) {
            velocity_x = 0.125;
        }
        if (x >= 0.8) {
            velocity_x = -0.125;
        }
    }
    
}

void Entity::Jump() {
	if (collidedBottom) {
		if (velocity_y > 0)
			y += 0.05;
		velocity_y = 1.2f;
		gravity_y = 0.0f;
	}
	else
		gravity_y = -4.0f;
	if (collidedRight && direction_x > 0 && velocity_y != 0.0f) {
		velocity_x = -2.0f;
		acceleration_x = 0.0f;
		velocity_y = 1.2f;
		collidedRight = false;
	}
	if (collidedLeft && direction_x < 0 && velocity_y != 0.0f) {
		velocity_x = 2.0f;
		acceleration_x = 0.0f;
		velocity_y = 1.2f;
		collidedLeft = false;
	}
	collidedBottom = false;
}


bool Entity::collidesWith(Entity other) {
    if (other.type == "Button") {
        if ((y-height/2 < other.y) && (x+width/2 > other.x-other.width/2) && (x-width/2 < other.x+other.width/2) && (y+height/2 > other.y-other.height/2)) {
            if (y > other.y) {
                if (other.velocity_y < 0) {
                    y = other.y + other.height;
                    velocity_y = other.velocity_y;
                    gravity_y = 0.0f;
                    collidedBottom = true;
                }
                else if (other.velocity_y > 0) {
                    y = other.y + other.height;
                    velocity_y = other.velocity_y;
                    gravity_y = 0.0f;
                    collidedBottom = true;
                }
            }
        }
    }
	if ((y-height/2 < other.y+other.height/2) && (x+width/2 > other.x-other.width/2) && (x-width/2 < other.x+other.width/2) && (y+height/2 > other.y-other.height/2)) {
		if (y > other.y) {
			if (other.velocity_y < 0) {
				y = other.y + other.height;
				velocity_y = other.velocity_y;
				gravity_y = 0.0f;
				collidedBottom = true;
			}
			else if (other.velocity_y > 0) {
				y = other.y + other.height;
				velocity_y = other.velocity_y;
				gravity_y = 0.0f;
				collidedBottom = true;
			}
		}
		else {
			collidedBottom = false;
			gravity_y = -4.0f;
		}
	}
    return false;
}

void Entity::Render(float elapsed) {
    if (type == "Player") {
        unsigned int playerID = LoadTexture2("beavor_sprites.png");
        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        const int runRight[] = {8, 9, 7, 9};
        const int runLeft[] = {6, 4, 5, 4};
        const int hitGroundLeft[] = {1, 2, 3, 2, 3, 2, 3, 2};
        const int hitGroundRight[] = {12, 11, 10, 11, 10, 11, 10, 11};
        animationElapsed += elapsed;
        if(animationElapsed > 1.0/framesPerSecond) {
            currentIndex++;
            idx++;
            animationElapsed = 0.0;
            if(currentIndex > numFrames-1) {
                currentIndex = 0;
            }
            if (idx > fixedFrames-1) {
                idx = 0;
            }
        }
        
        if(keys[SDL_SCANCODE_RIGHT]) {
            DrawSprite(playerID, runRight[currentIndex], 14.0, 1.0);
        } else if(keys[SDL_SCANCODE_LEFT]) {
            DrawSprite(playerID, runLeft[currentIndex], 14.0, 1.0);
        } else if(keys[SDL_SCANCODE_UP]) {
            if (direction_x < 0.0) {
                DrawSprite(playerID, 6, 14.0, 1.0);
            } else
                DrawSprite(playerID, 7, 14.0, 1.0);
        }else if(keys[SDL_SCANCODE_SPACE]) {
            if (direction_x < 0.0) {
                DrawSprite(playerID, hitGroundLeft[idx], 14.0, 1.0);
            } else
                DrawSprite(playerID, hitGroundRight[idx], 14.0, 1.0);
        } else {
            if (direction_x < 0.0) {
                DrawSprite(playerID, 0, 14.0, 1.0);
            } else
                DrawSprite(playerID, 13, 14.0, 1.0);
            
        }
    }
    if (type == "Crate" && x != 0 && y != 0) {
        DrawSprite(LoadTexture2("crate.png"), 0, 1.0, 1.0);
    }
    if (type == "Goal") {
        DrawSprite(LoadTexture2("waffle.png"), 0, 1.0, 1.0);
    }
    if (type == "Button"&& x != 0 && y != 0) {
        DrawSprite(LoadTexture2("button0.png"), 0, 1.0, 1.0);
    }
    if ((type == "Wall1"&& x != 0 && y != 0) || (type == "Wall2"&& x != 0 && y != 0)) {
        DrawSprite(LoadTexture2("log.png"), 0, 1.0, 1.0);
    }
    if ((type == "Saw1"&& x != 0 && y != 0) || (type == "Saw2"&& x != 0 && y != 0) || (type == "Saw3"&& x != 0 && y != 0) || (type == "Saw3"&& x != 0 && y != 0) ||
        (type == "Saw4"&& x != 0 && y != 0)) {
        DrawSprite(LoadTexture2("saw.png"), 0, 1.0, 1.0);
    }
}
void Entity::DrawSprite(int spriteTexture, int index, int spriteCountX, int spriteCountY) {
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spriteTexture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    //HACK NOTE
    //HARDCODED X and Y OFFSET
    if ((type == "Saw1") || (type == "Saw2") || (type == "Saw3") || (type == "Saw4")) {
        glTranslatef(x-0.475, y+0.535, 0.0);
    } else {
        glTranslatef(x-0.475, y+0.525, 0.0);
        
    }
    glScalef(width, height, 1.0);
    glRotatef(rotation, 0.0, 0.0, 1.0);
    
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
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    
}