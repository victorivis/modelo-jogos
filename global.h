#pragma once

// Por algum motivo essas variaveis estao sendo declaradas multiplas vezes mesmo com pragma once
// o namespace previne que isso aconteca
namespace{
    bool mostrarDebug=true;
    int aumentarSprite=4;
    const int FPS = 30;
}

enum Direcao{
    DIREITA, ESQUERDA, CIMA, BAIXO, NENHUM
};

struct Vector2{
    Vector2(){}
    Vector2(int x, int y): x(x), y(y){}

    int x;
    int y;
};