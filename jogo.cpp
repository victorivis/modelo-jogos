#include "jogo.h"
#include "global.h"

#include <iostream>

Jogo::Jogo(){

}

Jogo::~Jogo(){

}

int Jogo::loopPrincipal(){
    Tela tela;
    bool rodarLoop=true;
    SDL_Event evento;
    
    SDL_Texture* alface = tela.carregarTextura("alface.png");
    player = Entidade(alface, Vector2(16, 16), Vector2(300, 300), Vector2(0, 0));

    player.adicionarAnimacao("correrEsquerda", infoAnimacao(Vector2(0, 0), 200, 2));
    player.adicionarAnimacao("correrDireita", infoAnimacao(Vector2(0, 16), 200, 2));
    player.selecionarAnimacao("correrEsquerda");

    int tempoInicial = SDL_GetTicks();
    int deltaT = 1000 / FPS;
    while(rodarLoop){

        if(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT) rodarLoop=false;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodarLoop = false; break;
				}
			}
        }

        //Estabilizando a taxa de fps
        int tempoAtual = SDL_GetTicks();
        int delta = tempoAtual - tempoInicial;
        
        if(delta < deltaT){
            SDL_Delay(deltaT - delta);
            delta = deltaT;
        }
        
        atualizar(delta);
        desenhar(tela);

        tempoInicial = tempoAtual;
    }

    return 0;
}

void Jogo::atualizar(int tempo){
    player.atualizar(tempo);
}

void Jogo::desenhar(Tela &tela){
    player.mostrar(tela);
    tela.apresentar();
}