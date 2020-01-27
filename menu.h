#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "element.h"

#define ESPERA_CAMBIO 25
#define X_POS 0
#define Y_POS 120
#define WIDTH 600
#define HEIGHT 400
#define BORDE 40

class Menu: public Element{
    int index;
    int fila;
    int contador;
public:
    Menu(char *menu_path);
    void update();
    void render(BITMAP *bufer);
    void set_fila(int _fila);
};

#endif // MENU_H_INCLUDED
