#pragma once
#include "retangulo.h"

class Porta{
    public:
        Porta();
        Porta(Retangulo areaColisao, std::string destino);
        ~Porta();
        Retangulo getRetangulo();
        std::string getDestino();
    private:
        Retangulo _areaColisao;
        std::string _destino;
};