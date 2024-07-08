#include "player.h"
#include "imagem.h"
#include "global.h"

namespace constantesPlayer{
    float moveSpeed = 2.0f;
    float moveCap = 4.0f;
    float atrito = 0.90f;
    float forcaGravidade=0.8f;
    float limiteGravidade=8.0f;
    int tempoPulo = 400;
    float forcaPulo = 12*forcaGravidade;
};

//Por algum motivo eh impossivel selecionar a animacao no construtor
Player::Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem)
    : Entidade(tex, tamanho, posTela, posImagem), _dx(0), _dy(0), _olhando(NENHUMA), _spawnpoint(posTela), _noChao(false), _tempoPulo(0){

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
            if(-_dy < constantesPlayer::moveCap){
                if(gravidade){
                    _dy -= constantesPlayer::forcaPulo * _tempoPulo / constantesPlayer::tempoPulo;
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

void Player::adicionarControles(std::vector<SDL_Scancode> controles){
    _controles = controles;
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
        setX(_spawnpoint.x);
        setY(_spawnpoint.y);
        caiu();
    }
    
    if(input.estaPressionada(_controles[2])==false && input.estaPressionada(_controles[3])==false){
        _dx *= constantesPlayer::atrito;
        _olhando == DIREITA ? selecionarAnimacao("idleDireita") : selecionarAnimacao("idleEsquerda");
    }

    if(input.estaPressionada(_controles[0])==false && input.estaPressionada(_controles[1])==false){
        if(_noChao == false){
            _tempoPulo = 0;
        }
        _dy *= constantesPlayer::atrito;
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

    _x += _dx;
    _y += _dy;
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