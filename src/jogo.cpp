#include "jogo.h"
#include "global.h"
#include "input.h"
#include "mapa.h"

#include <cmath>
#include <iostream>

Jogo::Jogo(): _indice(0){

}

Jogo::~Jogo(){

}

void medirFPS(int& tempoDecorrido, Tela& tela, int numEntidades){
    static int tempoAquiDentro=0;
    static int framesAtuais=0;
    
    framesAtuais++;
    tempoAquiDentro+=tempoDecorrido;
    if(tempoAquiDentro >= 1000){
        char nomeAplicativo[100];
        sprintf(nomeAplicativo, "Uma simples game engine - Entidades: %d - FPS: %d", numEntidades, framesAtuais);
        SDL_SetWindowTitle(tela.getWindow(), nomeAplicativo);
        tempoAquiDentro -= 1000;
        framesAtuais=0;
    }
}

void atirar(Tela &tela, Player& player, std::vector<Projetil>& projeteis, int &indice){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    Retangulo colisaoPlayer = player.getCaixaColisao();
    Vector2 centroPlayer(colisaoPlayer.getCentroX(), colisaoPlayer.getCentroY());

    float deltaX = mouseX / aumentarSprite - tela.getCameraX() - centroPlayer.x;
    float deltaY = mouseY / aumentarSprite - tela.getCameraY() - centroPlayer.y;

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
    
    _mapa.carregarMapa("teste-morcego");

    bool rodarLoop=true;
    SDL_Event evento;
    
    SDL_Texture* alface = tela.carregarTextura("assets/sprites/alface.png");
    SDL_Texture* knight = tela.carregarTextura("assets/sprites/knight.png");
    SDL_Texture* spriteMorcego = tela.carregarTextura("assets/sprites/morcego.png");
    SDL_Texture* spritePerseguidor = tela.carregarTextura("assets/sprites/alvo.png");

    _players = {
        Player(alface, Vector2(16, 16), Vector2(), Vector2(0, 0)),
        Player(knight, Vector2(32, 32), Vector2(), Vector2(0, 0)),
    };

    if(_players.size() > 0) _players[0].adicionarControles({SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_R, SDL_SCANCODE_LSHIFT});
    if(_players.size() > 1) _players[1].adicionarControles({SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J, SDL_SCANCODE_L, SDL_SCANCODE_RSHIFT});


    for(int i=0; i<_players.size(); i++){
        _players[i].setSpawnPoint(_mapa.getSpawnpoint());
        _players[i].voltarParaSpawn();
    }

    ataques = std::vector<Ataque>(1, Ataque(Retangulo(500, 500, 40, 40), 200));
    //O if eh para destruir o vector caminhoMorcegos
    if(true){
        //std::vector<Linha> caminhoMorcegos = _mapa.getMorcegos();
        int velocidadeMorcegos = 2;

        //for(int i=0; i<caminhoMorcegos.size(); i++){
        //    morcegos.push_back(Morcego(spriteMorcego, Vector2(16, 24), caminhoMorcegos[i].p1, Vector2(0, 0), caminhoMorcegos[i].p2, velocidadeMorcegos));
        //}
    }

    perseguidores = std::vector<Perseguidor>(2, Perseguidor(spritePerseguidor, Vector2(16, 16), Vector2(400, 400), Vector2(0, 0), 1.5));
    
    /*
    if(_mapa.numMorcegos() > 0 && perseguidores.size() > 0){
        perseguidores[0].perseguir(morcegos[0].getpX(), morcegos[0].getpY());
    }
    */

    if(perseguidores.size() > 1){
        perseguidores[1].perseguir(_players[0].getpX(), _players[0].getpY());
    }    

    //Testar o desempenho
    for(int i=2; i<4; i++){
        perseguidores.push_back(Perseguidor(spritePerseguidor, Vector2(16, 16), Vector2(400, 400), Vector2(0, 0), 1.5 + i/10.0f));
        perseguidores[i].perseguir(_players[0].getpX(), _players[0].getpY());
    }

    _projeteis = std::vector<Projetil>(8);
    int tempoInicial = SDL_GetTicks();

    tela.selecionarSeguirCamera(_players[0].getpX(), _players[0].getpY());
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
                    atirar(tela, _players[0], _projeteis, _indice);
                }

                if(evento.button.button == SDL_BUTTON_LEFT){
                    if(ataques[0].estaRodando() == false){
                        ataques[0].invocarAtaque(_players[0], _players[0].getDirecao());
                    }
                }
            }

            if(evento.type == SDL_MOUSEWHEEL) {
                if(evento.wheel.y > 0) {
                    for(int i=0; i<12; i++){
                        int posicaoAtual = perseguidores.size();
                        perseguidores.push_back(Perseguidor(spritePerseguidor, Vector2(16, 16), Vector2(400, 400), Vector2(0, 0), 1.5 + (posicaoAtual-1)/10.0f ));
                        perseguidores[posicaoAtual].perseguir(_players[0].getpX(), _players[0].getpY());
                    }                  
                    
                } 
                else if(evento.wheel.y < 0) {
                    int cont=5;
                    while(perseguidores.empty()==false && cont--){
                        perseguidores.pop_back();
                    }
                }
            }

            else if(evento.type == SDL_WINDOWEVENT){
                if(evento.window.event == SDL_WINDOWEVENT_RESIZED){
                    tela.atualizarTamanhoCamera();
                }
            }
            
            input.receberInput(evento);

            //Alguns comandos para debuggar e se divertir
            if(input.foiLiberada(SDL_SCANCODE_G)){
                exibirColisoes = !exibirColisoes;
                printf("exibirColisoes: %d\n", exibirColisoes);
            }

            const float fatorZoom=0.25;
            if(input.foiPressionada(SDL_SCANCODE_MINUS)){
                aumentarSprite+=fatorZoom;
                std::cout << "Tamanho sprite" << aumentarSprite << "\n";
            }
            if(input.foiPressionada(SDL_SCANCODE_EQUALS)){
                if(aumentarSprite - fatorZoom > 0){
                    aumentarSprite-=fatorZoom;
                    std::cout << "Tamanho sprite" << aumentarSprite << "\n";
                }
            }
            if(input.foiLiberada(SDL_SCANCODE_Z)){
                ataqueMata = !ataqueMata;
                printf("Ataque mata: %d\n", ataqueMata);
            }
            if(input.foiLiberada(SDL_SCANCODE_H)){
                gravidade = !gravidade;
                printf("Gravidade: %d\n", gravidade);
            }
            if(input.foiLiberada(SDL_SCANCODE_F)){
                FPS = (FPS==50 ? 5000 : 50);
                deltaT = 1000/FPS;
                printf("Limite de FPS: %d\n", FPS);
            }

            const int velocidadeCamera = 10;

            if(input.foiLiberada(SDL_SCANCODE_P)){
                bool estaSeguindo = tela.seguirCamera();

                estaSeguindo ? 
                    tela.selecionarSeguirCamera(nullptr, nullptr) : 
                    tela.selecionarSeguirCamera(_players[0].getpX(), _players[0].getpY());

                printf("Camera segue player: %d\n", !estaSeguindo);
            }

            if(input.estaPressionada(SDL_SCANCODE_UP)){
                tela.moverCameraY(-velocidadeCamera);
            }
            else if(input.estaPressionada(SDL_SCANCODE_DOWN)){
                tela.moverCameraY(velocidadeCamera);
            }
            else if(input.estaPressionada(SDL_SCANCODE_RIGHT)){
                tela.moverCameraX(velocidadeCamera);
            }
            else if(input.estaPressionada(SDL_SCANCODE_LEFT)){
                tela.moverCameraX(-velocidadeCamera);
            }
        }

        for(int i=0; i<_players.size(); i++){
            _players[i].executarControles(input);
        }

        //Estabilizando a taxa de fps
        int tempoAtual = SDL_GetTicks();
        int delta = tempoAtual - tempoInicial;
        
        if(delta < deltaT){
            SDL_Delay(deltaT - delta);
            delta = deltaT;
        }

        atualizar(delta);
        medirFPS(delta, tela, 5 + perseguidores.size());
        desenhar(tela);

        tempoInicial = tempoAtual;
    }

    return 0;
}

void Jogo::atualizar(int tempo){
    for(int i=0; i<_players.size(); i++){
        _players[i].atualizar(tempo);
    }

    _mapa.atualizar(tempo);
    _mapa.lidarColisao(_players);

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

        for(int j=1; j<_players.size(); j++){
            _projeteis[i].lidarColisao(_players[j]);
        }

        for(int j=0; j<perseguidores.size(); j++){
            _projeteis[i].lidarColisao(perseguidores[j]);
        }
    }

    for(int i=0; i<ataques.size(); i++){
        ataques[i].atualizar(tempo);
        
        for(int j=1; j<_players.size(); j++){
            ataques[i].lidarColisao(_players[j]);
        }
        
        for(int j=0; j<perseguidores.size(); j++){
            ataques[i].lidarColisao(perseguidores[j]);
        }
    }
}

void Jogo::desenhar(Tela &tela){
    _mapa.mostrar(tela);
    for(int i=0; i<_players.size(); i++){
        _players[i].mostrar(tela);
    }

    for(int i=0; i<perseguidores.size(); i++){
        perseguidores[i].mostrar(tela);
    }

    for(int i=0; i<ataques.size(); i++){
        ataques[i].mostrar(tela);
    }

    tela.apresentar();

    for(int i=0; i<_projeteis.size(); i++){
        _projeteis[i].mostrar(tela);
    }
}