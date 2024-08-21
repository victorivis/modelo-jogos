#include "player.h"
#include "imagem.h"
#include "global.h"
#include <iostream>

void aplicarAtrito(float& delta, float atrito){
    if(abs(delta) >= 0.4f){
        delta *= atrito;
    }
    else if(delta != 0){
        delta = 0;
    }
}

namespace constantesPlayer{
    float moveSpeed = 2.0f;
    float moveCap = 4.0f;
    float atrito = 0.90f;
    float forcaGravidade=0.8f;
    float limiteGravidade=8.0f;
    float dashSpeed = moveSpeed*8;
    int tempoPulo = 400;
    float forcaPulo = 12*0.8f;//forcaGravidade;
};

//Por algum motivo eh impossivel selecionar a animacao no construtor
Player::Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem)
    : Entidade(tex, tamanho, posTela, posImagem), _dx(0), _dy(0), _olhando(NENHUMA), _spawnpoint(posTela), _noChao(false), _tempoPulo(0), _tempDx(0.0f), _tempDy(0.0f){

    adicionarAnimacao("idleEsquerda", infoAnimacao(Vector2(0, 0), 100, 1));
    adicionarAnimacao("idleDireita", infoAnimacao(Vector2(0, 16), 100, 1));

    adicionarAnimacao("correrEsquerda", infoAnimacao(Vector2(0, 0), 300, 3));
    adicionarAnimacao("correrDireita", infoAnimacao(Vector2(0, 16), 300, 3));

    adicionarAnimacao("dashDireita", infoAnimacao(Vector2(0, 48), 100, 2));
    adicionarAnimacao("dashEsquerda", infoAnimacao(Vector2(0, 64), 100, 2));
}

void Player::mover(Direcao direcao){
    switch (direcao){
        case DIREITA:
            if(_dx < constantesPlayer::moveCap) _dx += constantesPlayer::moveSpeed;
            selecionarAnimacao("correrDireita");
            _olhando = DIREITA;
            break;
        case ESQUERDA:
            if(-_dx < constantesPlayer::moveCap) _dx -= constantesPlayer::moveSpeed;
            selecionarAnimacao("correrEsquerda");
            _olhando = ESQUERDA;
            break;
        case CIMA:
            if(-_dy < constantesPlayer::moveCap){
                if(gravidade){
                    _dy -= constantesPlayer::forcaPulo * _tempoPulo / constantesPlayer::tempoPulo;

                    //Isso eh engracado, o player para nao tremer a tela fica enfiado dentro do bloco de colisao
                    //Entao para conseguir pular precisa modificar a posicao dele para que ele saida de dentro do bloco
                    if(_tempoPulo == constantesPlayer::tempoPulo){
                        _y -= 3;
                    }
                }
                else{
                    _dy -= constantesPlayer::moveSpeed;
                }
            }
            //_olhando = CIMA;
            break;
        case BAIXO:
            if(_dy < constantesPlayer::moveCap) _dy += constantesPlayer::moveSpeed;
            //_olhando = BAIXO;
            break;
    }
}

void Player::dash(){
    if(_olhando == DIREITA){
        selecionarAnimacao("dashDireita");
        _tempDx += constantesPlayer::dashSpeed;
    }
    else if(_olhando == ESQUERDA){
        selecionarAnimacao("dashEsquerda");
        _tempDx -= constantesPlayer::dashSpeed;
    }
}

void Player::adicionarControles(std::vector<SDL_Scancode> controles){
    _controles = controles;
}

void Player::setSpawnPoint(Vector2 spawnpoint){
    _spawnpoint = spawnpoint;
}

void Player::voltarParaSpawn(){
    setX(_spawnpoint.x);
    setY(_spawnpoint.y);
    caiu();
}

void Player::executarControles(Input &input){
    if(input.estaPressionada(_controles[0])){
        if(gravidade){
            if(_tempoPulo > 0){
                mover(CIMA);
                _noChao = false;
            }
        }
        else{
            mover(CIMA);
        }
    }
    if(input.estaPressionada(_controles[1])){
        if(gravidade == false){
            mover(BAIXO);
        }
    }
    if(input.estaPressionada(_controles[2])){
        mover(ESQUERDA);
    }
    if(input.estaPressionada(_controles[3])){
        mover(DIREITA);
    }
    if(input.foiPressionada(_controles[4])){
        voltarParaSpawn();
    }
    if(_controles.size() >= 6 && input.foiPressionada(_controles[5])){
        dash();
    }
    
    if(input.estaPressionada(_controles[2])==false && input.estaPressionada(_controles[3])==false){
        _dx *= constantesPlayer::atrito;
        if(abs(_tempDx) < 1.0f && abs(_tempDy) < 1.0f){
            _olhando == DIREITA ? selecionarAnimacao("idleDireita") : selecionarAnimacao("idleEsquerda");
        }
    }

    if(input.estaPressionada(_controles[0])==false && input.estaPressionada(_controles[1])==false){
        if(_noChao == false){
            _tempoPulo = 0;
        }
        
        aplicarAtrito(_dy, constantesPlayer::atrito);
    }
}

void Player::aplicarForcaX(float intensidade){
    _dx += intensidade;
}

void Player::aplicarForcaY(float intensidade){
    _dy += intensidade;
}

void Player::atualizar(int tempoDecorrido){
    if(_animacaoAtual == nullptr){
        selecionarAnimacao("idleDireita");
    }
    Entidade::atualizar(tempoDecorrido);

    if(gravidade && _noChao == false && _dy < constantesPlayer::limiteGravidade){
        _dy += constantesPlayer::forcaGravidade;
    }

    if(_noChao == false){
        _tempoPulo -= tempoDecorrido;
    }

    _x += _dx + _tempDx;
    _y += _dy + _tempDy;

    aplicarAtrito(_tempDx, 0.9f);
    aplicarAtrito(_tempDy, 0.9f);
}

void Player::mostrar(Tela &tela){
    Entidade::mostrar(tela);
}

void Player::tocouChao(){
    _dy = 0.0f;
    _noChao = true;
    _tempoPulo = constantesPlayer::tempoPulo;
}

void Player::caiu(){
    _noChao = false;
    _tempoPulo = 0;
}

int Player::getAltura(){
    return _tamanho.y * aumentarSprite;
}

Direcao Player::getDirecao(){
    return _olhando;
}

bool Player::estaCaindo(){
    return !_noChao;
}