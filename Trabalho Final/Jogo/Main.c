#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool inicializar();             //Variaveis globais

const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *PLANO_FUNDO = NULL;
ALLEGRO_EVENT_QUEUE *EVENTOS=NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_AUDIO_STREAM *musica = NULL;
ALLEGRO_SAMPLE *sample = NULL;

//---------------------------------------------------------------------------------------------------------------------------

bool inicializar();

int main(void)
{
    bool sair=false;

    int tecla = 0;

    if (!inicializar()){

        return -1;
    }
    al_attach_audio_stream_to_mixer(musica, al_get_default_mixer());
    al_set_audio_stream_playing(musica, true);
    al_draw_bitmap(PLANO_FUNDO, 0,0,0);


    // VARIAVEIS ---------------------------------------------------------------------------------------
    int raio= 23;  // Variaveis do personagem
    int x_bol= 20;
    int y_bol= 400;
    int borda_x=20;
    int borda_y=20;

     // Variaveis de teste
    int a=0;
    int contador=0;

    // COORDENADAS DOS CUBOS (escada)
    int x10=0,x11=200,x12=243,x13=286;       // O ULTIMO NUMERO DO NOME DA VARIAVEL
    int x20=640,x21=240,x22=283,x23=326;     // IDENTIFICA QUAL RETANGULO É.
    int y10=480,y11=420,y12=420,y13=420;
    int y20=420,y21=380,y22=340,y23=300;
    // COORDENADAS DOS TRIANGULOS
    int tx11=346,tx12=390;  // A PRIMEIRA COLUNA PERTENCE AO PRIMEIRO
    int ty11=420,ty12=420;  // SE BASEIE TAMBÉM PELO ULTIMO NUMERO DA VARIAVEL
    int tx21=386,tx22=430;
    int ty21=420,ty22=420;
    int tx31=365,tx32=405;
    int ty31=348,ty32=348;
    // COORDENADAS PARA A PRIMEIRA RAMPA
    int l1_x1=450,l1_y1=378,l1_x2=643,l1_y2=378;// Linha
    int q1_x1=450,q1_y1=420,q1_x2=490,q1_y2=380;// Cubo
    int q2_x1=597,q2_y1=420,q2_x2=637,q2_y2=380;// Cubo
//----------VARIAVEIS SEGUNDA TELA-----------------------------------------------------------------
    int Qx1=50,Qy1=0,Qx2=90,Qy2=40;
    int qx1=200,qy1=420,qx2=240,qy2=380;
    int plat2_x1=220,plat2_y1=220,plat2_x2=260,plat2_y2=260;
    int plat3_x1=340,plat3_y1=280,plat3_x2=380,plat3_y2=320;



    // --------------------------------------------------------------------------------------------------
   while (!sair) //LOOP PRINCIPAL
    {

        while(!al_is_event_queue_empty(EVENTOS)) //Loop do registro de Eventos
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(EVENTOS, &evento);
            if(evento.type == ALLEGRO_EVENT_KEY_DOWN){ // CONFIGURAÇÃO DAS TECLAS DE CONTROLE
                switch(evento.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                     tecla=1;
                     break;
                case ALLEGRO_KEY_DOWN:
                     tecla=2;
                     break;
                case ALLEGRO_KEY_LEFT:
                     tecla=3;
                     break;
                case ALLEGRO_KEY_RIGHT:
                    tecla=4;
                    break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }

        }


        if (tecla){
            al_draw_bitmap(PLANO_FUNDO, 0,0,0); // MOVIMENTAÇÃO DO PERSONAGEM(direções)
            switch(tecla){
            case 1:y_bol=y_bol-80;
            break;
            case 2: tecla=0;
            break;
            case 3: x_bol=x_bol-40;
            break;
            case 4: x_bol=x_bol+40;
            break;

            }
             tecla=y_bol++; // BOLINHA VOLTA PARA O CHÃO
        }

       al_draw_filled_rectangle(x10, y10, x20, y20, al_map_rgb(126, 79, 52)); //CHÃO DO JOGO

        // LIMITES DO JOGO
        if(y_bol>=398){
            y_bol=398;
        }
        if(x_bol<0){
            x_bol=23;
        }
        if(y_bol<=180){ // Para a bolinha não subir muito
            y_bol=180;
        }

        if(x_bol>640){
         x_bol=23;
         a=1;

        }


// PRIMITIVAS GRAFICAS DA SEGUNDA TELA DO JOGO -----------------------------------------------------------------------------------------------------


        if(a==1){
// FINALIZAÇÕES DAS PRIMITIVAS GRÁFICAS ---------------------------------------------------------------------------------
         tx11=0,tx12=0; // AQUI OS TRIANGULOS RECEBEM ZERO PARA DESAPARECEREM DA ULTIMA TELA
         ty11=0,ty12=0; // QUANDO A BOLINHA IR PARA A SEGUNDA TELA;
         tx21=0,tx22=0;
         ty21=0,ty22=0;
         tx31=0,tx32=0;
         ty31=0,ty32=0;

         x11=0,x12=0,x13=0; // ESCADA
         x21=0,x22=0,x23=0;
         y11=0,y12=0,y13=0;
         y21=0,y22=0,y23=0;

         l1_x1=0,l1_y1=0,l1_x2=0,l1_y2=0;// Linha 1
         q1_x1=0,q1_y1=0,q1_x2=0,q1_y2=0;// Cubo  1
         q2_x1=0,q2_y1=0,q2_x2=0,q2_y2=0;// Cubo 2
//--------------------------------------------------------------
// PRIMITIVAS GRÁFICAS DA 2° TELA



         al_draw_filled_rectangle(Qx1,Qy1,Qx2,Qy2, al_map_rgb(255, 5, 5));
         Qy1++;
         Qy2++;
         if((Qx1>x_bol+borda_x-1)|| (Qx2<x_bol+borda_x-1)||
         (Qy1>y_bol+borda_y-1)||(Qy2<y_bol+borda_y-1)){
         }
         else{
         al_clear_to_color(al_map_rgb(0, 0, 0));

         al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2,200,
         ALLEGRO_ALIGN_CENTRE, "GAME OVER");
         al_flip_display();

         al_rest(3.5);
         return 0;
        }

         al_draw_filled_rectangle(qx1,qy1,qx2,qy2, al_map_rgb(255, 0, 0));
         qx1++;
         qx2++;
         if((qx1+40>x_bol+borda_x-1)||(qx2+40<x_bol+borda_x-1)||//
             (y_bol>qy2+40)||(y_bol>qy1+40)){
         }
         else{
         al_clear_to_color(al_map_rgb(0, 0, 0));

         al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2,200,
         ALLEGRO_ALIGN_CENTRE, "GAME OVER");
         al_flip_display();

         al_rest(3.5);
         return 0;
        }



         al_draw_filled_rectangle(plat2_x1,plat2_y1,plat2_x2,plat2_y2, al_map_rgb(0, 3, 255));
         plat2_y1++;
         plat2_y2++;

         if((plat2_x1>x_bol+borda_x-1)|| (plat2_x2<x_bol+borda_x-1)||
            (plat2_y1>y_bol+borda_y-1)||(plat2_y2<y_bol+borda_y-1)){
         }
         else{
         al_clear_to_color(al_map_rgb(0, 0, 0));

         al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2,200,
         ALLEGRO_ALIGN_CENTRE, "GAME OVER");
         al_flip_display();

         al_rest(3.5);
         return 0;
        }
         al_draw_filled_rectangle(plat3_x1,plat3_y1,plat3_x2,plat3_y2, al_map_rgb(0, 3, 255));
         plat3_x1++;
         plat3_x2++;
         if((plat3_x1>x_bol+borda_x-1)|| (plat3_x2<x_bol+borda_x-1)||
            (plat3_y1>y_bol+borda_y-1)||(plat3_y2<y_bol+borda_y-1)){
         }
         else{
         al_clear_to_color(al_map_rgb(0, 0, 0));

         al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2,200,
         ALLEGRO_ALIGN_CENTRE, "GAME OVER");
         al_flip_display();

         al_rest(3.5);
         return 0;
        }


         contador=1;

        }
//------------- CUBOS VOLTAM A SUA POSIÇÃO INICIAL
         if(qx1&&qx2>=640){
            qx1=200;
            qx2=240;
        }
        if(Qy1&&Qy2>=480){
            Qy1=50;
            Qy2=90;
        }
        if( plat2_y1&&plat2_y2>=480){
          plat2_y1=220;
          plat2_y2=260;
        }
        if( plat3_x1&&plat3_x2>=640){
          plat3_x1=340;
          plat3_x2=380;
        }





//----------------------------------------------------------------------------------------------------------------
// PRIMITIVAS GRAFICAS DA PRIMEIRA TELA E SUAS COLISÕES

      al_draw_filled_circle(x_bol,y_bol,raio, al_map_rgb(63,72,204));// PERSONAGEM (bolinha azul)


      al_draw_filled_rectangle(x11, y11, x21, y21, al_map_rgb(190,122,87));
       if((x11>x_bol+borda_x-1)||(y21>y_bol+borda_y-1)||
         (x21<x_bol+borda_x-1)||(y11<y_bol+borda_y-1)){
         }
       else{
        x_bol=x_bol-7;
        y_bol--;
      }
      al_draw_filled_rectangle(x12, y12, x22, y22, al_map_rgb(190,122,87));
       if((x12>x_bol+borda_x-1)||(y22>y_bol+borda_y-1)||
         (x22<x_bol+borda_x-1)||(y12<y_bol+borda_y-1)){
         }
       else{
        x_bol=x_bol-40;
        y_bol--;
     }

     al_draw_filled_rectangle(x13, y13, x23, y23, al_map_rgb(190,122,87));
      if((x13>x_bol+borda_x-1)||(y23>y_bol+borda_y-1)||
         (x23<x_bol+borda_x-1)||(y13<y_bol+borda_y-1)){
         }
      else{
        x_bol=x_bol;
        y_bol--;
     }


                             //x1,   y1,   x2,   y2,    x3,    y3,
      al_draw_filled_triangle(tx11, ty11, tx21, ty21, tx31, ty31, al_map_rgb(128,128,128)); //PRIMEIRO TRIANGULO
       if((tx11>x_bol+borda_x-1)||(ty31+2>y_bol+borda_y-1)||
          (tx21<x_bol+borda_x-1)||(ty21<y_bol+borda_y-1)){
         }
       else{
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2,200,
        ALLEGRO_ALIGN_CENTRE, "GAME OVER");
        al_flip_display();

        al_rest(2.0);
        return 0;
       }


      al_draw_filled_triangle(tx12, ty12, tx22, ty22, tx32, ty32, al_map_rgb(128,128,128)); // SEGUNDO TRIANGULO
      if((tx12>x_bol+borda_x-1)||(ty32+2>y_bol+borda_y-1)||
          (tx22<x_bol+borda_x-1)||(ty22<y_bol+borda_y-1)){
         }
       else{
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_text(fonte, al_map_rgb(255, 0, 0), LARGURA_TELA / 2,200,
        ALLEGRO_ALIGN_CENTRE, "GAME OVER");
        al_flip_display();

        al_rest(3.5);
        return 0;
       }


      // PRIMEIRA RAMPA DO JOGO

      // Linha:      x1,  y1,    x2,    y2, cor, espessura
      al_draw_line(l1_x1, l1_y1, l1_x2, l1_y2, al_map_rgb(255, 255, 255), 3.0);
      if((l1_x1>x_bol+borda_x-1)||(l1_y2>y_bol+borda_y-1)||
         (l1_x2<x_bol+borda_x-1)||(l1_y1<y_bol+borda_y-1)){
         }
       else{
        x_bol=x_bol;
        y_bol--;
      }


      al_draw_filled_rectangle(q1_x1, q1_y1, q1_x2, q1_y2, al_map_rgb(190,122,87) );
      if((q1_x1>x_bol+borda_x-1)||(q1_y2>y_bol+borda_y-1)||
         (q1_x2<x_bol+borda_x-1)||(q1_y1<y_bol+borda_y-1)){
         }
      else{
        x_bol=x_bol;
        y_bol--;
      }

      al_draw_filled_rectangle(q2_x1, q2_y1, q2_x2, q2_y2, al_map_rgb(190,122,87) );
      if((q2_x1>x_bol+borda_x-1)||(q2_y2>y_bol+borda_y-1)||
         (q2_x2<x_bol+borda_x-1)||(q2_y1<y_bol+borda_y-1)){
         }
       else{
        x_bol=x_bol;
        y_bol--;
       }
//---------------------------------------------------------------------------------------------------------------------------


      if(x_bol>=620 && contador==1){ // PARA FECHAR NA SEGUNDA TELA
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2,200,
        ALLEGRO_ALIGN_CENTRE, "FIM DE JOGO");
        al_flip_display();
      //  al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

        al_rest(2.0);
        return 0;

        }

      al_flip_display();


      // -------------------------------------------------------------

      al_rest(0.005);
   }

    al_destroy_display(janela);
    al_destroy_event_queue(EVENTOS);
    al_destroy_audio_stream(musica);

    return 0;
}







//INICIALIZAÇÕES
bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "ERRO AO INICIALIZAR A BIBLIOTECA ALLEGRO.\n");
        return false;
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "ERRO AO INICIALIZAR: add-on de primitivas.\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "ERRO AO CARREGAR: add-on allegro_image.\n");
        return false;
    }

      if (!al_install_keyboard())
    {
        fprintf(stderr, "ERRO AO CARREGAR O TECLADO.\n");
        return false;
    }

     janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "ERRO AO CRIAR JANELA.\n");
        return false;
    }

    al_init_font_addon();

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar allegro_ttf.\n");
        return false;
    }

    al_set_window_title(janela, "TRABALHO FINAL");

    EVENTOS = al_create_event_queue();
    if (!EVENTOS)
    {
        fprintf(stderr, "ERRO AO CRIAR EVENTOS.\n");
        al_destroy_display(janela);
        return false;
    }

    fonte = al_load_font("arial.ttf", 75, 0);
    if (!fonte)
    {
        fprintf(stderr, "ERRO AO CARREGAR A FONTE. \n");
        return false;
    }

     if (!al_install_audio())
    {
        fprintf(stderr, "ERRO AO CARREGAR O AUDIO.\n");
        return false;
    }

    if (!al_init_acodec_addon())
    {
        fprintf(stderr, "ERRO AO CARREGAR CODECS DE AUDIO.\n");
        return false;
    }


    musica = al_load_audio_stream("musica.ogg", 4, 1024);

    if (!musica)
    {
        fprintf(stderr, "Falha ao carregar audio.\n");
        al_destroy_event_queue(EVENTOS);
        al_destroy_display(janela);
        al_destroy_sample(sample);
        return false;
    }
     if (!al_reserve_samples(1))
    {
        fprintf(stderr, "ERRO AO CARRREGAR SOM.\n");
        return false;
    }



    PLANO_FUNDO=al_load_bitmap("Imagem.png");
    if(!PLANO_FUNDO){
        fprintf(stderr," ERRO AO CARREGAR IMAGEM DE FUNDO.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(EVENTOS);
        return false;
    }

     al_register_event_source(EVENTOS, al_get_keyboard_event_source());
     al_register_event_source(EVENTOS, al_get_display_event_source(janela));

    return true;
}
