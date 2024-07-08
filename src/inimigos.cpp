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

//Perseguidor::Perseguidor(){}
//Perseguidor::~Perseguidor(){}
//Perseguidor::Perseguidor(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem): Entidade(tex, tamanho, posTela, posImagem){}
//
//void Perseguidor::perseguir(Vector2 pos){
//    
//}