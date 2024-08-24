#pragma once
#include <string>
#include <vector>

#include "imagem.h"
#include "retangulo.h"
#include "animacao.h"
#include "player.h"
#include "inclinacao.h"
#include "blocos.h"
#include "inimigos.h"
#include "porta.h"

void lerCSV(const char* minhaString, char charDividir, std::vector<Vector2>& GidPosicao);
Vector2 calcularGidRelativo(int gidAtual, int firstgid, int larguraTextura, int larguraBloco, int alturaBloco);
std::vector<std::string> split(const char* minhaString, char charDividir);

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
        
        void carregarMapa(std::string caminhoParaMapa);
        void lidarColisao(Player& player);
        void atualizar(int tempoDecorrido);
        void mostrar(Tela& tela);
        std::vector<Retangulo> getColisoes();
        std::vector<Linha> getMorcegos();
        Vector2 getSpawnpoint();

    private:
        std::vector<Retangulo> _colisoes;
        Vector2 _spawnpoint;
        std::vector<BlocoMovel> _blocosMoveis;
        std::vector<Inclinacao> _ladeiras;
        std::vector<Imagem> _blocos;
        std::vector<Animacao> _blocosAnimados;  
        std::vector<Linha> _caminhoMorcegos;  
        std::vector<Porta> _portas;
};