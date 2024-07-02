#pragma once

// Por algum motivo essas variaveis estao sendo declaradas multiplas vezes mesmo com pragma once
// o namespace previne que isso aconteca
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