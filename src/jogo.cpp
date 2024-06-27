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
    int tempoInicial = SDL_GetTicks();
    _indice = 0;
    _projeteis = std::vector<Projetil>(6);

    while(rodarLoop){

        input.resetar();
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT) rodarLoop=false;

			if(evento.type == SDL_KEYDOWN){
				switch(evento.key.keysym.sym){
					case SDLK_ESCAPE: rodarLoop = false; break;
				}
			}

            if(evento.type == SDL_MOUSEBUTTONDOWN){
                if(evento.button.button == SDL_BUTTON_LEFT){
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    Retangulo colisaoPlayer = player.getCaixaColisao();
                    Vector2 centroPlayer(colisaoPlayer.getCentroX(), colisaoPlayer.getCentroY());

                    float deltaX = (mouseX - centroPlayer.x);
                    float deltaY = (mouseY - centroPlayer.y);

                    if(deltaX == 0){
                        deltaX = 0.1;
                    }

                    int velocidade = deltaX > 0 ? 1 : -1;

                    float angulo = deltaY/deltaX;

                    std::cout << "Delta: " << deltaX << " " << deltaY << " angulo: " << angulo << "\n";

                    _projeteis[_indice] = Projetil(tela.carregarTextura("assets/sprites/bala.png"), Vector2(8, 8), centroPlayer, Vector2(0, 0), angulo, velocidade);
                    _indice = (_indice + 1) % _projeteis.size();
                }

                if(evento.button.button == SDL_BUTTON_RIGHT){
                    for(int i=0; i<_projeteis.size(); i++){
                        _projeteis[i].desativarProjetil();
                    }
                }
            }
            
            input.receberInput(evento);

            /*
            if(input.foiPressionada(SDL_SCANCODE_MINUS)){
                aumentarSprite++;
                _mapa.recarregar(tela, "mapa-inicial");
            }
            if(input.foiPressionada(SDL_SCANCODE_EQUALS)){
                if(aumentarSprite>1){
                    aumentarSprite--;
                    _mapa.recarregar(tela, "mapa-inicial");
                }
            }
            */
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

    for(int i=0; i<_projeteis.size(); i++){
        _projeteis[i].atualizar(tempo);
    }
    
    //for(int i=0; i<_projeteis.size(); i++){
    //    for(int j=0; j<_mapa._colisoes.size(); i++){
    //        _projeteis[i].lidarColisao(_mapa._colisoes[j]);
    //    }
    //    _projeteis[i].atualizar(tempo);
    //}
}

void Jogo::desenhar(Tela &tela){
    _mapa.mostrar(tela);
    player.mostrar(tela);
    tela.apresentar();

    for(int i=0; i<_projeteis.size(); i++){
        _projeteis[i].mostrar(tela);
    }
}