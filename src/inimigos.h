#pragma once
#include "entidade.h"

class Morcego : public Entidade{
    public:
        Morcego();
        ~Morcego();
        Morcego(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, Vector2 trajetoFim, int velocidade);
        void atualizar(int tempoDecorrido);
    
    private:
        Vector2 _trajetoInicio;
        Vector2 _trajetoFim;
        float _cosseno;
        float _seno;
        int _velocidade;
        bool sentido;
};