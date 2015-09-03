//
//  vertex.h
//  CS180Homework
//
//  Created by Jordan Hughes on 11/19/14.
//  Copyright (c) 2014 JHughes. All rights reserved.
//

#ifndef __CS180Homework__vertex__
#define __CS180Homework__vertex__

#include <stdio.h>

#endif /* defined(__CS180Homework__vertex__) */
class vertex{
private:
    float x;
    float y;
    float z;
    
public:
    vertex(float xC, float yC, float zC);
    vertex();
    float getX();
    float getY();
    float getZ();
    
    void setX(float xC);
    void setY(float yC);
    void setZ(float zC);
    void translate(float x, float y, float z);
};
