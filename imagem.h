#pragma once

#include "global.h"
#include "tela.h"

struct SDL_Texture;

class Imagem{
    public:
        Imagem(){}
        Imagem(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem);
        ~Imagem(){}

        void mostrar(Tela &tela);

    protected:
        SDL_Texture* _tex;
        Vector2 _tamanho;
        Vector2 _posTela;
        Vector2 _posImagem;
};