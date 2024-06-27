#include "projetil.h"
#include "global.h"

Projetil::Projetil():_inativo(true){}
Projetil::~Projetil(){}

Projetil::Projetil(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, float angulo, int velocidade):
    Entidade(tex, tamanho, posTela, posImagem), _angulo(angulo), _velocidade(velocidade), _tempo(0), _inativo(false){
        adicionarAnimacao("base", infoAnimacao(Vector2(0, 0), 100, 3));
    }

void Projetil::atualizar(int tempoDecorrido){
    if(_inativo == false){
        _tempo += tempoDecorrido;
        Entidade::atualizar(tempoDecorrido);
        if(_tempo >= deltaT){
            _x += _velocidade;
            _y += _velocidade * _angulo;
            _tempo -= deltaT;
        }

        //printf("(%f, %f) angulo: %f\n", _x, _y, _angulo);
    }
}

void Projetil::mostrar(Tela& tela){
    if(_inativo == false){
        Entidade::mostrar(tela);
    }
}

void Projetil::desativarProjetil(){
    _inativo = true;
}

bool Projetil::estaAtivo(){
    return !_inativo;
}

void Projetil::lidarColisao(Retangulo& colidido){
    if(_inativo==false){
        if(getCaixaColisao().colisaoAABB(colidido)){
            _inativo = true;
        }
    }
}