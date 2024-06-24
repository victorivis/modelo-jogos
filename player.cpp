#include "player.h"
#include "imagem.h"

namespace constantesPlayer{
    float moveSpeed = 0.2f;
    float moveCap = 2.0f;
};

Player::Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem):
    Entidade(tex, tamanho, posTela, posImagem){
        //adicionarAnimacao("correrDireita", {Vector2(0, 0), 2, 2});
        //adicionarAnimacao("correrEsquerda", {Vector2(0, 16), 2, 2});
        //selecionarAnimacao("correrDireita");
    }

void Player::mover(Direcao direcao){
    switch (direcao){
        case DIREITA:
            _dx += constantesPlayer::moveSpeed;
            break;
        case ESQUERDA:
            _dx -= constantesPlayer::moveSpeed;
            break;
        case CIMA:
            _dy -= constantesPlayer::moveSpeed;
            break;
        case BAIXO:
            _dy += constantesPlayer::moveSpeed;
            break;
    }
}

void Player::executarControles(SDL_Scancode tecla){
    if(tecla == SDL_SCANCODE_W){
        mover(CIMA);
    }
    else if(tecla == SDL_SCANCODE_S){
        mover(BAIXO);
    }
    else if(tecla == SDL_SCANCODE_A){
        mover(ESQUERDA);
    }
    else if(tecla == SDL_SCANCODE_D){
        mover(DIREITA);
    }
}

void Player::atualizar(int tempoDecorrido){
    Entidade::atualizar(tempoDecorrido);

    _x += _dx;
    _y += _dy;
}

void Player::mostrar(Tela &tela){
    Entidade::mostrar(tela);
    //SDL_Rect origem = {_posImagem.x, _posImagem.y, _tamanho.x, _tamanho.y};
    //SDL_Rect destino = {_x, _y, _tamanho.x * aumentarSprite, _tamanho.y * aumentarSprite};
    //SDL_RenderCopy(tela.getRenderer(), _tex, &origem, &destino);
}