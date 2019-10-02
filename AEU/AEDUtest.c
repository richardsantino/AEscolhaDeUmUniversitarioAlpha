#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define LARGURA_TELA 640
#define ALTURA_TELA 480

void inicializacao(){

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    al_init_primitives_addon();
	float points[8] = {0.0f, 0.0f, 100.00f, 100.00f, 200.00f, 100.00f, 640.00f, 150.00f};
	float polygon[8] = { 640.0f, 100.0f, 640.0f, 300.0f, 380.0f, 350.0f, 200.0f, 200.0f };

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

}

// Variáveis globais
    //Necessarias
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_FONT *fonte = NULL;
    ALLEGRO_FONT *fontePequena = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *imagem = NULL;
    bool fim = false;

    //Variaveis de personagem
    char nome[200] = " ";
    int i=1;
    int sexo;

    int valor=0;

int main(){
    inicializacao();

    //crição de dispositivos
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    fonte = al_load_font("arial.ttf", 30, 0);
    fontePequena = al_load_font("arial.ttf", 20, 0);
    fila_eventos = al_create_event_queue();
    imagem = al_load_bitmap("pi.bmp");

    //registros de sources
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    //definição de dispositivos
    al_draw_bitmap(imagem, 0, 0, 0);
    al_set_window_title(janela, "Vida De Universitario BETA");

    al_flip_display();

    valor = menu();

    if(valor == 1){
            personagem();
            comecarjogo();

    }
    else if (valor == 2){
            creditos();
    }

    thanos();

    return 0;
}

int menu(){
    while(!fim){
        ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fim = true;
        }

        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            // START GAME
            if(ev.mouse.y > 252 && ev.mouse.y < 306 && ev.mouse.x > 243 && ev.mouse.x < 437){
                    valor = 1;
                    return valor;
            }
            // CREDITOS
            if(ev.mouse.y > 401 && ev.mouse.y < 439 && ev.mouse.x > 456 && ev.mouse.x < 616){
                al_draw_text(fonte, al_map_rgb(252, 15, 192), LARGURA_TELA / 6, ALTURA_TELA / 1.75, ALLEGRO_ALIGN_CENTRE, "CREDITOS");
                valor = 2;
                return valor;
            }

            // QUIT
            if(ev.mouse.y > 324 && ev.mouse.y < 369 && ev.mouse.x > 273 && ev.mouse.x < 410){
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

    imagem = al_load_bitmap("personagem.bmp");
    al_draw_bitmap(imagem, 0, 0, 0);
    al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
    while(true){
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

        //input do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(ev.mouse.x > LARGURA_TELA / 2 && ev.mouse.y < 397){
                al_draw_text(fonte, al_map_rgb(155, 155, 155), 400, 400, ALLEGRO_ALIGN_CENTRE, "Feminino");
                al_draw_filled_rectangle(180,400,320,450,al_map_rgb(187, 222, 251));
                sexo = 2;
            }
            else if (ev.mouse.x < LARGURA_TELA / 2 && ev.mouse.y < 397){
                al_draw_text(fonte, al_map_rgb(155, 155, 155), 250, 400, ALLEGRO_ALIGN_CENTRE, "Masculino");
                al_draw_filled_rectangle(330,400,470,450,al_map_rgb(187, 222, 251));
                sexo = 1;
            }
        }



        //Input do teclado
         if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(ev.keyboard.keycode == ALLEGRO_KEY_A){
                strcat(nome, "a");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_B){
                strcat(nome, "b");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_C){
                strcat(nome, "c");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_D){
                strcat(nome, "d");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_E){
                strcat(nome, "e");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_F){
                strcat(nome, "f");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_G){
                strcat(nome, "g");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_H){
                strcat(nome, "h");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_I){
                strcat(nome, "i");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_J){
                strcat(nome, "j");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_K){
                strcat(nome, "k");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_L){
                strcat(nome, "l");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_M){
                strcat(nome, "m");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_N){
                strcat(nome, "n");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_O){
                strcat(nome, "o");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_P){
                strcat(nome, "p");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Q){
                strcat(nome, "q");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_R){
                strcat(nome, "r");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_S){
                strcat(nome, "s");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_T){
                strcat(nome, "t");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_U){
                strcat(nome, "u");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_V){
                strcat(nome, "v");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_W){
                strcat(nome, "w");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_X){
                strcat(nome, "x");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Y){
                strcat(nome, "y");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_Z){
                strcat(nome, "z");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                strcat(nome, " ");
                al_draw_bitmap(imagem, 0, 0, 0);
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                i++;
            }
             if(ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                    if(i>1){
                        nome[i-1] = NULL;
                        i--;
                        al_draw_bitmap(imagem, 0, 0, 0);
                        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Meu nome:");
                        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 100, ALLEGRO_ALIGN_CENTRE, nome);
                    }
            }
            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if (i > 1){
                        contEnter=contEnter+1;
                    al_clear_to_color(al_map_rgb(187,222,251));
                    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 50, ALLEGRO_ALIGN_CENTRE, "Isto esta certo?");
                    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 200, ALLEGRO_ALIGN_CENTRE, "Eu me chamo%s", nome);

                    if (sexo == 1){
                        al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu sou do sexo masculino");
                    }
                    else if (sexo == 2) {
                        al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu sou do sexo feminino");
                    }
                    else {
                        al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 230, ALLEGRO_ALIGN_CENTRE, "Eu nao tenho sexo definido");
                    }

                    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 400, ALLEGRO_ALIGN_CENTRE, "Pressione Enter para iniciar");
                    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 430, ALLEGRO_ALIGN_CENTRE, "Pressione Shift para voltar");


                    if(contEnter == 2){
                        break;
                    }


                }
            }

            if(ev.keyboard.keycode == ALLEGRO_KEY_LSHIFT || ev.keyboard.keycode == ALLEGRO_KEY_RSHIFT){
                    contEnter=0;
                    personagem();
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
    char escolha1[100];
    int esc1_tipo1;
    int valor1_esc1;
    char escolha2[100];
    int esc2_tipo1;
    int valor1_esc2;

}info;

//dando informações as cartas
info cartas[2] = {
    {0,"O que fazer essa semana", "Estudar para o ENEM", 1, 20 , "Ir para uma feira de tecnologia", 2, 30},
    {1,"Carta 2","Escolha indefinida", 0, 0, "Escolha indefinida" ,0 ,0}
    };

void escolha(int tipo,int valor){
    if(tipo == 1){
        inteligencia = inteligencia + valor;
    }
    if(tipo == 2){
        fama = fama + valor;
    }

}

int comecarjogo(){
        imagem = al_load_bitmap("estilo.bmp");
        //imagem = al_load_bitmap("fluxo.bmp");

        ALLEGRO_EVENT_QUEUE *fila_eventos_fluxo = NULL;

        //crição de dispositivos
        fila_eventos_fluxo = al_create_event_queue();
        //imagem = al_load_bitmap("fluxo.bmp");

        //registros de sources
        al_register_event_source(fila_eventos_fluxo, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos_fluxo, al_get_mouse_event_source());

        //definição de dispositivos
        al_draw_bitmap(imagem, 0, 0, 0);

        al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 20, ALLEGRO_ALIGN_LEFT, "inteligencia: %d", inteligencia);
        al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 40, ALLEGRO_ALIGN_LEFT, "fama: %d", fama);
        al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 60, ALLEGRO_ALIGN_LEFT, "dinheiro: %d", dinheiro);

        al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 200, 150, ALLEGRO_ALIGN_LEFT, "%s", cartas[0].texto);
        al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 350, 310, ALLEGRO_ALIGN_LEFT, "%s", cartas[0].escolha2);
        al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 310, ALLEGRO_ALIGN_LEFT, "%s", cartas[0].escolha1);

        al_flip_display();

        int fluxo = 0;
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

         //input do mouse
        if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(ev.mouse.x > LARGURA_TELA / 2){
                al_draw_bitmap(imagem, 0, 0, 0);
                escolha(cartas[fluxo].esc2_tipo1, cartas[fluxo].valor1_esc2);
                fluxo++;

                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 20, ALLEGRO_ALIGN_LEFT, "inteligencia: %d", inteligencia);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 40, ALLEGRO_ALIGN_LEFT, "fama: %d", fama);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 60, ALLEGRO_ALIGN_LEFT, "dinheiro: %d", dinheiro);

                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 200, 150, ALLEGRO_ALIGN_LEFT, "%s", cartas[fluxo].texto);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 350, 310, ALLEGRO_ALIGN_LEFT, "%s", cartas[fluxo].escolha2);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 310, ALLEGRO_ALIGN_LEFT, "%s", cartas[fluxo].escolha1);
            }
            else if (ev.mouse.x < LARGURA_TELA / 2){
                al_draw_bitmap(imagem, 0, 0, 0);

                escolha(cartas[fluxo].esc1_tipo1, cartas[fluxo].valor1_esc1);
                fluxo++;

                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 20, ALLEGRO_ALIGN_LEFT, "inteligencia: %d", inteligencia);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 40, ALLEGRO_ALIGN_LEFT, "fama: %d", fama);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 60, ALLEGRO_ALIGN_LEFT, "dinheiro: %d", dinheiro);

                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 200, 150, ALLEGRO_ALIGN_LEFT, "%s", cartas[fluxo].texto);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 350, 310, ALLEGRO_ALIGN_LEFT, "%s", cartas[fluxo].escolha2);
                al_draw_textf(fontePequena, al_map_rgb(255, 0, 0), 20, 310, ALLEGRO_ALIGN_LEFT, "%s", cartas[fluxo].escolha1);

            }
        }

        al_flip_display();

    }
}

int creditos(){
    while(true){
            ALLEGRO_EVENT ev;

        al_wait_for_event(fila_eventos, &ev);

    al_clear_to_color(al_map_rgb(187,222,251));
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 80, ALLEGRO_ALIGN_CENTRE, "Feito por:");
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 140, ALLEGRO_ALIGN_CENTRE, "Thiabot");
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 180, ALLEGRO_ALIGN_CENTRE, "Perninha");
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 220, ALLEGRO_ALIGN_CENTRE, "Banheiro");
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 260, ALLEGRO_ALIGN_CENTRE, "& Carol");
    al_draw_textf(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, 450, ALLEGRO_ALIGN_CENTRE, "2019");

    if(ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                break;
            }

        }

        al_flip_display();
    }
}

int thanos(){
    al_destroy_bitmap(imagem);
    al_destroy_display(janela);
    al_destroy_font(fonte);
    al_destroy_font(fontePequena);
    al_destroy_event_queue(fila_eventos);
}
