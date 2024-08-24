#include "porta.h"

Porta::Porta(){}

Porta::Porta(Retangulo areaColisao, std::string destino): _areaColisao(areaColisao), _destino(destino){}

Porta::~Porta(){}

Retangulo Porta::getRetangulo(){
    return _areaColisao;
}

std::string Porta::getDestino(){
    return _destino;
}