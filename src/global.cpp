#include "global.h"
#include <cmath>

bool mostrarDebug=true;
bool exibirColisoes=false;
float aumentarSprite=1.0f;
int FPS = 50;
int deltaT = 1000 / FPS;
bool gravidade = true;
bool ataqueMata = false;

double calcularHipotenusa(Vector2& p1, Vector2& p2){
    int deltaX = p1.x - p2.x;
    int deltaY = p1.y - p2.y;

    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

void calcularSenoCosseno(Vector2 p1, Vector2 p2, float& seno, float& cosseno){
    double hipotenusa = calcularHipotenusa(p1, p2);

    //Considera p1 como origem e p2 como destino
    if(hipotenusa != 0){
        seno = (p2.y - p1.y) / hipotenusa;
        cosseno = (p2.x - p1.x) / hipotenusa; 
    }
    else{
        seno = 0;
        cosseno = 0;
    }
}