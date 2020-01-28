#include "element.h"

Element::Element(int _x, int _y, int _width, int _height, char* img_path){
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    img = load_bitmap(img_path, NULL);
    hit = false;
    destroy = false;
//    if(img == NULL){
//        std::cout << "Error loading image: " << img_path << std::endl;
//    }
}

void Element::render(BITMAP *buffer){
    masked_blit(img, buffer, 0, 0, x, y, width, height);
}

void Element::update(){
}

int Element::get_x(){
    return x;
}

int Element::get_y(){
    return y;
}

int Element::get_width(){
    return width;
}

int Element::get_height(){
    return height;
}

void Element::set_destroy(bool _destroy){
    destroy = _destroy;
}
bool Element::get_destroy(){
    return destroy;
}

void Element::set_hit(bool _hit){
    hit = _hit;
}
bool Element::get_hit(){
    return hit;
}

