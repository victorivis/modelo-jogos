#pragma once
#include "tela.h"
#include "player.h"
#include "mapa.h"

class Jogo{
    public:
        Jogo();
        ~Jogo();
        int loopPrincipal();
        
        void atualizar(int tempo);
        void desenhar(Tela &tela);
    
    private:
        Mapa _mapa;
        Player player;
};