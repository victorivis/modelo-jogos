#include "jogo.h"
#include "global.h"
#include "input.h"
#include "mapa.h"

#include <cmath>
#include <iostream>

Jogo::Jogo(){

}

Jogo::~Jogo(){

}

void medirFPS(int& tempoDecorrido, Tela& tela){
    static int tempoAquiDentro=0;
    static int framesAtuais=0;
    
    framesAtuais++;
    tempoAquiDentro+=tempoDecorrido;
    if(tempoAquiDentro >= 1000){
        char nomeAplicativo[100];
        sprintf(nomeAplicativo, "Uma simples game engine - FPS: %d", framesAtuais);
        SDL_SetWindowTitle(tela.getWindow(), nomeAplicativo);
        tempoAquiDentro -= 1000;
        framesAtuais=0;
    }
}

void atirar(Tela &tela, Player& player, std::vector<Projetil>& projeteis, int &indice){
    //static int _indice = 0;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    Retangulo colisaoPlayer = player.getCaixaColisao();
    Vector2 centroPlayer(colisaoPlayer.getCentroX(), colisaoPlayer.getCentroY());

    float deltaX = mouseX+tela.getCameraX() - centroPlayer.x;
    float deltaY = mouseY+tela.getCameraY() - centroPlayer.y;

    float hipotenusa = sqrt(deltaX * deltaX + deltaY * deltaY);
    if(hipotenusa == 0){
        hipotenusa = 1;
    }

    int velocidade = 10;
    float seno = deltaY/hipotenusa;
    float cosseno = deltaX/hipotenusa;

    projeteis[indice] = Projetil(tela.carregarTextura("assets/sprites/bala.png"), Vector2(8, 8), centroPlayer, Vector2(0, 0), seno, cosseno, velocidade);
    indice = (indice + 1) % projeteis.size();
}

int Jogo::loopPrincipal(){
    Tela tela;
    Input input;
    _mapa.carregarMapa(tela, "teste-morcego");

    bool rodarLoop=true;
    SDL_Event evento;
    
    SDL_Texture* alface = tela.carregarTextura("assets/sprites/alface.png");
    SDL_Texture* knight = tela.carregarTextura("assets/sprites/knight.png");
    SDL_Texture* spriteMorcego = tela.carregarTextura("assets/sprites/morcego.png");
    SDL_Texture* spritePerseguidor = tela.carregarTextura("assets/sprites/alvo.png");

    player = Player(alface, Vector2(16, 16), _mapa.getSpawnpoint(), Vector2(0, 0));
    player2 = Player(knight, Vector2(32, 32), _mapa.getSpawnpoint(), Vector2(0, 0));

    ataques = std::vector<Ataque>(1, Ataque(Retangulo(500, 500, 40, 40), 200));
    //O if eh para destruir o vector caminhoMorcegos
    if(true){
        std::vector<Linha> caminhoMorcegos = _mapa.getMorcegos();
        int velocidadeMorcegos = 2;

        for(int i=0; i<caminhoMorcegos.size(); i++){
            morcegos.push_back(Morcego(spriteMorcego, Vector2(16, 24), caminhoMorcegos[i].p1, Vector2(0, 0), caminhoMorcegos[i].p2, velocidadeMorcegos));
        }
    }

    perseguidores = std::vector<Perseguidor>(2, Perseguidor(spritePerseguidor, Vector2(16, 16), Vector2(400, 400), Vector2(0, 0), 1.5));
    perseguidores[0].perseguir(morcegos[0].getpX(), morcegos[0].getpY());
    perseguidores[1].perseguir(player.getpX(), player.getpY());

    //Testar o desempenho
    for(int i=2; i<4; i++){
        perseguidores.push_back(Perseguidor(spritePerseguidor, Vector2(16, 16), Vector2(400, 400), Vector2(0, 0), 1.5 + i/10.0f));
        perseguidores[i].perseguir(player.getpX(), player.getpY());
    }

    player.adicionarControles({SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_R, SDL_SCANCODE_LSHIFT});
    player2.adicionarControles({SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J, SDL_SCANCODE_L, SDL_SCANCODE_RSHIFT});

    _indice = 0;
    _projeteis = std::vector<Projetil>(8);
    int tempoInicial = SDL_GetTicks();

    tela.selecionarSeguirCamera(player.getpX(), player.getpY());
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
                if(evento.button.button == SDL_BUTTON_RIGHT){
                    atirar(tela, player, _projeteis, _indice);
                }

                if(evento.button.button == SDL_BUTTON_LEFT){
                    if(ataques[0].estaRodando() == false){
                        ataques[0].invocarAtaque(player, player.getDirecao());
                    }
                }
            }

            if(evento.type == SDL_MOUSEWHEEL) {
                if(evento.wheel.y > 0) {
                    int posicaoAtual = perseguidores.size()-1;
                    perseguidores.push_back(Perseguidor(spritePerseguidor, Vector2(16, 16), Vector2(400, 400), Vector2(0, 0), 1.5 + posicaoAtual/10.0f));
                    perseguidores[posicaoAtual+1].perseguir(player.getpX(), player.getpY());
                } 
                else if(evento.wheel.y < 0) {
                    if(perseguidores.size() > 1){
                        perseguidores.pop_back();
                    }
                }
            }
            
            input.receberInput(evento);

            //Alguns comandos para debuggar e se divertir
            if(input.foiLiberada(SDL_SCANCODE_G)){
                exibirColisoes = !exibirColisoes;
                printf("exibirColisoes: %d\n", exibirColisoes);
            }
            if(input.foiPressionada(SDL_SCANCODE_MINUS)){
                aumentarSprite++;
            }
            if(input.foiPressionada(SDL_SCANCODE_EQUALS)){
                if(aumentarSprite>1){
                    aumentarSprite--;
                }
            }
            if(input.foiLiberada(SDL_SCANCODE_Z)){
                ataqueMata = !ataqueMata;
                printf("Ataque mata: %d\n", ataqueMata);
            }
            if(input.foiLiberada(SDL_SCANCODE_H)){
                gravidade = !gravidade;
                printf("Ataque mata: %d\n", gravidade);
            }
        }
        player.executarControles(input);
        player2.executarControles(input);

        //Estabilizando a taxa de fps
        int tempoAtual = SDL_GetTicks();
        int delta = tempoAtual - tempoInicial;
        
        if(delta < deltaT){
            SDL_Delay(deltaT - delta);
            delta = deltaT;
        }

        atualizar(delta);
        medirFPS(delta, tela);
        desenhar(tela);

        tempoInicial = tempoAtual;
    }

    return 0;
}

void Jogo::atualizar(int tempo){
    player.atualizar(tempo);
    player2.atualizar(tempo);
    
    for(int i=0; i<morcegos.size(); i++){
        morcegos[i].atualizar(tempo);
    }

    _mapa.atualizar(tempo);
    _mapa.lidarColisao(player);
    _mapa.lidarColisao(player2);

    for(int i=0; i<_projeteis.size(); i++){
        _projeteis[i].atualizar(tempo);
    }

    for(int i=0; i<perseguidores.size(); i++){
        perseguidores[i].atualizar(tempo);
    }

    std::vector<Retangulo> colisoes = _mapa.getColisoes();
    for(int i=0; i<_projeteis.size(); i++){
        for(int j=0; j<colisoes.size(); j++){
            _projeteis[i].lidarColisao(colisoes[j]);
        }

        _projeteis[i].lidarColisao(player2);

        for(int j=0; j<perseguidores.size(); j++){
            _projeteis[i].lidarColisao(perseguidores[j]);
        }
    }

    for(int i=0; i<ataques.size(); i++){
        ataques[i].atualizar(tempo);
        
        ataques[i].lidarColisao(player2);
        ataques[i].lidarColisao(morcegos);
        
        for(int j=0; j<perseguidores.size(); j++){
            ataques[i].lidarColisao(perseguidores[j]);
        }
    }
}

void Jogo::desenhar(Tela &tela){
    _mapa.mostrar(tela);
    player.mostrar(tela);
    player2.mostrar(tela);

    for(int i=0; i<perseguidores.size(); i++){
        perseguidores[i].mostrar(tela);
    }

    for(int i=0; i<morcegos.size(); i++){
        morcegos[i].mostrar(tela);
    }

    for(int i=0; i<ataques.size(); i++){
        ataques[i].mostrar(tela);
    }

    tela.apresentar();

    for(int i=0; i<_projeteis.size(); i++){
        _projeteis[i].mostrar(tela);
    }
}