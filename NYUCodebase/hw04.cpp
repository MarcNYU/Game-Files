//
//  hw04.cpp
//  NYUCodebase
//
//  Created by Marcus Williams on 3/1/15.
//  Copyright (c) 2015 Ivan Safrin. All rights reserved.
//

#include <stdio.h>
#include "ClassDemoApp.h"
int main(int argc, char *argv[])
{
    ClassDemoApp app;
    while(!app.UpdateAndRender()) {}
    return 0;
}