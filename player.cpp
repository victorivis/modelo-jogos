#include "player.h"
#include "imagem.h"

namespace constantesPlayer{
    float moveSpeed = 1.0f;
    float moveCap = 4.0f;
};

//Por algum motivo eh impossivel selecionar a animacao no construtor
Player::Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem)
    : Entidade(tex, tamanho, posTela, posImagem), _dx(0), _dy(0) {

    adicionarAnimacao("idleEsquerda", infoAnimacao(Vector2(0, 0), 10000, 1));
    adicionarAnimacao("idleDireita", infoAnimacao(Vector2(0, 16), 10000, 1));

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
    if(input.foiPressionada(SDL_SCANCODE_W)){
        mover(CIMA);
    }
    if(input.foiPressionada(SDL_SCANCODE_S)){
        mover(BAIXO);
    }
    if(input.foiPressionada(SDL_SCANCODE_A)){
        mover(ESQUERDA);
    }
    if(input.foiPressionada(SDL_SCANCODE_D)){
        mover(DIREITA);
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