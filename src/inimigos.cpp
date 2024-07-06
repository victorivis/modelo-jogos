#include "inimigos.h"

#define construtorMorcego tex, tamanho, posTela, posImagem

Morcego::Morcego(){}
Morcego::~Morcego(){}
Morcego::Morcego(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, Vector2 trajetoFim, int velocidade): 
    _trajetoFim(trajetoFim), _velocidade(velocidade), _trajetoInicio(posTela), Entidade(construtorMorcego){
        adicionarAnimacao("idle", infoAnimacao(Vector2(0, 0), 200, 5));
        selecionarAnimacao("idle");

        calcularSenoCosseno(posTela, trajetoFim, _seno, _cosseno);
    }

void Morcego::atualizar(int tempoDecorrido){
    Entidade::atualizar(tempoDecorrido);
    
    if(sentido){
        _x += _velocidade * _cosseno;
        _y += _velocidade * _seno;
    }
    else{
        _x -= _velocidade * _cosseno;
        _y -= _velocidade * _seno;
    }

    if(_x < _trajetoFim.x){
        _x = _trajetoInicio.x;
        _y = _trajetoInicio.y;
    }

    //if(sentido){
    //    if(_cosseno > 0 ? _x < _trajetoFim.x : _x > _trajetoFim.x){
    //        sentido = false;
    //    }            
    //}
    //else if((_cosseno < 0 ? _x <= _trajetoInicio.x : _x >= _trajetoInicio.x)  ){
    //    sentido = true;
    //}

        /*
        if(sentido){
            if(_cosseno < 0 ? _x < _trajetoFim.x : _x > _trajetoFim.x){
                sentido = false;
            }            
        }
        else if((_cosseno < 0 ? _x <= _trajetoInicio.x : _x >= _trajetoInicio.x)  ){
            sentido = true;
        }
        */

    /*
    if((_x <= _trajetoFim.x && _x >= _trajetoInicio.x)){
        _x = _trajetoInicio.x;
        _y = _trajetoInicio.y;
    }
    */

        /*
        if(sentido){
            if(_x < _trajetoFim.x){
                sentido = false;
            }            
        }
        else if(_x <= _trajetoInicio.x){
            sentido = true;
        }
        */
}