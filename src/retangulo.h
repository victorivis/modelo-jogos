#pragma once
#include "global.h"
#include "tela.h"
#include <SDL2/SDL.h>

class Retangulo{
    public:
    Retangulo(){}
    ~Retangulo(){}
    Retangulo(int x, int y, int largura, int altura);    

    bool colisaoAABB(Retangulo& retangulo);
    Direcao ladoColisao(Retangulo& retangulo);

    int getDireita();
    int getEsquerda();
    int getCima();
    int getBaixo();
    int getLargura();
    int getAltura();
    int getCentroX();
    int getCentroY();

    void setX(int num);
    void setY(int num);
    void debugRetangulo();
    void exibirRetangulo(Tela& tela);
    SDL_Rect getSDLRect();

    private:
        int _x;
        int _y;
        int _largura;
        int _altura;
};