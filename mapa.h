#pragma once
#include <string>
#include <vector>

#include "imagem.h"
#include "retangulo.h"
#include "player.h"

void lerCSV(const char* minhaString, char charDividir, std::vector<Vector2>& GidPosicao);

struct infoBloco{
    infoBloco(){}
    infoBloco(SDL_Texture* textura, int gidAtual):tex(textura), gid(gidAtual){};
    SDL_Texture* tex;
    int gid;
};

class Mapa{
    public:
        Mapa(){};
        ~Mapa(){};
        
        void carregarMapa(Tela& tela, std::string caminhoParaMapa);
        void lidarColisao(Player& player);
        //void Mapa::exibirColisoes(Tela& tela);
        void mostrar(Tela& tela);

    public:
        std::vector<infoBloco> _infoBlocos;
        std::vector<Imagem> _blocos;
        std::vector<Retangulo> _colisoes;
};