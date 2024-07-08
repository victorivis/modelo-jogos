#include "inimigos.h"

#define construtorMorcego tex, tamanho, posTela, posImagem

Morcego::Morcego(){}
Morcego::~Morcego(){}
Morcego::Morcego(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, Vector2 trajetoFim, int velocidade): 
    _trajetoFim(trajetoFim), _velocidade(velocidade), _trajetoInicio(posTela), sentido(true), Entidade(tex, tamanho, posTela, posImagem){
        calcularSenoCosseno(posTela, trajetoFim, _seno, _cosseno);
    }

void Morcego::atualizar(int tempoDecorrido){
    if(_animacaoAtual == nullptr){
        adicionarAnimacao("morcego", infoAnimacao(Vector2(0, 24), 120, 4));
        selecionarAnimacao("morcego");
    }

    Entidade::atualizar(tempoDecorrido);
    //if(Entidade::atualizar(tempoDecorrido)){
        if(sentido){
            if(_cosseno==0){
                if(_seno > 0 ? _y > _trajetoFim.y : _y < _trajetoFim.y){
                    sentido = false;
                }
            }
            else{
                if(_cosseno > 0 ? _x > _trajetoFim.x : _x < _trajetoFim.x){
                    sentido = false;
                }
            }
        }
        else{
            if(_cosseno==0){
                if(_seno > 0 ? _y < _trajetoInicio.y : _y > _trajetoInicio.y){
                    sentido = true;
                }
            }
            else{
                if(_cosseno > 0 ? _x < _trajetoInicio.x : _x > _trajetoInicio.x){
                    sentido = true;
                }
            }
        }
        
        if(sentido){
            _x += _velocidade * _cosseno;
            _y += _velocidade * _seno;
        }
        else{
            _x -= _velocidade * _cosseno;
            _y -= _velocidade * _seno;
        }
    //}
}

void Morcego::mostrar(Tela& tela){
    Imagem::mostrar(tela);
}

Perseguidor::Perseguidor(): _perseguidoX(nullptr), _perseguidoY(nullptr){}
Perseguidor::~Perseguidor(){}
Perseguidor::Perseguidor(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, float velocidade): 
    Entidade(tex, tamanho, posTela, posImagem), _perseguidoX(nullptr), _perseguidoY(nullptr), _velocidade(velocidade){}

void Perseguidor::perseguir(float* posX, float* posY){
    _perseguidoX = posX;
    _perseguidoY = posY;
}

void Perseguidor::atualizar(int tempoDecorrido){
    if(_animacaoAtual == nullptr){
        adicionarAnimacao("idle", infoAnimacao(Vector2(0, 0), 1, 1));
        selecionarAnimacao("idle");
    }

    Entidade::atualizar(tempoDecorrido);
    if(_perseguidoX != nullptr && _perseguidoY != nullptr){
        float seno, cosseno;
        calcularSenoCosseno(Vector2(getX(), getY()), Vector2(*_perseguidoX, *_perseguidoY), seno, cosseno);

        empurrarX(_velocidade * cosseno);
        empurrarY(_velocidade * seno);
    }
}