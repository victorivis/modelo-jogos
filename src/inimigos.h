#pragma once
#include "entidade.h"

class Morcego : public Entidade{
    public:
        Morcego();
        ~Morcego();
        Morcego(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, Vector2 trajetoFim, int velocidade);
        void atualizar(int tempoDecorrido);
        void mostrar(Tela& tela);
    
    private:
        Vector2 _trajetoInicio;
        Vector2 _trajetoFim;
        float _cosseno;
        float _seno;
        int _velocidade;
        bool sentido;
};

class Perseguidor : public Entidade {
    public:
        Perseguidor();
        ~Perseguidor();
        Perseguidor(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, float velocidade=2.5);
        void perseguir(float* posX, float* posY);
        void atualizar(int tempoDecorrido);

    private:
        float* _perseguidoX;
        float* _perseguidoY;
        float _velocidade;
};