#pragma once
#include "imagem.h"
#include <map>
#include <vector>


class Animacao : public Imagem{
    public:
        Animacao(){}
        Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, int numeroFrames, int duracao);
        Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, std::vector<Vector2>& frames, int duracao);
        ~Animacao(){}

        void atualizar(int tempo);
        void mostrar(Tela& tela);

    protected:
        std::vector<Vector2> _frames;
        int _duracao;
        int _indice;
        int _totalTempo;
};