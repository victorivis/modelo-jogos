#pragma once
#include "tela.h"
#include "player.h"
#include "mapa.h"
#include "projetil.h"

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
        Player player2;
        std::vector<Projetil> _projeteis;
        int _indice;
};