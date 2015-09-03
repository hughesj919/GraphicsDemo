//
//  vertex.cpp
//  CS180Homework
//
//  Created by Jordan Hughes on 11/19/14.
//  Copyright (c) 2014 JHughes. All rights reserved.
//

#include "vertex.h"
vertex::vertex(float xC, float yC, float zC){
    x = xC;
    y = yC;
    z = zC;
}

vertex::vertex(){
    
}

float vertex::getX(){
    return x;
}
float vertex::getY(){
    return y;
}
float vertex::getZ(){
    return z;
}
void vertex::setX(float xC){
    x = xC;
}
void vertex::setY(float yC){
    y = yC;
}
void vertex::setZ(float zC){
    z = zC;
}

void vertex::translate(float x, float y, float z){
    
}