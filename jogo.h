#pragma once
#include "tela.h"
#include "entidade.h"

class Jogo{
    public:
        Jogo();
        ~Jogo();
        int loopPrincipal();
        
        void atualizar(int tempo);
        void desenhar(Tela &tela);
    
    private:
        Entidade player;
};