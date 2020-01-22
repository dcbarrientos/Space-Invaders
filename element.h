#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <string>

class Element{
    int x, y;       //Posicion del elememento
    BITMAP img;     //Imagen del elemento

    public:
    Element(int _x, int _y, std::string img_path);
    void update();
    void render(BITMAP *buffer);
};

#endif // ELEMENT_H_INCLUDED
