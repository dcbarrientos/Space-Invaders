#include "element.h"
#include<iostream>
Element::Element(int _x, int _y, int _width, int _height, char* img_path){
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    img = load_bitmap(img_path, NULL);

    if(img == NULL){
        std::cout << "Error loading image: " << img_path << std::endl;
    }
}

void Element::render(BITMAP *buffer){
    masked_blit(img, buffer, 0, 0, x, y, width, height);
}

void Element::update(){
}
