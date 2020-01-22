#include <allegro.h>
#include <iostream>

#include "main.h"
#include "nave.h"

using namespace std;

//https://www.youtube.com/watch?v=a2MoETBfdQE&list=PL6hPvfzEEMDZ4PSkN-5Zj_0-YVO7b0OgC&index=3
int main(int argc, char *argv[]){
    init_allegro(WIDTH, HEIGHT);
    init_audio(70, 70);

    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);
    BITMAP *bala = load_bitmap("resources/Bala2.bmp", NULL);
    //BITMAP *nave = load_bitmap("resources/nave.bmp", NULL);

    int x = WIDTH / 2;
    int y = HEIGHT - 50;
    int ndisparos = 0;
    string nave_path = "resources/nave.bmp";
    Nave nave(x, y, nave_path);

    while(!key[KEY_ESC]){
        clear_to_color(buffer, 0x000000);
        //masked_blit(nave, buffer, 0, 0, x, y, NAVE_WIDTH, NAVE_HEIGHT);

    }

    return 0;
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
