#pragma once
#include "tela.h"

class Jogo{
    public:
        Jogo();
        ~Jogo();
        int loopPrincipal();
        
        void desenhar(Tela &tela);
};