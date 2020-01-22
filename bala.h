#ifndef BALA_H_INCLUDED
#define BALA_H_INCLUDED

#include "element.h"

#define SPEED 8
#define BALA_WIDTH
#define BALA_HEIGHT

class Bala: Element{

    Bala(int x, int y, int width, int height, char *img_path): Element(x, y, width, height, img_path){};
    void update();
};

#endif // BALA_H_INCLUDED
