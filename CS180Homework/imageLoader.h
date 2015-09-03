//
//  imageLoader.h
//  CS180Homework
//
//  Created by Jordan Hughes on 11/15/14.
//  Copyright (c) 2014 JHughes. All rights reserved.
//

#ifndef __CS180Homework__imageLoader__
#define __CS180Homework__imageLoader__

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#endif /* defined(__CS180Homework__imageLoader__) */


class imageLoader{
    private:
        string fileName;
        unsigned char header[54];
        char* imgdata;
        unsigned int width;
        unsigned int height;
        unsigned int imageSize;
        unsigned int dataPos;
    public:
        imageLoader(string fName);
        void loadImage();
        char* data();
        int getWidth();
        int getHeight();
};
