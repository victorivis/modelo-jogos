#pragma once
#include "imagem.h"
#include "retangulo.h"
#include <map>

struct infoAnimacao{
    Vector2 _frameInicial;
    int _duracao;
    int _numeroFrames;

    infoAnimacao(){}
    
    infoAnimacao(Vector2 frameInicial, int duracao, int numeroFrames):
        _frameInicial(frameInicial), _duracao(duracao), _numeroFrames(numeroFrames){}
};


class Entidade : public Imagem{
    public:
        Entidade(){}
        ~Entidade(){};
        Entidade(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem);

        void adicionarAnimacao(std::string nome, infoAnimacao info);
        void selecionarAnimacao(std::string nome);

        void atualizar(int tempoDecorrido);
        Retangulo getCaixaColisao();
        //utiliza o void mostrar() de Imagem
    protected:
        int _indice;
        infoAnimacao* _animacaoAtual;
        std::map<std::string, infoAnimacao> _animacoes;
        Retangulo _caixaColisao;
};