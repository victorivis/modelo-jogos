#pragma once
#include <SDL2/SDL.h>
#include "entidade.h"


class Player : virtual public Entidade{
    public:
        Player(){}
        Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem);
        ~Player(){}

        void mover(Direcao direcao);
        void executarControles(SDL_Scancode tecla);

        void atualizar(int tempoDecorrido);
        void mostrar(Tela &tela);
    private:
        int _dx;
        int _dy;
};

