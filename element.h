#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <string>
#include <allegro.h>

class Element{
    protected:
    int x, y;       //Posicion del elememento
    int width, height;
    BITMAP *img;     //Imagen del elemento

    public:
    Element(int _x, int _y, int width, int height, char* img_path);
    void update();
    void render(BITMAP *buffer);
    int get_x();
    int get_y();

};

#endif // ELEMENT_H_INCLUDED
