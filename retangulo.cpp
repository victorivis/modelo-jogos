#include "retangulo.h"
#include "iostream"

Retangulo::Retangulo(int x, int y, int largura, int altura):
    _x(x), _y(y), _largura(largura), _altura(altura){}

bool Retangulo::colisaoAABB(Retangulo& retangulo){
    return getDireita() > retangulo.getEsquerda() &&
               getEsquerda() < retangulo.getDireita() &&
               getBaixo() > retangulo.getCima() &&
               getCima() < retangulo.getBaixo();
}

Direcao Retangulo::ladoColisao(Retangulo& retangulo){
    if (!colisaoAABB(retangulo)) {
        return NENHUMA;
    }

    int dx1 = retangulo.getDireita() - getEsquerda();
    int dx2 = getDireita() - retangulo.getEsquerda();
    int dy1 = retangulo.getBaixo() - getCima();
    int dy2 = getBaixo() - retangulo.getCima();

    int minDx = dx1 < dx2 ? dx1 : dx2;
    int minDy = dy1 < dy2 ? dy1 : dy2;

    if (minDx < minDy) {
        return (dx1 < dx2) ? ESQUERDA : DIREITA;
    } else {
        return (dy1 < dy2) ? CIMA : BAIXO;
    }
}

int Retangulo::getDireita(){
    return _x + _largura;
}

int Retangulo::getEsquerda(){
    return _x;
}

int Retangulo::getCima(){
    return _y;
}

int Retangulo::getBaixo(){
    return _y + _altura;
}

int Retangulo::getLargura(){
    return _largura;
}

int Retangulo::getAltura(){
    return _altura;
}

void Retangulo::setX(int num){
    _x = num;
}

void Retangulo::setY(int num){
    _y = num;
}

void Retangulo::debugRetangulo(){
    printf("(%d, %d, %d, %d)\n", _x, _y, _largura, _altura);
}

void Retangulo::exibirRetangulo(Tela& tela){
    SDL_Rect myRect = getSDLRect();
    SDL_SetRenderDrawColor(tela.getRenderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(tela.getRenderer(), &myRect);
}

SDL_Rect Retangulo::getSDLRect(){
    return {_x, _y, _largura, _altura};
}