#include "projetil.h"
#include "global.h"
#include "cmath"

Projetil::Projetil():_inativo(true){}
Projetil::~Projetil(){}

Projetil::Projetil(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, float seno, float cosseno, int velocidade):
    Entidade(tex, tamanho, posTela, posImagem), _seno(seno), _cosseno(cosseno), _velocidade(velocidade), _tempo(0), _inativo(false){
        _angulo = atan2(_seno, _cosseno) * 180.0/M_PI;
        adicionarAnimacao("base", infoAnimacao(Vector2(0, 0), 120, 4));
        selecionarAnimacao("base");
    }

void Projetil::atualizar(int tempoDecorrido){
    if(_inativo == false){
        _tempo += tempoDecorrido;
        Entidade::atualizar(tempoDecorrido);
        if(_tempo >= deltaT){
            _x += _velocidade * _cosseno;
            _y += _velocidade * _seno;
            _tempo -= deltaT;
        }
    }
}

void Projetil::mostrar(Tela& tela){
    if(_inativo == false){
        SDL_Rect origem = {_posImagem.x, _posImagem.y, _tamanho.x, _tamanho.y};
        SDL_Rect destino = {_x, _y, _tamanho.x * aumentarSprite, _tamanho.y * aumentarSprite};
        SDL_RenderCopyEx(tela.getRenderer(), _tex, &origem, &destino, _angulo, NULL, SDL_FLIP_NONE);
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