#include <allegro.h>
#include <iostream>
#include <vector>

#include "main.h"
#include "nave.h"
#include "bala.h"
#include "enemigo.h"
#include "math.h"

using namespace std;
Nave *nave;
Bala *bala_player;
vector<Bala*> balas_enemigos;
vector<Enemigo*> enemigos;
int cont;

//https://www.youtube.com/watch?v=a2MoETBfdQE&list=PL6hPvfzEEMDZ4PSkN-5Zj_0-YVO7b0OgC&index=3
int main(int argc, char *argv[]){
    init_allegro(WIDTH, HEIGHT);
    init_audio(70, 70);

    BITMAP *buffer = create_bitmap(WIDTH, HEIGHT);

    char nave_path[] = "resources\\nave.bmp";
    char bala_path[] = "resources\\bala2.bmp";
    char enemigos_path[] = "resources\\enemigos.bmp";

    int x = WIDTH / 2;
    int y = HEIGHT - 50;
    cont = 0;

    balas_enemigos.clear();

    nave = new Nave(x, y, NAVE_WIDTH, NAVE_HEIGHT, nave_path);
    enemigos.insert(enemigos.end(), new Enemigo(50, 80, 25, 20, 5, enemigos_path));
    enemigos.insert(enemigos.end(), new Enemigo(75, 80, 25, 20, 5, enemigos_path));
    enemigos.insert(enemigos.end(), new Enemigo(100, 80, 25, 20, 5, enemigos_path));

    while(!key[KEY_ESC]){
        clear_to_color(buffer, 0x000000);

        if(key[KEY_LEFT])
            nave->move(KEY_LEFT);
        if(key[KEY_RIGHT])
            nave->move(KEY_RIGHT);

        if(key[KEY_SPACE]){
            if(bala_player == NULL){
                int xt = nave->get_x() + NAVE_WIDTH / 2 - BALA_WIDTH / 2;
                bala_player = new Bala(xt, nave->get_y(), BALA_WIDTH, BALA_HEIGHT, BALA_SPEED * -1,bala_path);
            }
        }
        disparar_enemigo();

        update();
        render(buffer);

        rest(1000/60);  //Actualizo 60 veces por segundo.
    }

    delete(nave);

    return 0;
}

void update(){
    for(unsigned int i = 0; i < balas_enemigos.size(); i++)
        balas_enemigos[i]->update();
/*
    for(unsigned int i = 0; i < balas_enemigos.size(); i++){
        if(balas_enemigos[i]->is_out())
            balas_enemigos.erase(balas_enemigos.begin() + i);
    }
*/
    if(bala_player != NULL){
        bala_player->update();

        if(bala_player->is_out()){
            delete(bala_player);
            bala_player = NULL;
        }
    }

    for(unsigned int i = 0; i < enemigos.size(); i++)
        enemigos[i]->update();

    //Verificar colisiones
}

void render(BITMAP *buffer){
    nave->render(buffer);
    if(bala_player != NULL)
        bala_player->render(buffer);

    for(unsigned int i = 0; i < balas_enemigos.size(); i++)
        balas_enemigos[i]->render(buffer);

    for(unsigned int i = 0; i < enemigos.size(); i++)
        enemigos[i]->render(buffer);

    blit(buffer, screen, 0, 0, 0, 0, WIDTH, HEIGHT);
}

void disparar_enemigo(){
    if(cont++ == BALA_ENEMIGO_ESPERA){
        cont = 0;
        char bala_enemigo_path[] = "resources\\Bala_enem.bmp";

        int n_enemigo = get_random(0, enemigos.size() - 1);
        cout << n_enemigo << endl;
        int xt = enemigos[n_enemigo]->get_x() + BALA_ENEMIGO_WIDTH / 2;
        balas_enemigos.insert(balas_enemigos.end(), new Bala(xt, enemigos[n_enemigo]->get_y(), BALA_ENEMIGO_WIDTH, BALA_ENEMIGO_HEIGHT, BALA_SPEED, bala_enemigo_path));
        cout << "cont: " << cont << " balas: " << balas_enemigos.size() << endl;
    }
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
