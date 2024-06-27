#include "jogo.h"
#include "global.h"
#include "input.h"
#include "mapa.h"

#include <iostream>

Jogo::Jogo(){

}

Jogo::~Jogo(){

}

void medirFPS(int& tempoDecorrido){
    static int tempoAquiDentro=0;
    static int framesAtuais=0;
    
    framesAtuais++;
    tempoAquiDentro+=tempoDecorrido;
    if(tempoAquiDentro >= 1000){
        printf("FPS: %d\n", framesAtuais);
        tempoAquiDentro -= 1000;
        framesAtuais=0;
    }
}

int Jogo::loopPrincipal(){
    Tela tela;
    Input input;
    _mapa.carregarMapa(tela, "mapa-inicial");

    bool rodarLoop=true;
    SDL_Event evento;
    
    SDL_Texture* alface = tela.carregarTextura("assets/sprites/alface.png");
    player = Player(alface, Vector2(16, 16), Vector2(300, 300), Vector2(0, 0));

    int deltaT = 1000 / FPS;
    int tempoInicial = SDL_GetTicks();
    while(rodarLoop){

        input.resetar();
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT) rodarLoop=false;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodarLoop = false; break;
				}

                //player.executarControles(evento.key.keysym.sym);
			}

            
            input.receberInput(evento);
        }
        player.executarControles(input);

        //Estabilizando a taxa de fps
        int tempoAtual = SDL_GetTicks();
        int delta = tempoAtual - tempoInicial;
        
        if(delta < deltaT){
            SDL_Delay(deltaT - delta);
            delta = deltaT;
        }

        atualizar(delta);
        medirFPS(delta);
        desenhar(tela);

        tempoInicial = tempoAtual;
    }

    return 0;
}

void Jogo::atualizar(int tempo){
    player.atualizar(tempo);
    _mapa.atualizar(tempo);
    _mapa.lidarColisao(player);
}

void Jogo::desenhar(Tela &tela){
    _mapa.mostrar(tela);
    player.mostrar(tela);
    tela.apresentar();
}