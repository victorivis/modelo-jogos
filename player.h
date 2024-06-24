#pragma once
#include <SDL2/SDL.h>
#include "entidade.h"
#include "input.h"

class Player : public Entidade{
    public:
        Player(){}
        Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem);
        ~Player(){}

        void mover(Direcao direcao);
        void executarControles(Input &input);

        void atualizar(int tempoDecorrido);
        void mostrar(Tela &tela);
    private:
        Direcao _olhando;
        int _dx;
        int _dy;
};

