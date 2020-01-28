#include "menu.h"

Menu::Menu(char *menu_path): Element(X_POS, Y_POS, WIDTH, HEIGHT, menu_path){
    index = 0;
    fila = 0;
}

void Menu::update(){
    contador++;
    if(ESPERA_CAMBIO <= contador){
        if(index == 0)
            index = 1;
        else
            index = 0;
        contador = 0;
    }
}

void Menu::render(BITMAP *buffer){
    blit(img, buffer, WIDTH * index, fila * HEIGHT, x, y, WIDTH, HEIGHT);
}

void Menu::set_fila(int _fila){
    fila = _fila;
}

