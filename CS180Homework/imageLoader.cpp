//
//  imageLoader.cpp
//  CS180Homework
//
//  Created by Jordan Hughes on 11/15/14.
//  Copyright (c) 2014 JHughes. All rights reserved.
//

#include "imageLoader.h"



imageLoader::imageLoader(string fName){
    fileName = fName;
    
}

void imageLoader::loadImage(){
    ifstream myFile;
    string line;
    myFile.open(fileName);
    if(myFile.is_open()){
        if(getline(myFile,line)){
            memcpy(header, line.c_str(), 54);
            width = *(int*)&(header[18]);
            height = *(int*)&(header[22]);
            imageSize = *(int*)&(header[34]);
            if(imageSize == 0)
                imageSize = width*height*3;
            dataPos = *(int*)&(header[10]);
            if(dataPos==0)
                dataPos = 54;
            imgdata = new char[imageSize];
            memcpy(imgdata, line.c_str()+dataPos, imageSize);
        }
        
    }
    myFile.close();
}

char* imageLoader::data(){
    return imgdata;
}
int imageLoader::getWidth(){
    return width;
}
int imageLoader::getHeight(){
    return height;
}