#include "jogo.h"
#include "animacao.h"
#include <iostream>

Jogo::Jogo(){

}

Jogo::~Jogo(){

}

int Jogo::loopPrincipal(){
    Tela tela;
    bool rodarLoop=true;
    SDL_Texture* alface = tela.carregarTextura("alface.png");
    Animacao imgAlface(alface, Vector2(16, 16), Vector2(300, 300), Vector2(0, 16), 3, 1000);

    SDL_Event evento;

    int tempoInicial = SDL_GetTicks();

    while(rodarLoop){
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT) rodarLoop=false;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodarLoop = false; break;
				}
			}
        }

        int tempoAtual = SDL_GetTicks();
        imgAlface.atualizar(tempoAtual - tempoInicial);
        imgAlface.mostrar(tela);
        desenhar(tela);

        tempoInicial = tempoAtual;

        //SDL_Delay(100);
    }

    return 0;
}

void Jogo::desenhar(Tela &tela){
    tela.apresentar();
}