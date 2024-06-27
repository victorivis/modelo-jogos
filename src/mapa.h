#pragma once
#include <string>
#include <vector>

#include "imagem.h"
#include "retangulo.h"
#include "animacao.h"
#include "player.h"

void lerCSV(const char* minhaString, char charDividir, std::vector<Vector2>& GidPosicao);
Vector2 calcularGidRelativo(int gidAtual, int firstgid, int larguraTextura, int larguraBloco, int alturaBloco);

struct infoBloco{
    infoBloco(){}
    infoBloco(SDL_Texture* textura, int gidAtual):tex(textura), gid(gidAtual){};
    SDL_Texture* tex;
    int gid;
};

struct infoBlocoAnimado{
    infoBlocoAnimado(){}
    infoBlocoAnimado(int duracao, int firstGid, int idFrameInicial, std::vector<int>& framesAnimacao):
        duracao(duracao), firstGid(firstGid), idFrameInicial(idFrameInicial), framesAnimacao(framesAnimacao){}

    int gidAbsoluto(){return firstGid+idFrameInicial;}

    int duracao;
    int firstGid;
    int idFrameInicial;
    std::vector<int> framesAnimacao;
};

class Mapa{
    public:
        Mapa(){};
        ~Mapa(){};
        
        void carregarMapa(Tela& tela, std::string caminhoParaMapa);
        void lidarColisao(Player& player);
        void atualizar(int tempoDecorrido);
        void mostrar(Tela& tela);
        void recarregar(Tela& tela, std::string caminhoParaMapa);

    public:
        std::vector<Retangulo> _colisoes;

    public:
        std::vector<infoBloco> _infoBlocos;
        std::vector<Imagem> _blocos;
        std::vector<Animacao> _blocosAnimados;        
};