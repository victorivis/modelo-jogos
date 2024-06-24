#pragma once
#include "tela.h"
#include "player.h"

class Jogo{
    public:
        Jogo();
        ~Jogo();
        int loopPrincipal();
        
        void atualizar(int tempo);
        void desenhar(Tela &tela);
    
    private:
        Player player;
};