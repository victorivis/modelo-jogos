#include "blocos.h"

BlocoMovel::BlocoMovel(){

}

BlocoMovel::~BlocoMovel(){

}

BlocoMovel::BlocoMovel(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, Vector2 pontoFinal, int velocidade):
    Imagem(tex, tamanho, posTela, posImagem), _pontoInicio(posTela), _pontoFinal(pontoFinal), _velocidade(velocidade), _sentido(true){
        calcularSenoCosseno(posTela, pontoFinal, _seno, _cosseno);
    }

void BlocoMovel::atualizar(){
        if(_sentido){
            if(_cosseno==0){
                if(_seno > 0 ? _y > _pontoFinal.y : _y < _pontoFinal.y){
                    _sentido = false;
                }
            }
            else{
                if(_cosseno > 0 ? _x > _pontoFinal.x : _x < _pontoFinal.x){
                    _sentido = false;
                }
            }
        }
        else{
            if(_cosseno==0){
                if(_seno > 0 ? _y < _pontoInicio.y : _y > _pontoInicio.y){
                    _sentido = true;
                }
            }
            else{
                if(_cosseno > 0 ? _x < _pontoInicio.x : _x > _pontoInicio.x){
                    _sentido = true;
                }
            }
        }
        
        _x += getDeslocamentoX();
        _y += getDeslocamentoY();
}

Retangulo BlocoMovel::getHitBox(){
    return Retangulo(_x, _y, _tamanho.x, _tamanho.y);
}

double BlocoMovel::getDeslocamentoX(){
    if(_sentido){
        return _velocidade * _cosseno;
    }
    return -_velocidade * _cosseno;
}
double BlocoMovel::getDeslocamentoY(){
    if(_sentido){
        return _velocidade * _seno;
    }
    return -_velocidade * _seno;
}