#include "jogo.h"
#include <iostream>

Jogo::Jogo(){

}

Jogo::~Jogo(){

}

int Jogo::loopPrincipal(){
    Imagens imagens;
    bool rodarLoop=true;
    SDL_Texture* tex = imagens.carregarTextura("alface.png");

    SDL_Event evento;
    while(rodarLoop){
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT) rodarLoop=false;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodarLoop = false; break;
				}
			}
        }

        SDL_RenderCopy(imagens.getRenderer(), tex, NULL, NULL);
        desenhar(imagens);
    }

    return 0;
}

void Jogo::desenhar(Imagens &imagens){
    imagens.apresentarTela();
}