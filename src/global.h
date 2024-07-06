#pragma once

extern bool mostrarDebug;
extern bool exibirColisoes;
extern float aumentarSprite;
extern const int FPS;
extern const int deltaT;
extern bool gravidade;

enum Direcao{
    DIREITA, ESQUERDA, CIMA, BAIXO, NENHUMA
};

struct Vector2{
    Vector2(){}
    Vector2(int x, int y): x(x), y(y){}

    int x;
    int y;
};

struct Vector3{
    Vector3(){}
    Vector3(int x, int y, int z): x(x), y(y), z(z){}

    int x;
    int y;
    int z;
};

struct Linha{
    Linha(Vector2 inicio, Vector2 fim): p1(inicio), p2(fim){}
    Vector2 p1;
    Vector2 p2;
};

double calcularHipotenusa(Vector2& p1, Vector2& p2);
void calcularSenoCosseno(Vector2 p1, Vector2 p2, float& seno, float& cosseno);