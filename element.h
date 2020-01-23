#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <string>
#include <allegro.h>

class Element{
    protected:
    int x, y;       //Posicion del elememento
    int width, height;
    BITMAP *img;     //Imagen del elemento
    bool destroy;
    bool hit;
    int hit_count;

    public:
    Element(int _x, int _y, int width, int height, char* img_path);
    void update();
    void render(BITMAP *buffer);
    int get_x();
    int get_y();
    int get_width();
    int get_height();
    void set_destroy(bool _destroy);
    bool get_destroy();
    void set_hit(bool _hit);
    bool get_hit();
};

#endif // ELEMENT_H_INCLUDED
