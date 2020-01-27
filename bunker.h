#ifndef BUNKER_H_INCLUDED
#define BUNKER_H_INCLUDED

#include "element.h"

#define HITS_MAX 3

class Bunker: public Element{
    int type;       //Identifico el tipo de tile que uso, ser�a la fila
    int state;      //Estado en el que est� ese pedazo de bunker, ser�a columna. Aceptar�a hasta 3 hits.
    int hits;       //Cantidad de hits, al 4 se lo destruye

public:
    Bunker(int _x, int _y, int _width, int _height, int _type, char *img_path);
    void set_hit();
    void update();
    void render(BITMAP *buffer);
};

#endif // BUNKER_H_INCLUDED
