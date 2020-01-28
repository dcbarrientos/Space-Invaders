#include "bunker.h"

Bunker::Bunker(int _x, int _y, int _width, int _height, int _type, char *img_path): Element(_x, _y, _width, _height, img_path){
    type = _type;
    state = 0;
    hits = 0;
    destroy = false;
}

void Bunker::set_hit(){
    hits++;
}

void Bunker::update(){
    if(hits >= HITS_MAX){
        destroy = true;
    }
}

void Bunker::render(BITMAP *buffer){
    masked_blit(img, buffer, hits * width, type * height, x, y, width, height);
}

