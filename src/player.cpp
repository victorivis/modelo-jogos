#include "player.h"
#include "imagem.h"
#include "global.h"

namespace constantesPlayer{
    float moveSpeed = 1.0f;
    float moveCap = 4.0f;
    float atrito = 0.8f;
};

//Por algum motivo eh impossivel selecionar a animacao no construtor
Player::Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem)
    : Entidade(tex, tamanho, posTela, posImagem), _dx(0), _dy(0), _olhando(NENHUMA), _spawnpoint(posTela){

    adicionarAnimacao("idleEsquerda", infoAnimacao(Vector2(0, 0), 100, 1));
    adicionarAnimacao("idleDireita", infoAnimacao(Vector2(0, 16), 100, 1));

    adicionarAnimacao("correrEsquerda", infoAnimacao(Vector2(0, 0), 300, 3));
    adicionarAnimacao("correrDireita", infoAnimacao(Vector2(0, 16), 300, 3));
}

void Player::mover(Direcao direcao){
    switch (direcao){
        case DIREITA:
            if(_dx < constantesPlayer::moveCap) _dx += constantesPlayer::moveSpeed;
            if(_olhando != DIREITA){
                selecionarAnimacao("correrDireita");
                _olhando = DIREITA;
            }
            break;
        case ESQUERDA:
            if(-_dx < constantesPlayer::moveCap) _dx -= constantesPlayer::moveSpeed;
            if(_olhando != ESQUERDA){
                selecionarAnimacao("correrEsquerda");
                _olhando = ESQUERDA;
            }
            break;
        case CIMA:
            if(-_dy < constantesPlayer::moveCap) _dy -= constantesPlayer::moveSpeed;
            //_olhando = CIMA;
            break;
        case BAIXO:
            if(_dy < constantesPlayer::moveCap) _dy += constantesPlayer::moveSpeed;
            //_olhando = BAIXO;
            break;
    }
}

void Player::executarControles(Input &input){
    if(input.estaPressionada(SDL_SCANCODE_W)){
        mover(CIMA);
    }
    if(input.estaPressionada(SDL_SCANCODE_S)){
        mover(BAIXO);
    }
    if(input.estaPressionada(SDL_SCANCODE_A)){
        mover(ESQUERDA);
    }
    if(input.estaPressionada(SDL_SCANCODE_D)){
        mover(DIREITA);
    }
    if(input.foiPressionada(SDL_SCANCODE_G)){
        exibirColisoes = !exibirColisoes;
        printf("exibirColisoes: %d\n", exibirColisoes);
    }
    if(input.foiPressionada(SDL_SCANCODE_R)){
        setX(_spawnpoint.x);
        setY(_spawnpoint.y);
    }

    if(input.foiPressionada(SDL_SCANCODE_MINUS)){
        aumentarSprite++;
    }
    if(input.foiPressionada(SDL_SCANCODE_EQUALS)){
        if(aumentarSprite>1){
            aumentarSprite--;
        }
    }

    if(input.estaPressionada(SDL_SCANCODE_A)==false && input.estaPressionada(SDL_SCANCODE_D)==false){
        _dx *= constantesPlayer::atrito;
        _olhando == DIREITA ? selecionarAnimacao("idleDireita") : selecionarAnimacao("idleEsquerda");
    }

    if(input.estaPressionada(SDL_SCANCODE_W)==false && input.estaPressionada(SDL_SCANCODE_S)==false){
        _dy *= constantesPlayer::atrito;
    }
}

void Player::atualizar(int tempoDecorrido){
    if(_animacaoAtual == nullptr){
        selecionarAnimacao("idleDireita");
    }
    Entidade::atualizar(tempoDecorrido);

    _x += _dx;
    _y += _dy;
}

void Player::mostrar(Tela &tela){
    Entidade::mostrar(tela);
}

int Player::getAltura(){
    return _tamanho.y * aumentarSprite;
}