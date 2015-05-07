//
//  clean collision.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 5/6/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <stdio.h>

void ClassDemoApp::Update(float elapsed) {
    int charge = 0;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            done = true;
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                if (entities[0].collidedBottom) {
                    //cause tremor
                    //update all entites
                    charge++;
                }
            }
        }
        if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                if (entities[0].collidedBottom) {
                    entities[0].direction_y = 1.0;
                }
            }
        }
    }
    for (size_t i = 1; i < entities.size(); i++) {
        if (entities[i].type == "Player" || entities[i].type == "Crate") {
            //Apply Gravity
//            entities[j].direction_y = -1.0;
//            if (!entities[j].collidedBottom) {
//                entities[j].direction_y = -1.0;
//            } else {entities[j].direction_y = 0.0;}
        }
        if (!entityCollision(entities[0], entities[i])) {
            if ((entities[j].type == "Saw1") || (entities[i].type == "Saw2") || (entities[i].type == "Saw3") || (entities[j].type == "Saw4")) {
                //Activate Game Over
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                entities[0].direction_x = 1.0;
//                if (target.collidedBottom && !target.collidedRight) {
//                    target.direction_x = 1.0;
//                }
            } else if (!keys[SDL_SCANCODE_RIGHT]) {
                entities[0].direction_x = 0.0;
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                entities[0].direction_x = -1.0;
//                if (target.collidedBottom && !target.collidedLeft) {
//                    target.direction_x = -1.0;
//                }
            } else if (!keys[SDL_SCANCODE_LEFT]) {
                entities[0].direction_x = 0.0;
            }
        }
        if ((entities[j].type == "Saw1") || (entities[j].type == "Saw2") || (entities[j].type == "Saw3") || (entities[j].type == "Saw4")) {
            entities[j].rotation -= elapsed*1000;
        }
        
        if (charge >=3) {
            //ADD SMALL SMOKE EFFECT
            if (entities[i].type == "Crate") {
                entities[i].direction_y = 1.0;
            }
            charge = 0;
        }
        if (3 < charge <= 6) {
            //ADD SMOKE EFFECT
            /*
             if (surface == earth) {
                //ACTIVATE DUST1
             }
             if (surface == pipe || surface == metal) {
             //ACTIVATE DUST4
             }
             if (surface == log) {
             //ACTIVATE DUST2
             }
             if (surface == sand) {
             //ACTIVATE DUST3
             }
             */
            if (entities[i].type == "Crate") {
                if (entities[0].x > entities[i].x) {
                    entities[i].direction_x = -1.0;
                    entities[i].direction_y = 1.0;
                }
                if (entities[0].x < entities[i].x) {
                    entities[i].direction_x = 1.0;
                    entities[i].direction_y = 1.0;
                }
                
            }
            if (entities[i].type == "Ice") {
                //Destory Ice
            }
            if ((entities[j].type == "Saw1") || (entities[j].type == "Saw2") || (entities[j].type == "Saw3") || (entities[j].type == "Saw4")) {
                entities[i].direction_y = 1.0;
            }
            charge = 0;
        }
        if (6 < charge <= 9) {
            //ADD SMOKE EFFECT
            /*
             if (surface == earth) {
             //ACTIVATE DUST1
             }
             if (surface == pipe || surface == metal) {
             //ACTIVATE DUST4
             }
             if (surface == log) {
             //ACTIVATE DUST2
             }
             if (surface == sand) {
             //ACTIVATE DUST3
             }
             */
            if (entities[i].type == "Crate") {
                if (entities[0].x > entities[i].x) {
                    entities[i].direction_x = -1.0;
                    entities[i].direction_y = 1.0;
                }
                if (entities[0].x < entities[i].x) {
                    entities[i].direction_x = 1.0;
                    entities[i].direction_y = 1.0;
                }
                
            }
            if (entities[i].type == "Ice") {
                if (entityCollision(entities[0], entities[i])) {
                    //Destory Ice
                }
            }
            if ((entities[j].type == "Saw1") || (entities[j].type == "Saw2") || (entities[j].type == "Saw3") || (entities[j].type == "Saw4")) {
                entities[i].direction_y = 1.0;
            }
            charge = 0;
            //Shake Screen
        }
        if (charge >= 10) {
            //ADD SMOKE EFFECT
            /*
             if (surface == earth) {
             //ACTIVATE DUST1
             }
             if (surface == pipe || surface == metal) {
             //ACTIVATE DUST4
             }
             if (surface == log) {
             //ACTIVATE DUST2
             }
             if (surface == sand) {
             //ACTIVATE DUST3
             }
             */
            if (entities[i].type == "Crate") {
                if (entities[0].x > entities[i].x) {
                    entities[i].direction_x = -1.0;
                    entities[i].direction_y = 1.0;
                }
                if (entities[0].x < entities[i].x) {
                    entities[i].direction_x = 1.0;
                    entities[i].direction_y = 1.0;
                }
                
            }
            if (entities[i].type == "Ice") {
                //Destory All Ice
            }
            if ((entities[j].type == "Saw1") || (entities[j].type == "Saw2") || (entities[j].type == "Saw3") || (entities[j].type == "Saw4")) {
                entities[i].direction_y = 1.0;
            }
            charge = 0;
            //Violently Shake Screen
        }
        entities[i].Update(elapsed);
    }
}
