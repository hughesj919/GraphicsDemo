//
//  main.cpp
//  CS180Homework
//
//  Created by Jordan Hughes on 10/12/14.
//  Copyright (c) 2014 JHughes. All rights reserved.
//


#ifdef __APPLE__      //unix
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32     //windows
#include <windows.h>
#endif
#include <GL/gl.h> // linux
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include "soil.h"
#include <vector>
#include "vertex.h"

using namespace std;


#define PI 3.14159265

int width = 1920;
int height = 1080;
int windowX = 200;
int windowY = 200;
int faceCounter = 0;
bool axisOn = false;
bool drawCubes = true;
bool lightsOn = true;
bool drawNumbers = true;
bool buildMode = false;
bool backgroundOn = true;
int rotationOffset = 0;
int rotationOffset2 = 0;
int priorMouseX = 0;
int priorMouseY = 0;
float theta = 45.0;
float theta2 = 85.0;
float up = 1.0;
float zeroOffset = 0;
float oneOffset = -5.0;
float twoOffset = -10.0;
float threeOffset = -15.0;
float fourOffset = -20.0;
float fiveOffset = -25.0;
float sixOffset = -30.0;
float sevenOffset = -35.0;
float eightOffset = -40.0;
float nineOffset = -45.0;
float tenOffset = -50.0;

float lightX = 7.0;
float lightY = 20.0;
float lightZ = 7.0;
char* imgData;
GLuint tex;

vector<vertex> top;
float floorY = -.25;


vector<vertex> drawCircle3dShadow(float radius, float depth, float thickness, int numLoops, vector<vertex> points){
    for(int i=0;i<=numLoops;i++){
        points.push_back(vertex((thickness+radius)*cos((i*18) * (PI / 180.0)) , (thickness+radius)*sin((i*18) * (PI / 180.0)), 0.0f));
        points.push_back(vertex(radius*cos((i*18) * (PI / 180.0)) , radius*sin((i*18) * (PI / 180.0)), 0.0f));
    }
    return points;
}

void drawCircle3d(float radius, float depth, float thickness, int numLoops)
{
    glBegin(GL_QUAD_STRIP);
    glColor3d(0, 0, 1);
    for(int i=0;i<=numLoops;i++){
        glNormal3f(cos((i*18)* (PI / 180.0)),sin((i*18) * (PI / 180.0)),0);
        glVertex3f(radius*cos((i*18) * (PI / 180.0)) , radius*sin((i*18) * (PI / 180.0)), -depth);
        glNormal3f(cos((i*18)* (PI / 180.0)),sin((i*18) * (PI / 180.0)),0);
        glVertex3f(radius*cos((i*18) * (PI / 180.0)) , radius*sin((i*18) * (PI / 180.0)), 0.0f);
    }
    glEnd();
    
   glBegin(GL_QUAD_STRIP);
    for(int i=0;i<=numLoops;i++){
        glNormal3f(cos((i*18)* (PI / 180.0)),sin((i*18) * (PI / 180.0)),-depth);
        glVertex3f((thickness+radius)*cos((i*18) * (PI / 180.0)) , (thickness+radius)*sin((i*18) * (PI / 180.0)), -depth);
        glNormal3f(cos((i*18)* (PI / 180.0)),sin((i*18) * (PI / 180.0)),0);
        glVertex3f((thickness+radius)*cos((i*18) * (PI / 180.0)) , (thickness+radius)*sin((i*18) * (PI / 180.0)), 0.0f);
    }
    glEnd();
    
    glNormal3f(0, 0, -1);
    glBegin(GL_QUAD_STRIP);
    glColor3d(1, 0, 0);
    for(int i=0;i<=numLoops;i++){
        glVertex3f((thickness+radius)*cos((i*18) * (PI / 180.0)) , (thickness+radius)*sin((i*18) * (PI / 180.0)), -depth);
        glVertex3f(radius*cos((i*18) * (PI / 180.0)) , radius*sin((i*18) * (PI / 180.0)), -depth);
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    glColor3d(0, 1, 0);
    glNormal3f(0, 0, 1);
    for(int i=0;i<=numLoops;i++){
        glVertex3f((thickness+radius)*cos((i*18) * (PI / 180.0)) , (thickness+radius)*sin((i*18) * (PI / 180.0)), 0.0f);
        glVertex3f(radius*cos((i*18) * (PI / 180.0)) , radius*sin((i*18) * (PI / 180.0)), 0.0f);
    }
    glEnd();
}

vector<vertex> drawRectangleShadow(float width, float height, vector<vertex> points){
    points.push_back(vertex(0.0f,height,0.0f));
    points.push_back(vertex(0.0f,0.0f,0.0f));
    points.push_back(vertex(width,0.0f,0.0f));
    points.push_back(vertex(width,height,0.0f));
    return points;
}

void drawRectangle3d(float width, float height, float depth)
{
    
    glBegin(GL_QUADS);
    
    glColor3d(1, 0, 0);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f( 0.0f, height, 0.0f); //vertex 1
    glVertex3f( 0.0f, 0.0f, 0.0f); //vertex 2
    glVertex3f(width, 0.0f, 0.0f); //vertex 3
    glVertex3f( width, height, 0.0f); //vertex 4
    
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f( 0.0f, height, -1.0*depth); //vertex 1
    glVertex3f( 0.0f, 0.0f, -1.0*depth); //vertex 2
    glVertex3f( width, 0.0f, -1.0*depth); //vertex 3
    glVertex3f( width, height, -1.0*depth); //vertex 4
    
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f( 0.0f, height, -1.0*depth); //vertex 1
    glVertex3f( 0.0f, 0.0f, -1.0*depth); //vertex 2
    glVertex3f( 0.0f, 0.0f, 0.0f); //vertex 3
    glVertex3f( 0.0f, height, 0.0f); //vertex 4
    
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( width, height, -1.0*depth); //vertex 1
    glVertex3f( width, 0.0f, -1.0*depth); //vertex 2
    glVertex3f( width, 0.0f, 0.0f); //vertex 3
    glVertex3f( width, height, 0.0f); //vertex 4
    
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 0.0f, height, -1.0*depth); //vertex 1
    glVertex3f( 0.0f, height, 0.0f); //vertex 2
    glVertex3f( width, height, 0.0f); //vertex 2
    glVertex3f( width, height, -1.0*depth); //vertex 1
    
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f( 0.0f, 0.0f, -1.0*depth); //vertex 1
    glVertex3f( 0.0f, 0.0f, 0.0f); //vertex 2
    glVertex3f( width, 0.0f, 0.0f); //vertex 2
    glVertex3f( width, 0.0f, -1.0*depth); //vertex 1
    
    glEnd();
    
}

void drawTriangle(float depth)
{
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glColor3d(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    
    glNormal3f(0, 0, -1);
    glVertex3f(0.0f, 0.0f, -depth);
    glVertex3f(0.5f, 1.0f, -depth);
    glVertex3f(1.0f, 0.0f, -depth);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3d(1, 1, 0);
    glNormal3f(0, -1, 0);
    glVertex3f(0.0f, 0.0f, -depth);
    glVertex3f(1.0f, 0.0f, -depth);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    
    glNormal3f(-1,2, 0);
    glVertex3f(0.0f, 0.0f, -depth);
    glVertex3f(0.5f, 1.0f, -depth);
    glVertex3f(0.5f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    
    glNormal3f(2,1,0);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, 1.0f, 0.0f);
    glVertex3f(0.5f, 1.0f, -depth);
    glVertex3f(1.0f, 0.0f, -depth);
    
    glEnd();
}

void drawPentagon(float depth)
{
    glBegin(GL_POLYGON);
    glColor3d(1, 0, 0);
    glNormal3f(0, 0, 1);
    glVertex3f(0.25f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.25f, 1.0f, 0.0f);
    glVertex3f(0.75f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.75f, 0.0f, 0.0f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3d(1, 0, 0);
    glNormal3f(0, 0, -1);
    glVertex3f(0.25f, 0.0f, -depth);
    glVertex3f(0.0f, 0.5f, -depth);
    glVertex3f(0.25f, 1.0f, -depth);
    glVertex3f(0.75f, 1.0f, -depth);
    glVertex3f(1.0f, 0.5f, -depth);
    glVertex3f(0.75f, 0.0f, -depth);
    glEnd();
    
    glColor3d(1, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(0.25f, 0.0f, 0.0f);
    glVertex3f(0.25f, 0.0f, -depth);
    glVertex3f(0.75f, 0.0f, -depth);
    glVertex3f(0.75f, 0.0f, 0.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(0.25f, 1.0f, 0.0f);
    glVertex3f(0.25f, 1.0f, -depth);
    glVertex3f(0.75f, 1.0f, -depth);
    glVertex3f(0.75f, 1.0f, 0.0f);
    
    glNormal3f(-2, -1, 0);
    glVertex3f(0.25f, 0.0f, 0.0f);
    glVertex3f(0.00f, 0.5f, 0.0f);
    glVertex3f(0.00f, 0.5f, -depth);
    glVertex3f(0.25f, 0.0f, -depth);
    
    glNormal3f(2, -1, 0);
    glVertex3f(0.75f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.5f, 0.0f);
    glVertex3f(1.0f, 0.5f, -depth);
    glVertex3f(0.75f, 0.0f, -depth);
    
    glNormal3f(2, 1, 0);
    glVertex3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.75f, 1.0f, 0.0f);
    glVertex3f(0.75f, 1.0f, -depth);
    glVertex3f(1.0f, 0.5f, -depth);
    
    glNormal3f(-2, 1, 0);
    glVertex3f(0.0f, 0.5f, -depth);
    glVertex3f(0.25f, 1.0f, -depth);
    glVertex3f(0.25f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    
    glEnd();
}

void drawBackGround()
{
    glPushMatrix();
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glColor3d(1,1,1);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-20.0f, 20.0f, 0.0f);
    glVertex3f(20.0f, 20.0f, 0.0f);
    glVertex3f(20.0f, -20.0f, 0.0f);
    glVertex3f(-20.0f, -20.0f, 0.0f);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glColor3d(1,1,1);
    glBegin(GL_QUADS);
    glVertex3f(-20.0f, floorY-.01, 20.0f);
    glVertex3f(20.0f, floorY-.01, 20.0f);
    glVertex3f(20.0f, floorY-.01, -20.0f);
    glVertex3f(-20.0f, floorY-.01, -20.0f);
    glEnd();
    glPopMatrix();
}


vector<vertex> rotateShadowVertices(vector <vertex> points, float degrees, float x, float y, float z){
    vector<vertex>::iterator it;
    if(z > 0){
        int counter = 0;
        for(it = points.begin(); it!=points.end();it++){
            float r = pow(it->getX()*it->getX()+it->getY()*it->getY(),.5);
            float currAngle = atan2(it->getY(),it->getX());
           // if(z<0) degrees = -degrees;
            float newX = r*cos((degrees * (PI / 180.0))+currAngle);
            float newY = r*sin((degrees * (PI / 180.0))+currAngle);
            it->setX(r*cos((degrees * (PI / 180.0))+currAngle));
            it->setY(r*sin((degrees * (PI / 180.0))+currAngle));
        }
    }
    return points;
}


vector<vertex> translateShadowVertices(vector <vertex> points, float xTrans, float yTrans, float zTrans){
    vector<vertex>::iterator it;
    for(it = points.begin(); it!=points.end();it++){
        it->setX(it->getX()+xTrans);
        it->setY(it->getY()+yTrans);
        it->setZ(it->getZ()+zTrans);
    }
    return points;
}

void drawShadow(vector<vertex> points, int type){
    vector <vertex>::iterator it;
    vector <vertex> vertices;
    vector <vertex>::iterator it2;
    float newX, newY, newZ;
    float slopeY, slopeX, slopeZ, t;
    for(it=points.begin();it!=points.end();++it){
        slopeX = lightX - it->getX();
        slopeY = lightY - it->getY();
        slopeZ = lightZ - it->getZ();
        t = (floorY - it->getY())/slopeY;
        newY = floorY;
        newX = slopeX*t+it->getX();
        newZ = slopeZ*t+it->getZ();
        vertex v(newX,newY,newZ);
        vertices.push_back(v);
    }
    
    glBegin(type);
    if(buildMode)
        glColor3f(0.000, 1.000, 0.498);
    else
        glColor3f(0.663, 0.663, 0.663);
    glNormal3f(0, -1, 0);
    for(it2=vertices.begin();it2!=vertices.end();++it2){
        glVertex3f(it2->getX(), it2->getY(), it2->getZ());
    }
    glEnd();
    
}

void drawNumberZeroShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;

    points = drawCircle3dShadow(.15f, .10f, .10f, 10, points);
    points = translateShadowVertices(points, 0.0f, .75f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();

    points = drawCircle3dShadow(.15f, .10f, .10f, 10, points);
    points = rotateShadowVertices(points, 180.0, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, 0.0f, .25f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawRectangleShadow(.10f, .50f, points);
    points = translateShadowVertices(points, -0.25f, 0.25f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
    points = drawRectangleShadow(.10f, .50f, points);
    points = translateShadowVertices(points, 0.15f, 0.25f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}



void drawNumberZero()
{
    glPushMatrix();
    glTranslatef(0.0f, .75f, 0.0f);
    drawCircle3d(.15f, .10f, .10f, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, .25f, 0.0f);
    glRotatef(180.0, 0.0f, 0.0f, .10f);
    drawCircle3d(.15f, .10f, .10f, 10);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.25f, 0.25f, 0.0f);
    drawRectangle3d(.10f, .50f, .10f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.15f, 0.25f, 0.0f);
    drawRectangle3d(.10f, .50f, .10f);
    glPopMatrix();
    
}

void drawNumberOneShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    points.push_back(vertex(0,0,0));
    points.push_back(vertex(0,1,0));
    points.push_back(vertex(.15,1,0));
    
    points.push_back(vertex(0,0,0));
    points.push_back(vertex(.15,1,0));
    points.push_back(vertex(.15,0,0));
    
    points.push_back(vertex(0,.70,0));
    points.push_back(vertex(-.15,.70,0));
    points.push_back(vertex(-.15,.85,0));
    
    points.push_back(vertex(0,.70,0));
    points.push_back(vertex(-.15,.85,0));
    points.push_back(vertex(0,.85,0));
    
    for(it = points.begin(); it!=points.end();it++){
        it->setX(it->getX()+xTrans);
        it->setY(it->getY()+yTrans);
        it->setZ(it->getZ()+zTrans);
    }
    drawShadow(points,GL_TRIANGLES);
    
}

void drawNumberOne()
{
    drawRectangle3d(0.15f,0.70f,0.10f);
    glPushMatrix();
    glTranslatef(-0.15f,0.70f, 0.0f);
    drawRectangle3d(0.30f, 0.15f, .10f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.00f, 0.85f, 0.0f);
    drawRectangle3d(0.15f, 0.15f, .10f);
    glPopMatrix();
    
    
}

void drawNumberTwoShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 13, points);
    points = rotateShadowVertices(points, -90, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, 0.0f, .50f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 5, points);
    points = rotateShadowVertices(points, 90.0, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, 0.0f, .10f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawRectangleShadow(.45f, .10f, points);
    points = translateShadowVertices(points, -.25f, 0.0f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}

void drawNumberTwo()
{
    glPushMatrix();
    glTranslatef(0.0f, .50f, 0.0f);
    glRotatef(-90.0f, 0.0f, 0.0f, .10f);
    drawCircle3d(.15f, .10f, .10f, 13);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, .10f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, .10f);
    drawCircle3d(.15f, .10f, .10f, 5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-.25f, 0.0f, 0.0f);
    drawRectangle3d(.45f, .10f, .10f);
    glPopMatrix();
    
}

void drawNumberThreeShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 14, points);
    points = rotateShadowVertices(points, 180.0f, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, 0.0f, .25f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 14, points);
    points = rotateShadowVertices(points, 290.0, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, 0.0f, .63f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
}

void drawNumberThree()
{
    glPushMatrix();
    glTranslatef(0.0f, .25f, 0.0f);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    drawCircle3d(.15f, .10f, .10f, 14);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, .63f, 0.0f);
    glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
    drawCircle3d(.15f, .10f, .10f, 14);
    glPopMatrix();
}

void drawNumberFourShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawRectangleShadow(.15f, 1.0f, points);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
    points = drawRectangleShadow(.30f, .15f, points);
    points = translateShadowVertices(points, -.25f, .50f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
    points = drawRectangleShadow(.15f, .50f, points);
    points = translateShadowVertices(points, -.30f, .50f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}


void drawNumberFour()
{
    drawRectangle3d(.15f, 1.0f, .10f);
    glPushMatrix();
    glTranslatef(-.20f, .50f, 0.0f);
    drawRectangle3d(.30f, .15f, .10f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-.30f, .50f, 0.0f);
    drawRectangle3d(.15f, .50f, .10f);
    glPopMatrix();
    
}

void drawNumberFiveShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawCircle3dShadow(.20f, .10f, .10f, 18, points);
    points = rotateShadowVertices(points, 180.0, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, 0.30f, 0.30f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawRectangleShadow(.10f, .50f, points);
    points = translateShadowVertices(points, .05f, 0.48f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
    points = drawRectangleShadow(.40f, .10f, points);
    points = translateShadowVertices(points, 0.05f, 0.98f, 0.0);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}

void drawNumberFive()
{
    glPushMatrix();
    glTranslatef(.30f, .30f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    drawCircle3d(.20f, .10f, .10f, 18);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.05f, .48f, 0.0f);
    drawRectangle3d(.10f, .50f, .10f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.05f, .98f, 0.0f);
    drawRectangle3d(.40f, .10f, .10f);
    glPopMatrix();
}

void drawNumberSixShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 20, points);
    points = translateShadowVertices(points, 0.25f, 0.25f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawRectangleShadow(.15f, 1.0f, points);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}

void drawNumberSix()
{
    glPushMatrix();
    glTranslatef(.25f, .25f, 0.0f);
    drawCircle3d(.15f, .10f, .10f,20);
    glPopMatrix();
    
    glPushMatrix();
    drawRectangle3d(.15f, 1.0f, .10f);
    glPopMatrix();
}

void drawNumberSevenShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;

    points = drawRectangleShadow(.15f, 1.12f, points);
    points = translateShadowVertices(points, -0.05f, 0.04f, 0.0f);
    points = rotateShadowVertices(points, -20.0, 0.0f, 0.0f, 1.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
    points = drawRectangleShadow(.47f, .15f, points);
    points = translateShadowVertices(points, 0.00f, 1.00f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}

void drawNumberSeven()
{
    glPushMatrix();
    glRotatef(-20, 0.0f, 0.0f, 1.0f);
    glTranslatef(-.05f, 0.04f, 0.0f);
    drawRectangle3d(.15f, 1.12f, .10f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    drawRectangle3d(.47f, .15f, .10f);
    glPopMatrix();
    
}

void drawNumberEightShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 20, points);
    points = translateShadowVertices(points, 0.00f, 0.65f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 20, points);
    points = translateShadowVertices(points, 0.00f, 0.25f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
}

void drawNumberEight()
{
    glPushMatrix();
    glTranslatef(0.0f, .65f, 0.0f);
    drawCircle3d(.15f, .10f, .10f,20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, .25f, 0.0f);
    drawCircle3d(.15f, .10f, .10f,20);
    glPopMatrix();
}

void drawNumberNineShadow(float xTrans, float yTrans, float zTrans){
    vector<vertex> points;
    vector<vertex>::iterator it;
    
    points = drawCircle3dShadow(.15f, .10f, .10f, 20, points);
    points = translateShadowVertices(points, -.10f, 0.75f, 0.0f);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUAD_STRIP);
    points.clear();
    
    points = drawRectangleShadow(.15f, 1.0f, points);
    points = translateShadowVertices(points, xTrans, yTrans, zTrans);
    drawShadow(points, GL_QUADS);
    points.clear();
    
}

void drawNumberNine()
{
    glPushMatrix();
    glTranslatef(-.10f, .75f, 0.0f);
    drawCircle3d(.15f, .10f, .10f,20);
    glPopMatrix();
    drawRectangle3d(.15f, 1.0f, .10f);
}

void drawNumberTen()
{
    glPushMatrix();
    drawNumberOne();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(.50f, 0.0f, 0.0f);
    drawNumberZero();
    glPopMatrix();
}

void drawLetterE()
{
    
    drawRectangle3d(.10f, 1.0f, .10f);
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    drawRectangle3d(.50f, .10f, .10f);
    glPopMatrix();
    
    drawRectangle3d(.50f, .10f, .10f);
    
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    drawRectangle3d(.40f, .10f, .10f);
    glPopMatrix();
    
}

void drawLetterT()
{
    glPushMatrix();
    glTranslatef(.35f, 0.0f, 0.0f);
    drawRectangle3d(.10f, 1.0f, .10f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    drawRectangle3d(.80f, 0.10f, .10f);
    glPopMatrix();
    
}

void drawFaceObject()
{
    switch(faceCounter%6)
    {
        case 0: glPushMatrix();
            glScalef(.50f, .50f, .50f);
            glTranslatef(.50f, .50f, -.10f);
            drawRectangle3d(1.0,1.0,.10);
            glPopMatrix();
            break;
        case 1:
            glPushMatrix();
            glScalef(.50f, .50f, .50f);
            glTranslatef(.50f, .50f, -.10f);
            drawTriangle(.10);
            glPopMatrix();
            break;
        case 2:
            glPushMatrix();
            glScalef(.50f, .50f, .50f);
            glTranslatef(.50f, .50f, -.10f);
            drawPentagon(.10);
            glPopMatrix();
            break;
        case 3:
            glPushMatrix();
            glScalef(.50f, .50f, .50f);
            glTranslatef(.85f, .50f, -.10f);
            drawNumberOne();
            glPopMatrix();
            break;
        case 4:
            glPushMatrix();
            glScalef(.50f, .50f, .50f);
            glTranslatef(.65f, .50f, -.10f);
            drawLetterE();
            glPopMatrix();
            break;
        case 5:
            glPushMatrix();
            glScalef(.50f, .50f, .50f);
            glTranslatef(.50f, .50f, -.10f);
            drawLetterT();
            glPopMatrix();
            break;
    }
    faceCounter++;
}


void drawCubeFace()
{

    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1,0,1);
    
    glNormal3f(1,0,0);
    glVertex3f( 0.10f, 0.10f, 0.0f ); //vertex 1
    glVertex3f( 0.10f, .90f, 0.0f ); //vertex 2
    glVertex3f( 0.10f, 0.10f, -0.10f ); //vertex 3
    glVertex3f( 0.10f, 0.90f, -0.10f ); //vertex 4
    
    glNormal3f(0,-1,0);
    glVertex3f( 0.10f, .90f, 0.0f ); //vertex 5
    glVertex3f( 0.90f, .90f, -.10f ); //vertex 6
    glVertex3f( 0.90f, .90f, 0.0f ); //vertex 7
    
    glNormal3f(-1,0,0);
    glVertex3f( 0.90f, .10f, 0.0f ); //vertex 8
    glVertex3f( 0.90f, .90f, -0.10f ); //vertex 9
    glVertex3f( 0.90f, .10f, -0.10f ); //vertex 10
    
    glNormal3f(0,1,0);
    glVertex3f( 0.90f, .10f, 0.00f ); //vertex 11
    glVertex3f( 0.10f, .10f, -0.10f ); //vertex 12
    glVertex3f( 0.10f, .10f, 0.00f ); //vertex 13
    glEnd();
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(1,1,1);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f( 0.10f, 0.10f, -0.10f ); //vertex 1
    glTexCoord2f(0, 1);
    glVertex3f( 0.10f, 0.90f, -0.10f ); //vertex 2
    glTexCoord2f(1, 0);
    glVertex3f( 0.90f, 0.10f, -0.10f ); //vertex 3
    glTexCoord2f(1, 1);
    glVertex3f( 0.90f, 0.90f, -0.10f ); //vertex 4
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    
    glBegin(GL_TRIANGLE_STRIP);
    glColor3d(0,0,1);
    glNormal3f(0, 0, 1);
    glVertex3f( 0.00f, 0.10f, 0.00f ); //vertex 1
    glVertex3f( 0.00f, 1.00f, 0.00f ); //vertex 2
    glVertex3f( 0.10f, 0.10f, 0.00f ); //vertex 3
    glVertex3f( 0.10f, 1.00f, 0.00f ); //vertex 4
    
    glVertex3f( 0.10f, 0.90f, 0.00f ); //vertex 4
    glVertex3f( 1.00f, 1.00f, 0.00f ); //vertex 4
    glVertex3f( 1.00f, 0.90f, 0.00f ); //vertex 4
    
    glVertex3f( 0.90f, 0.90f, 0.00f ); //vertex 4
    glVertex3f( 1.00f, 0.00f, 0.00f ); //vertex 4
    glVertex3f( 0.90f, 0.00f, 0.00f ); //vertex 4
    
    glVertex3f( 0.90f, 0.10f, 0.00f ); //vertex 4
    glVertex3f( 0.00f, 0.00f, 0.00f ); //vertex 4
    glVertex3f( 0.00f, 0.10f, 0.00f ); //vertex 4
    glEnd();
    
    drawFaceObject();
}


void drawCubeShadow(float xTrans, float yTrans, float zTrans, bool rOffset1){
    vector<vertex> points;
    vector<vertex>::iterator it;
    points.push_back(vertex(1,1,1));
    points.push_back(vertex(0,1,1));
    points.push_back(vertex(0,1,0));
    points.push_back(vertex(1,1,0));
    int counter = 0;
    int rOffset = 0;
    rOffset1?rOffset=rotationOffset:rOffset=rotationOffset2;
    for(it = points.begin(); it!=points.end();it++){
        it->setX(.7071*cos((rOffset%360+45+counter*90) * (PI / 180.0)));
        it->setZ(.7071*sin((rOffset%360+45+counter*90) * (PI / 180.0)));
        it->setX(it->getX()+xTrans);
        it->setY(it->getY()+yTrans);
        it->setZ(it->getZ()+zTrans);
        counter++;
    }
    drawShadow(points,GL_POLYGON);
}

void drawCube()
{
    //front
    glPushMatrix();
    glTranslatef(0.0f, 0.0f,1.0f);
    drawCubeFace();
    glPopMatrix();
    
    //back
    glPushMatrix();
    glTranslatef(0.0f, 1.0f,0.0f);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    drawCubeFace();
    glPopMatrix();
    
    //top
    glPushMatrix();
    glTranslatef(0.0f, 1.0f,1.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    drawCubeFace();
    glPopMatrix();
    
    //bottom
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    drawCubeFace();
    glPopMatrix();
    
    //left
    glPushMatrix();
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    drawCubeFace();
    glPopMatrix();
    
    //right
    glPushMatrix();
    glTranslatef(1.0f, 0.0f,1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawCubeFace();
    glPopMatrix();
    
}
void repositionNumbers(){
    zeroOffset = 0;
    oneOffset = -5.0;
    twoOffset = -10.0;
    threeOffset = -15.0;
    fourOffset = -20.0;
    fiveOffset = -25.0;
    sixOffset = -30.0;
    sevenOffset = -35.0;
    eightOffset = -40.0;
    nineOffset = -45.0;
    tenOffset = -50.0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(buildMode){
        axisOn = true;
        lightsOn = true;
        backgroundOn = false;
        drawCubes = false;
        drawNumbers = true;
        
    }else{
        axisOn = false;
        lightsOn = true;
        backgroundOn = true;
        drawCubes = true;
        drawNumbers = true;
    }
    //need to flip the up vector depending on polar vector so camera rotation is seemless
    if(theta2 > 360 || theta2 < -360)
        theta2 = remainder(theta2, 360.0);

    if((theta2 > 180 && theta2 <= 360) || (theta2<0 && theta2 >=-180))
        up=-1.0;
    else
        up=1.0;
        
    //formula for spherical coordinates[
    gluLookAt(pow(128.0,0.5)*cos(theta*PI/180.0)*sin(theta2*PI/180.0),pow(128.0,0.5)*cos(theta2*PI/180.0),pow(128.0,0.5)*sin(theta*PI/180.0)*sin(theta2*PI/180.0),
                0.0f,0.0f,0.0f,
                0.0f,up,0.0f);
    
    
    if(lightsOn){
        GLfloat pos[]= {lightX,lightY,lightZ,1};
        GLfloat dif[]= {2.5,2.5,2.5,1};  //white diffuse light
        GLfloat amb[]= {.05,.05,.05,1};  //faint black ambient light
        glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
    }
    
    if(drawCubes){
        glPushMatrix();
        glRotatef(rotationOffset%360, 0.0f, 1.0f, 0.0f);
        glTranslatef(-.5f, 1.0f, 0.5f);
        glRotatef(180, 1.0f, 0.0f, 0.0f);
        drawCube();
        glPopMatrix();
    
        glPushMatrix();
        drawCubeShadow(0,0,0,false);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 2.0f);
        glRotatef(rotationOffset2%360, 0.0f, 1.0f, 0.0f);
        glTranslatef(-.5f, 0.0f, -0.5f);
        drawCube();
        glPopMatrix();
        
        glPushMatrix();
        drawCubeShadow(0,0,2.0f,true);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 4.0f);
        glRotatef(rotationOffset%360, 0.0f, 1.0f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glTranslatef(-.5f, 0.0f, -0.5f);
        drawCube();
        glPopMatrix();
        
        glPushMatrix();
        drawCubeShadow(0,0,4.0f,false);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        glRotatef(rotationOffset2%360, 0.0f, 1.0f, 0.0f);
        glRotatef(-90, 0.0f, 1.0f, 0.0f);
        glTranslatef(-.5f, 0.0f, -0.5f);
        drawCube();
        glPopMatrix();
        
        glPushMatrix();
        drawCubeShadow(2.0f,0,0.0f,true);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(4.0f, 0.0f, 0.0f);
        glRotatef(rotationOffset%360, 0.0f, 1.0f, 0.0f);
        glRotatef(-180, 0.0f, 1.0f, 0.0f);
        glTranslatef(-.5f, 0.0f, -0.5f);
        drawCube();
        glPopMatrix();
        
        glPushMatrix();
        drawCubeShadow(4.0f,0,0.0f,false);
        glPopMatrix();
    }
    
    if(axisOn){
        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable( GL_LINE_SMOOTH );
        glLineWidth( 1.5 );
        glBegin(GL_LINES);
        glVertex3f(-1000, 0, 0);
        glVertex3f(1000, 0, 0);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);
        glVertex3f(0, 0, -1000);
        glVertex3f(0, 0, 1000);
        glEnd();
    }
    
    if(drawNumbers){
        glPushMatrix();
        glTranslatef(zeroOffset, 0.0f, .25*(zeroOffset*zeroOffset));
        drawNumberZero();
        glPopMatrix();
        
        drawNumberZeroShadow(zeroOffset, 0.0f, .25*(zeroOffset*zeroOffset));
        
        glPushMatrix();
        glTranslatef((.25*(oneOffset*oneOffset)), 0.0f, oneOffset);
        drawNumberOne();
        glPopMatrix();
        
        drawNumberOneShadow((.25*(oneOffset*oneOffset)), 0.0f, oneOffset);
        
        glPushMatrix();
        glTranslatef(twoOffset, 0.0f, .25*(twoOffset*twoOffset));
        drawNumberTwo();
        glPopMatrix();
        
        drawNumberTwoShadow(twoOffset, 0.0f, .25*(twoOffset*twoOffset));
        
        glPushMatrix();
        glTranslatef((.25*(threeOffset*threeOffset)), 0.0f, threeOffset);
        drawNumberThree();
        glPopMatrix();
        
        drawNumberThreeShadow((.25*(threeOffset*threeOffset)), 0.0f, threeOffset);
        
        glPushMatrix();
        glTranslatef(fourOffset, 0.0f, .25*(fourOffset*fourOffset));
        drawNumberFour();
        glPopMatrix();
        
        drawNumberFourShadow(fourOffset, 0.0f, .25*(fourOffset*fourOffset));
        
        glPushMatrix();
        glTranslatef((.25*(fiveOffset*fiveOffset)), 0.0f, fiveOffset);
        drawNumberFive();
        glPopMatrix();
        
        drawNumberFiveShadow((.25*(fiveOffset*fiveOffset)), 0.0f, fiveOffset);
        
        glPushMatrix();
        glTranslatef(sixOffset, 0.0f, .25*(sixOffset*sixOffset));
        drawNumberSix();
        glPopMatrix();
        
        drawNumberSixShadow(sixOffset, 0.0f, .25*(sixOffset*sixOffset));
        
        glPushMatrix();
        glTranslatef((.25*(sevenOffset*sevenOffset)), 0.0f, sevenOffset);
        drawNumberSeven();
        glPopMatrix();
        
        drawNumberSevenShadow((.25*(sevenOffset*sevenOffset)), 0.0f, sevenOffset);
        
        glPushMatrix();
        glTranslatef(eightOffset, 0.0f, .25*(eightOffset*eightOffset));
        drawNumberEight();
        glPopMatrix();
        
        drawNumberEightShadow(eightOffset, 0.0f, .25*(eightOffset*eightOffset));
        
        glPushMatrix();
        glTranslatef((.25*(nineOffset*nineOffset)), 0.0f, nineOffset);
        drawNumberNine();
        glPopMatrix();
        
        drawNumberNineShadow((.25*(nineOffset*nineOffset)), 0.0f, nineOffset);
        
        glPushMatrix();
        glTranslatef(tenOffset, 0.0f, .25*(tenOffset*tenOffset));
        drawNumberTen();
        glPopMatrix();
        drawNumberOneShadow(tenOffset, 0.0f, .25*(tenOffset*tenOffset));
        drawNumberZeroShadow(tenOffset+.50f, 0.0f, .25*(tenOffset*tenOffset));
    }
    
    if(backgroundOn){
        glPushMatrix();
        glTranslatef(-10.0f, 0.0f, -10.0f);
        drawBackGround();
        glPopMatrix();
    }
    
    glutSwapBuffers();
    
}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 27 || key == 'q' || key == 'Q')
        exit(0);
    if(key == 'b')
        buildMode = !buildMode;
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON){
        if(state == GLUT_DOWN){
            priorMouseX = x;
            priorMouseY = y;
        }else if(state == GLUT_UP){
            int diffX = x-priorMouseX;
            int diffY = y-priorMouseY;
        }
    }
}

void mouseMotion(int x, int y){
    int diffX = x-priorMouseX;
    theta = theta + (((diffX)*360.0)/width);
    int diffY = y-priorMouseY;
    theta2 = theta2 + (((diffY)*360.0)/height);
    priorMouseX = x;
    priorMouseY = y;
    printf("x:%d y:%d \n",x,y);
}

void reshape(int wth, int ht)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0, wth, ht);
    gluPerspective(45, wth/ht, .1, 100);
    glMatrixMode(GL_MODELVIEW);
    width=wth;
    height=ht;
    
}

void idle(){
    glutPostRedisplay();
    if(buildMode){
        rotationOffset = 0;
        rotationOffset2 = 0;
        zeroOffset = 0;
        oneOffset = 0;
        twoOffset = 0;
        threeOffset = 0;
        fourOffset = 0;
        fiveOffset = 0;
        sixOffset = 0;
        sevenOffset = 0;
        eightOffset = 0;
        nineOffset = 0;
        tenOffset = 0;
    }else{
        rotationOffset++;
        rotationOffset2--;
        zeroOffset = zeroOffset+.02;
        oneOffset = oneOffset+.02;
        twoOffset = twoOffset+.02;
        threeOffset = threeOffset+.02;
        fourOffset = fourOffset+.02;
        fiveOffset = fiveOffset+.02;
        sixOffset = sixOffset+.02;
        sevenOffset = sevenOffset +.02;
        eightOffset = eightOffset +.02;
        nineOffset = nineOffset +.02;
        tenOffset = tenOffset + .02;
    }
}

void createWindowAndCallbacks()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow("OpenGL Graphics Demo");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glClearColor(0,0,0,0);
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    createWindowAndCallbacks();
    
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0, width, height);
    gluPerspective(45, width/height, .1, 100);
    
    if(lightsOn){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_NORMALIZE);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    int width, height;
    unsigned char* image =SOIL_load_image("/Users/jhughes/Documents/wood.bmp", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    

    glutMainLoop();
}