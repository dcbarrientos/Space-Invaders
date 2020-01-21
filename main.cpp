#include <allegro.h>
#include <iostream>

#include "main.h"

using namespace std;

//https://www.youtube.com/watch?v=a2MoETBfdQE&list=PL6hPvfzEEMDZ4PSkN-5Zj_0-YVO7b0OgC&index=3
int main(int argc, char *argv[]){
    init_allegro(WIDTH, HEIGHT);
    init_audio(70, 70);
    return 1;
}

void init_allegro(int ancho, int alto){
    allegro_init();
    install_keyboard();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ancho, alto, 0, 0);
}

bool init_audio(int vol_derecha, int vol_izquierda){
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0){
        allegro_message("Error: no se pudo inicializar el sonido\n%s\n", allegro_error);
        return false;
    }

    set_volume(vol_izquierda, vol_derecha);
    return true;
}

END_OF_MAIN()
