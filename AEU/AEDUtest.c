#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h> //ainda é necessaria?
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define LARGURA_TELA 640
#define ALTURA_TELA 480

void inicializacao(){

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_init_primitives_addon();

    DeuErro();
}

int DeuErro (){
    if(!al_init()){
        fprintf(stderr, "Falha init!\n");
        return 0;
    }
    /*
    AINDA NAP FUNCIONA :(
    if(!al_init_font_addon()){
        fprintf(stderr, "Falha font!\n");
        return 0;
    }
    */
    if(!al_init_ttf_addon){
        fprintf(stderr, "Falha ttf!\n");
        return 0;
    }
    if(!al_is_keyboard_installed()){
        fprintf(stderr, "Falha keyboard!\n");
        return 0;
    }
    if(!al_is_mouse_installed()){
        fprintf(stderr, "Falha mouse!\n");
        return 0;
    }
    if(!al_init_image_addon()){
        fprintf(stderr, "Falha image!\n");
        return 0;
    }

    if(!al_init_primitives_addon()){
        fprintf(stderr, "Falha primitives!\n");
        return 0;
    }

    if (!al_install_audio()){
        fprintf(stderr, "Falha ao inicializar áudio\n");
        return 0;
    }

    if (!al_init_acodec_addon()){
        fprintf(stderr, "Falha ao inicializar codecs de áudio.n");
        return 0;
    }

}

// Variáveis globais
    //Necessarias
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_FONT *fontePixelGrande = NULL;
    ALLEGRO_FONT *fontePixel = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *imagem = NULL;
    ALLEGRO_BITMAP *prova = NULL;
    ALLEGRO_AUDIO_STREAM *musica = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    bool fim = false;

    //Variaveis de personagem
    char nome[200] = " ";
    int i=1;
    int sexo;
    int curso; // 1=exatas; 2=Humanas
    bool aprovado;
    int valor=0;

int main(){
    inicializacao();

    //crição de dispositivos
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    fontePixelGrande = al_load_font("VCR_OSD_MONO.ttf", 30, 0);
    fontePixel = al_load_font("VCR_OSD_MONO.ttf", 21, 0);
    fila_eventos = al_create_event_queue();
    imagem = al_load_bitmap("telainicial.bmp");
    al_reserve_samples(1);

    if(!al_reserve_samples(1)){
        fprintf(stderr, "Falha ao alocar canais de áudio.n");
        thanos();
        return 0;
    }

    //registros de sources
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    //definição de dispositivos
    al_draw_bitmap(imagem, 0, 0, 0);
    al_set_window_title(janela, "Vida De Universitario BETA");

    //definição de audio
    musica = al_load_audio_stream("Beliver imagine dragons.ogg", 4, 1024);
    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.n");
        thanos();
        return 0;
    }
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);


    //al_flip_display();

    int t;
while(!fim){
    valor = menu();

    if(valor == 1){
            t = personagem();

            if(t != 3){
                comecarjogo();
                imagem = al_load_bitmap("telainicial.bmp");
            }
            else{
            imagem = al_load_bitmap("telainicial.bmp");
            al_draw_bitmap(imagem, 0, 0, 0);
            }

    }
    else if (valor == 2){
            t = creditos();
            if(t == 3){
                imagem = al_load_bitmap("telainicial.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
            }
    }
    else if(valor == 3){
        fim = true;
    }
}

    thanos();

    return 0;
}

int menu(){
    while(!fim){
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

        al_draw_bitmap(imagem, 0, 0, 0);
        /*
        //Menu Bonito
        // O menu tá lagado e tá aumentando o consumo de memória a ponto de ele não fechar e ser preciso encerrar o processo
            // START GAME
            if(ev.mouse.y > 240 && ev.mouse.y < 283 && ev.mouse.x > 193 && ev.mouse.x < 362){
                imagem = al_load_bitmap("telainicial-iniciar.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_flip_display();
            }
            // CREDITOS
            else if(ev.mouse.y > 413 && ev.mouse.y < 459 && ev.mouse.x > 464 && ev.mouse.x < 629){
                imagem = al_load_bitmap("telainicial-creditos.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_flip_display();
            }
            // QUIT
            else if(ev.mouse.y > 324 && ev.mouse.y < 343 && ev.mouse.x > 193 && ev.mouse.x < 363){
                imagem = al_load_bitmap("telainicial-sair.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_flip_display();
            }
            else{
                imagem = al_load_bitmap("telainicial.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_flip_display();
            }*/


        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
        }

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            // START GAME
            if(ev.mouse.y > 240 && ev.mouse.y < 283 && ev.mouse.x > 193 && ev.mouse.x < 362){
                    valor = 1;
                    return valor;
            }
            // CREDITOS
            if(ev.mouse.y > 413 && ev.mouse.y < 459 && ev.mouse.x > 464 && ev.mouse.x < 629){
                al_draw_text(fontePixel, al_map_rgb(252, 15, 192), LARGURA_TELA / 6, ALTURA_TELA / 1.75, ALLEGRO_ALIGN_CENTRE, "CREDITOS");
                valor = 2;
                return valor;
            }

            // QUIT
            if(ev.mouse.y > 324 && ev.mouse.y < 343 && ev.mouse.x > 193 && ev.mouse.x < 363){
                valor = 3;
                return valor;
                fim = true;
            }

        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                fim = true;
            }

        }
        al_flip_display();
    }
}

int personagem(){
    int contEnter=0;

    imagem = al_load_bitmap("sexojogo.bmp");
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
    while(true){
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);
        al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 100, 460, ALLEGRO_ALIGN_CENTRE, "Ctrl para voltar");
        //eventos de saida
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
            break;
        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                fim = true;
                break;
            }

        }

        //input do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(ev.mouse.x > 230 && ev.mouse.y > 238 && ev.mouse.x < 301 && ev.mouse.y < 340){
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                al_draw_rectangle(230, 238, 301, 340, al_map_rgb(0,0,0), 2);
                sexo = 2;
            }
            else if (ev.mouse.x > 364 && ev.mouse.y > 238 && ev.mouse.x < 435 && ev.mouse.y < 340){
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                al_draw_rectangle(364, 238, 435, 340, al_map_rgb(0,0,0), 2);
                sexo = 1;
            }
        }



        //Input do teclado
         if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_A){
                strcat(nome, "a");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_B){
                strcat(nome, "b");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_C){
                strcat(nome, "c");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_D){
                strcat(nome, "d");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_E){
                strcat(nome, "e");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_F){
                strcat(nome, "f");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_G){
                strcat(nome, "g");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_H){
                strcat(nome, "h");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_I){
                strcat(nome, "i");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_J){
                strcat(nome, "j");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_K){
                strcat(nome, "k");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_L){
                strcat(nome, "l");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_M){
                strcat(nome, "m");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_N){
                strcat(nome, "n");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_O){
                strcat(nome, "o");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_P){
                strcat(nome, "p");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Q){
                strcat(nome, "q");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_R){
                strcat(nome, "r");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_S){
                strcat(nome, "s");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_T){
                strcat(nome, "t");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_U){
                strcat(nome, "u");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_V){
                strcat(nome, "v");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_W){
                strcat(nome, "w");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_X){
                strcat(nome, "x");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Y){
                strcat(nome, "y");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Z){
                strcat(nome, "z");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                strcat(nome, " ");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
             if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                    if(i>1){
                        nome[i-1] = NULL;
                        i--;
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 130, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                        al_draw_text(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 150, ALLEGRO_ALIGN_CENTRE, nome);
                    }
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if (i > 1){
                        contEnter=contEnter+1;
                    imagem = al_load_bitmap("confirma.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);
                    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Eu me chamo%s", nome);

                    if (sexo == 1){
                        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu sou do sexo masculino");
                    }
                    else if (sexo == 2) {
                        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu sou do sexo feminino");
                    }
                    else {
                        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu nao tenho sexo definido");
                    }


                    if(contEnter == 2){
                        break;
                    }


                }
            }

            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT || ev.keyboard.keycode == ALLEGRO_KEY_RSHIFT){
                    contEnter=0;
                    personagem();
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_RCTRL || ev.keyboard.keycode == ALLEGRO_KEY_LCTRL){
                while(i>0){
                    nome[i] = NULL;
                    i--;
                }
                nome[0] = " ";
                sexo = NULL;
                i=1;
                return 3;
            }
         }


        al_flip_display();
    }

}

//variaveis influenciadas  //tipo
    int inteligencia=100;  // = 1
    int fama=100;          // = 2
    int dinheiro=100;      // = 3

typedef struct{
    int num;
    char texto[100];
    int esc1_tipo1;
    int valor1_esc1;
    int esc1_tipo2;
    int valor2_esc1;
    int esc2_tipo1;
    int valor1_esc2;
    int esc2_tipo2;
    int valor2_esc2;
}info;

//dando informações as cartas
info cartas[53] = {
    //{Numero da carta,texto da carta, atributo1, valor do atributo1, atributo2, valor do atributo2, atributo1, valor do atributo 1, atributo2, valor do atributo2},
    {0,"cartas/1.bmp", 11, 20, NULL, NULL, 22, 30, NULL, NULL},
    {1, "cartas/2.bmp", 14, 2, NULL, NULL,14 ,1, NULL, NULL},
    {2, "cartas/3.bmp", 11, 5, NULL, NULL,22 ,5, 23, -20},
    {3, "cartas/4.bmp", 12, 10, NULL, NULL, 22 ,10, NULL, NULL},
    {4, "cartas/5.bmp", 12, -20, 11, 20, 22 ,20, 21, -10}, // TEM QUE AFETAR INTELIGENCIA E FAMA
    {5, "cartas/prova.bmp", 15, 0, NULL, NULL, 25, 1, NULL, NULL},
    {6, "cartas/0.bmp", 15, 0, NULL, NULL, 25, 1, NULL, NULL},
    {7, "cartas/ferias.bmp", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,},
    {8, "cartas/0.bmp", 12, 10, 11, -5,22 ,-10, 21, 10},
    {9, "cartas/0.bmp", 11, 10, 12, -10,22 ,10, 23, -15},
    {10, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {11, "cartas/prova.bmp", 15, 1, NULL, NULL,25 ,0, NULL, NULL},
    {12, "cartas/0.bmp", 15, 1, NULL, NULL, 25, 0, NULL, NULL},
    {13, "cartas/ferias.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {14, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL}, //3 semestre
    {15, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {16, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {17, "cartas/prova.bmp", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {18, "cartas/0.bmp", 15, 1, NULL, NULL, 25,0, NULL, NULL},
    {19, "cartas/ferias.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {20, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},//4 semestre
    {21, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {22, "cartas/0.bmp", 11, 0, NULL, NULL,22 ,0, NULL, NULL},
    {23, "cartas/prova.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {24, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {25, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {26, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL}, //5 semestre
    {27, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {28, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {29, "cartas/prova.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {30, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {31, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {32, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL}, //6 semestre
    {33, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {34, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {35, "cartas/prova.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {36, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {37, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {38, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL}, //7 semestre
    {39, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {40, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {41, "cartas/prova.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {42, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {43, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {44, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL}, //8 semestre
    {45, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {46, "cartas/0.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {47, "cartas/prova.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {48, "cartas/semestre-completo.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {49, "cartas/ferias.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {50, "cartas/semestre-completo.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {51, "cartas/semestre-completo.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    {52, "cartas/semestre-completo.bmp", 11, 0, NULL, NULL, 22 ,0, NULL, NULL},
    };

void escolha(int tipo1, int valor1, int tipo2,int valor2){
    if(tipo1 < 20 || tipo2 < 20){ // SIGNIFICA QUE NÃO É A ESCOLHA 2
            if(tipo1 == 11){
                inteligencia = inteligencia + valor1;
            }
            if(tipo1 == 12){
                fama = fama + valor1;
            }
            if(tipo1 == 13){
                dinheiro = dinheiro + valor1;
            }
            if(tipo2 == 11){
                inteligencia = inteligencia + valor2;
            }
            if(tipo2 == 12){
                fama = fama + valor2;
            }
            if(tipo2 == 13){
                dinheiro = dinheiro + valor2;
            }
            if(tipo1 == 14){ //Criada especificamente para escolher o curso
                curso = valor1;
            }
            if (tipo1 == 15){ //Criada especificamente para provas
                aprovado = valor1;
            }
    }
    if(tipo1 > 20 || tipo2 > 20){ // SIGNIFICA QUE É A ESCOLHA 2
            if(tipo1 == 21){
                inteligencia = inteligencia + valor1;
            }
            if(tipo1 == 22){
                fama = fama + valor1;
            }
            if(tipo1 == 23){
                dinheiro = dinheiro + valor1;
            }
            if(tipo2 == 21){
                inteligencia = inteligencia + valor2;
            }
            if(tipo2 == 22){
                fama = fama + valor2;
            }
            if(tipo2 == 23){
                dinheiro = dinheiro + valor2;
            }
            if(tipo1 == 24){ //Criada especificamente para provas
                curso = valor1;
            }
            if (tipo1 == 25){
                aprovado = valor1;
            }
    }

}
//Variaveis de tempo
    int mes=11;
    int semestre=0;

int comecarjogo(){
        int fluxo = 0;
        imagem = al_load_bitmap(cartas[fluxo].texto);

        ALLEGRO_EVENT_QUEUE *fila_eventos_fluxo = NULL;

        //crição de dispositivos
        fila_eventos_fluxo = al_create_event_queue();

        //registros de sources
        al_register_event_source(fila_eventos_fluxo, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos_fluxo, al_get_mouse_event_source());

        //definição de dispositivos
        al_draw_bitmap(imagem, 0, 0, 0);

        //al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Mes: %d", mes);
        //al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 90, ALLEGRO_ALIGN_LEFT, "Semestre: %d", semestre);

        al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
        al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
        al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);

        al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);

        al_flip_display();


        bool sair = false;
    while(!fim){
        ALLEGRO_EVENT ev;
        al_wait_for_event(fila_eventos, &ev);

            //eventos de saida
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                fim = true;
            }

        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_RCTRL || ev.keyboard.keycode == ALLEGRO_KEY_LCTRL){
                return 3;
            }
        }

        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if(inteligencia <= 0 || fama <= 0 || dinheiro <= 0){
                    fim = true;
                    break;
                }
            }
        }

         //input do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && inteligencia > 0 && fama > 0 && dinheiro > 0){

            if(ev.mouse.x > LARGURA_TELA / 2){
                imagem = al_load_bitmap(cartas[fluxo].texto);
                al_draw_bitmap(imagem, 0, 0, 0);

                escolha(cartas[fluxo].esc2_tipo1, cartas[fluxo].valor1_esc2, cartas[fluxo].esc2_tipo2, cartas[fluxo].valor2_esc2);
                fluxo++;
                mes++;

                //al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Mes: %d", mes);
                //al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 90, ALLEGRO_ALIGN_LEFT, "Semestre: %d", semestre);

                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);

                al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);

                if(fluxo == 1){
                    imagem = al_load_bitmap("cartas/curso.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);

                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
                    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);
                }

                if(mes == 6 || mes == 12){
                    semestre++;
                }

                //PROVAS
                if(mes == 5 || mes == 11){
                    if(curso == 1){
                            if(semestre == 1){
                                imagem = al_load_bitmap("cartas/Exatas/prova1.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                            else if(semestre == 2){
                                imagem = al_load_bitmap("cartas/Exatas/prova2.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                    }
                    else{
                            if(semestre == 1){
                                imagem = al_load_bitmap("cartas/Humanas/prova1.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                            else if(semestre == 2){
                                imagem = al_load_bitmap("cartas/Humanas/prova2.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }

                    }
                }


            }

            else if (ev.mouse.x < LARGURA_TELA / 2){
                imagem = al_load_bitmap(cartas[fluxo].texto);
                al_draw_bitmap(imagem, 0, 0, 0);

                escolha(cartas[fluxo].esc1_tipo1, cartas[fluxo].valor1_esc1, cartas[fluxo].esc1_tipo2, cartas[fluxo].valor2_esc1);
                fluxo++;
                mes++;

                //al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Mes: %d", mes);
                //al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 90, ALLEGRO_ALIGN_LEFT, "Semestre: %d", semestre);

                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);

                al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);

                if(fluxo == 1){
                    imagem = al_load_bitmap("cartas/curso.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);

                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 10, ALLEGRO_ALIGN_LEFT, "Inteligencia: %d", inteligencia);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 30, ALLEGRO_ALIGN_LEFT, "Fama: %d", fama);
                    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 50, ALLEGRO_ALIGN_LEFT, "Dinheiro: %d", dinheiro);
                    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA/2, 435, ALLEGRO_ALIGN_CENTER, "%s", nome);
                }

                if(mes == 6 || mes == 12){
                    semestre++;
                }
                //PROVAS
                if(mes == 5 || mes == 11){
                    if(curso == 1){
                        if(semestre == 1){
                                imagem = al_load_bitmap("cartas/Exatas/prova1.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                            else if(semestre == 2){
                                imagem = al_load_bitmap("cartas/Exatas/prova2.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                    }
                    else{
                        if(semestre == 1){
                                imagem = al_load_bitmap("cartas/Humanas/prova1.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                            else if(semestre == 2){
                                imagem = al_load_bitmap("cartas/Humanas/prova2.bmp");
                                al_draw_bitmap(imagem, 0, 0, 0);
                            }
                    }
                }



            }
        }

        al_flip_display();

        if(fluxo>=50){
                imagem = al_load_bitmap("cartas/0.bmp");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 20, 310, ALLEGRO_ALIGN_LEFT, "End");
                al_flip_display();
                fluxo++;
                if(mes==2){
                    fim = true;
                }
        }
            if(semestre != 1){
                    if((mes == 6 || mes == 12) && aprovado == 0){
                    imagem = al_load_bitmap("cartas/semestre-reprovado.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);
                }
                else if((mes == 6 || mes == 12) && aprovado == 1){
                    imagem = al_load_bitmap("cartas/semestre-completo.bmp");
                    al_draw_bitmap(imagem, 0, 0, 0);
                }
            }
        if(mes == 12){
            mes = 0;
        }

         if(inteligencia <= 0 || dinheiro <= 0 || fama <= 0){
                    al_clear_to_color(al_map_rgb(255,255,255));
                    al_draw_text(fontePixel, al_map_rgb(0,0,0), LARGURA_TELA/3, ALTURA_TELA/2, ALLEGRO_ALIGN_LEFT, "Voce Perdeu =(");
            }

    }

}

int creditos(){
    while(true){
            ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Feito por:");
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 140, ALLEGRO_ALIGN_CENTRE, "Thiago");
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 180, ALLEGRO_ALIGN_CENTRE, "Richard");
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 220, ALLEGRO_ALIGN_CENTRE, "Guilherme");
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 260, ALLEGRO_ALIGN_CENTRE, "& Carol");
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 410, ALLEGRO_ALIGN_CENTRE, "Irlanda");
    al_draw_textf(fontePixelGrande, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 450, ALLEGRO_ALIGN_CENTRE, "2019");
    al_draw_textf(fontePixel, al_map_rgb(0, 0, 0), 100, 460, ALLEGRO_ALIGN_CENTRE, "Ctrl para voltar");

    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                break;
            }

        }
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
            break;
        }
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_RCTRL || ev.keyboard.keycode == ALLEGRO_KEY_LCTRL){
                return 3;
            }
        }

        al_flip_display();
    }

}

int thanos(){
    al_destroy_bitmap(imagem);
    al_destroy_bitmap(prova);
    al_destroy_display(janela);
    al_destroy_font(fontePixelGrande);
    al_destroy_font(fontePixel);
    al_destroy_event_queue(fila_eventos);
    al_destroy_sample(sample);
    al_destroy_audio_stream(musica);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_audio();
}
