#include "global.h"
#include <cmath>

bool mostrarDebug=false;
bool exibirColisoes=false;
float aumentarSprite=1.5f;
const int FPS = 50;
int const deltaT = 1000 / FPS;
bool gravidade = true;

double calcularHipotenusa(Vector2& p1, Vector2& p2){
    int deltaX = p1.x - p2.x;
    int deltaY = p1.y - p2.y;

    return sqrt(deltaX * deltaX + deltaY * deltaY);
}
void calcularSenoCosseno(Vector2 p1, Vector2 p2, float& seno, float& cosseno){
    double hipotenusa = calcularHipotenusa(p1, p2);
    if(hipotenusa != 0){
        seno = (p1.y - p2.y) / hipotenusa;
        cosseno = (p1.x - p2.x) / hipotenusa; 
    }
    else{
        seno = 0;
        cosseno = 0;
    }
}