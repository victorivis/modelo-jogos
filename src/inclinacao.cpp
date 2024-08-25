#include "inclinacao.h"
#include <cmath>

Inclinacao::Inclinacao(){}
Inclinacao::~Inclinacao(){}

Inclinacao::Inclinacao(Vector2 p1, Vector2 p2): _p1(p1), _p2(p2){
    float hipotenusa = sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) );
    if(hipotenusa!=0){
        _seno = (p1.x - p2.x)/hipotenusa;
    }
    else{
        _seno = 1;
    }
}

bool Inclinacao::estaColidindo(Player& player){
    bool colideX = (_p1.x <= player.getX() && _p2.x >= player.getX()) || (_p2.x <= player.getX() && _p1.x >= player.getX());
    bool colideY = (_p1.y <= player.getY() && _p2.y >= player.getY()) || (_p2.y <= player.getY() && _p1.y >= player.getY());
    return colideX && colideY;
}

void Inclinacao::lidarColisao(Player& player){
    if(estaColidindo(player)){
        if(mostrarDebug){
            printf("Colidindo inclincacao, seno: %f\n", _seno);
        }
        player.setY( (player.getX() - _p1.x) * _seno + _p1.y -player.getAltura()-1);
    }
}

void Inclinacao::mostrar(Tela& tela){
    SDL_SetRenderDrawColor(tela.getRenderer(), 255, 0, 0, 255);
    const Vector2 p1 = Vector2( (_p1.x + tela.getCameraX()) * aumentarSprite, (_p1.y + tela.getCameraY()) * aumentarSprite);
    const Vector2 p2 = Vector2( (_p2.x + tela.getCameraX()) * aumentarSprite, (_p2.y + tela.getCameraY()) * aumentarSprite);

    SDL_RenderDrawLine(tela.getRenderer(), p1.x, p1.y, p2.x, p2.y);
}