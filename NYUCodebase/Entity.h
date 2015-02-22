//
//  Entity.h
//  NYUCodebase
//
//  Created by Marcus Williams on 2/20/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#ifndef NYUCodebase_Entity_h
#define NYUCodebase_Entity_h

class Entity {
public:
    Entity (int texture, float xCord, float yCord, float w, float h, float spd) : x(xCord), y(yCord), rotation(0.0), textureID(texture), width(w), height(h), speed(spd), direction_x(0.0), direction_y(0.0){}
    void Draw();
    float x;
    float y;
    float rotation;
    int textureID;
    float width;
    float height;
    float speed;
    float direction_x;
    float direction_y;
};


#endif
