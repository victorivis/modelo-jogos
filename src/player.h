#pragma once
#include <SDL2/SDL.h>
#include "entidade.h"
#include "input.h"
#include <vector>

class Player : public Entidade{
    public:
        Player(){}
        Player(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem);
        ~Player(){}

        void mover(Direcao direcao);
        void dash();
        void adicionarControles(std::vector<SDL_Scancode> controles);
        void executarControles(Input &input);
        void setSpawnPoint(Vector2 spawnpoint);
        void voltarParaSpawn();

        void aplicarForcaX(float X);
        void aplicarForcaY(float Y);

        void atualizar(int tempoDecorrido);
        void mostrar(Tela &tela);
        void tocouChao();
        void caiu();
        int getAltura();
        Direcao getDirecao();
        bool estaCaindo();

    private:
        bool _noChao;
        std::vector<SDL_Scancode> _controles;
        Vector2 _spawnpoint;
        Direcao _olhando;
        float _dx;
        float _dy;
        int _tempoPulo;

        float _tempDx;
        float _tempDy;
};

