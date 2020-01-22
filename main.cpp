#include <allegro.h>
#include <iostream>
#include <vector>

#include "main.h"
#include "nave.h"

using namespace std;
Nave *nave;
vector<Element> enemigos;

//https://www.youtube.com/watch?v=a2MoETBfdQE&list=PL6hPvfzEEMDZ4PSkN-5Zj_0-YVO7b0OgC&index=3
int main(int argc, char *argv[]){
    init_allegro(WIDTH, HEIGHT);
    init_audio(70, 70);

    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);

    int x = WIDTH / 2;
    int y = HEIGHT - 50;
    //int ndisparos = 0;

    char nave_path[] = "resources\\nave.bmp";
    nave = new Nave(x, y, NAVE_WIDTH, NAVE_HEIGHT, nave_path);

    while(!key[KEY_ESC]){
        clear_to_color(buffer, 0x000000);

        if(key[KEY_LEFT])
            nave->move(KEY_LEFT);
        if(key[KEY_RIGHT])
            nave->move(KEY_RIGHT);

        update();
        render(buffer);

        rest(1000/60);  //Actualizo 60 veces por segundo.
    }

    delete(nave);

    return 0;
}

void update(){
    //nave->update(key);
}

void render(BITMAP *buffer){
    nave->render(buffer);

    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
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
